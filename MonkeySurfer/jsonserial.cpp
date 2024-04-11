#include "jsonserial.h"

JsonSerial::JsonSerial() {
    _context = nullptr;
    _serial = nullptr;
    _work = nullptr;
    _runThread = nullptr;

    _read[0] = '\0';
    _msg[0] = '\0';
    _send[0] = '\0';

    _recvInProgress = false;
    _readingMsg = false;
    _newData = false;
    _ndx = 0;

    _sendInProgress = false;
    _lastsend = std::chrono::steady_clock::now();
}
JsonSerial::~JsonSerial() {
    if (_context) delete _context;
    if (_serial) delete _serial;
    if (_work) delete _work;
    if (_runThread) delete _runThread;
}

void JsonSerial::openSerialPort(const char* port) {
    try {
        _context = new asio::io_context;
        _serial = new asio::serial_port(*_context);
        _work = new asio::io_context::work(*_context);
        _runThread = new std::thread([this]() { _context->run(); });

        _serial->open(port);
        _serial->set_option(asio::serial_port_base::baud_rate(BAUD_RATE));
    }
    catch (const asio::system_error& e) {
        errout << "Le port serial n'a pas pu etre ouvert: " << e.what() << std::endl;
    }
}

void JsonSerial::recvJson() {
    recv();

    if (_newData) {
        try {
            _recvjson = nlohmann::json::parse(_msg);
        }
        catch (const nlohmann::json::parse_error& e) {
            errout << "Erreur de conversion str en json: " << e.what() << std::endl;
        }
        _newData = false;
    }
}

void JsonSerial::sendJson() {
    // Delai d'envoi
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastsend);
    if (elapsed.count() < SEND_DELAY)
        return;
    _lastsend = std::chrono::steady_clock::now();

    // test
    _sendjson["delR"] = true;
    _sendjson["delJ"] = true;
    _sendjson["delV"] = true;
    _sendjson["bar"] = true;
    _sendjson["motvib"] = true;

    std::string msg = START_MARKER + _sendjson.dump() + END_MARKER;

    send(msg.c_str());
}

void JsonSerial::recvPrint() {
    recv();

    if (_newData) {
        std::cout << _msg << std::endl;
        _newData = false;
    }
}

bool JsonSerial::boutonAppuye(int indexBtn) {
    if (0 > indexBtn || 3 < indexBtn) {
        errout << "Mauvais index de bouton, fonction \"JsonSerial::boutonAppuye(int indexBtn)\"." << std::endl;
        return false;
    }

    if (!_recvjson.contains("btn")) {
        errout << "La cle \"btn\" ne se retrouve pas dans le document json." << std::endl;
        return false;
    }

    bool appuye = (_recvjson["btn"][indexBtn]["appuye"] == true);
    _recvjson["btn"][indexBtn]["appuye"] = false; // Empeche lectures subsequentes du meme message json ou "appuye" == true
    return appuye;
}

bool JsonSerial::boutonMaintenu(int indexBtn) {
    if (0 > indexBtn || 3 < indexBtn) {
        errout << "Mauvais index de bouton, fonction \"JsonSerial::boutonAppuye(int indexBtn)\"." << std::endl;
        return false;
    }

    if (!_recvjson.contains("btn")) {
        errout << "La cle \"btn\" ne se retrouve pas dans le document json." << std::endl;
        return false;
    }

    return _recvjson["btn"][indexBtn]["maintenu"] == true;
}

bool JsonSerial::joystickMaintenu(Direction dir, bool repeat) {
    const char* jsondir = (dir == HAUT || dir == BAS) ? "joyY" : "joyX";

    if (!_recvjson.contains(jsondir)) {
        errout << "La cle \"" << jsondir << "\" ne se retrouve pas dans le document json." << std::endl;
        return NEUTRE;
    }

    bool dirs_are_equal = ((Direction)_recvjson[jsondir]["dir"] == dir);

    if (repeat) {
        if (_recvjson[jsondir]["repeat"] == true && dirs_are_equal)
            _recvjson[jsondir]["repeat"] = false;
        else
            return NEUTRE;
    }

    return dirs_are_equal;
}

bool JsonSerial::accShake() {
    if (!_recvjson.contains("acc")) {
        errout << "La cle \"acc\" ne se retrouve pas dans le document json." << std::endl;
        return NEUTRE;
    }

    return !_recvjson["acc"];
}
int JsonSerial::muons(RandomGenerator* random, int borneinf, int bornesup) {
    if (!_recvjson.contains("muons")) {
        errout << "La cle \"muons\" ne se retrouve pas dans le document json." << std::endl;
        return NEUTRE;
    }
    else
    {
        random->derniermuons = random->vraimuons;
        random->vraimuons = _recvjson["muons"];
        random->tableau[0] = random->derniermuons;
        random->tableau[1] = random->vraimuons;
        random->muons = random->verificateurNouveauMuon(random->tableau[1], random->tableau[0]);
        random->muons = random->random(1, (162 + random->i) % 25486, random->muons);
        random->muons = random->random(3, 14556, random->muons);
        int rand = random->random(borneinf, bornesup, random->muons);
        std::cout << rand << std::endl;
        random->i = (random->i + 1) % 1727;
    }

    return _recvjson["muons"];
}
void JsonSerial::lcd(const char* msg_row_1, const char* msg_row_2) {
    _sendjson["lcd"][0] = msg_row_1;
    _sendjson["lcd"][1] = msg_row_2;
}

void JsonSerial::recv() {
    if (!_recvInProgress) {
        _recvInProgress = true;

        _serial->async_read_some(asio::buffer(_read, sizeof(_read)),
            [this](const asio::error_code& error, size_t bytes_transferred) {
                if (error) {
                    errout << "Erreur lors de la lecture des donnees de l'arduino: " << error.message() << std::endl;
                    return;
                }

                for (int i = 0; i < bytes_transferred;) {
                    if (_newData)
                        continue;

                    if (_readingMsg == true) {
                        if (_read[i] != END_MARKER) {
                            _msg[_ndx] = _read[i];
                            _ndx++;
                            if (_ndx >= JSON_BUFFER_SIZE) {
                                _ndx = JSON_BUFFER_SIZE - 1;
                            }
                        }
                        else {
                            _msg[_ndx] = '\0';
                            _readingMsg = false;
                            _ndx = 0;
                            _newData = true;
                        }
                    }
                    else if (_read[i] == START_MARKER) {
                        _readingMsg = true;
                    }

                    i++;
                }

                _recvInProgress = false;
            });
    }
}

void JsonSerial::send(const char* msg) {
    if (!_sendInProgress) {
        _sendInProgress = true;

        strcpy_s(_send, msg);

        _serial->async_write_some(asio::buffer(_send, std::strlen(_send)),
            [this](const asio::error_code& error, size_t bytes_transferred) {
                if (error) {
                    errout << "Erreur lors de l'envoi des donnees a l'arduino: " << error.message() << std::endl;
                    return;
                }

                _sendInProgress = false;
            });
    }
}
