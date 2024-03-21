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
        std::cerr << "Le port serial n'a pas pu etre ouvert: " << e.what() << std::endl;
    }
}

void JsonSerial::recvJson() {
    recv();

    if (_newData) {
        try {
            _json = nlohmann::json::parse(_msg);
        }
        catch (const nlohmann::json::parse_error& e) {
            std::cerr << "Erreur de conversion str en json: " << e.what() << std::endl;
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
    nlohmann::json j;
    j["delR"] = true;
    j["delJ"] = true;
    j["delV"] = true;
    j["bar"] = true;
    j["lcd"] = "bonjour";
    j["motvib"] = true;

    std::string msg = START_MARKER + j.dump() + END_MARKER;

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
        std::cerr << "Mauvais index de bouton, fonction \"JsonSerial::boutonAppuye(int indexBtn)\"." << std::endl;
        return false;
    }

    if (!_json.contains("btn")) {
        std::cerr << "La cle \"btn\" ne se retrouve pas dans le document json." << std::endl;
        return false;
    }

    bool appuye = (_json["btn"][indexBtn]["appuye"] == true);
    _json["btn"][indexBtn]["appuye"] = false; // Empeche lectures subsequentes du meme message json ou "appuye" == true
    return appuye;
}

bool JsonSerial::boutonMaintenu(int indexBtn) {
    if (0 > indexBtn || 3 < indexBtn) {
        std::cerr << "Mauvais index de bouton, fonction \"JsonSerial::boutonAppuye(int indexBtn)\"." << std::endl;
        return false;
    }

    if (!_json.contains("btn")) {
        std::cerr << "La cle \"btn\" ne se retrouve pas dans le document json." << std::endl;
        return false;
    }

    return _json["btn"][indexBtn]["maintenu"] == true;
}

Direction JsonSerial::joystickMaintenuX() {
    if (!_json.contains("joyX")) {
        std::cerr << "La cle \"joyX\" ne se retrouve pas dans le document json." << std::endl;
        return NEUTRE;
    }

    return (Direction)_json["joyX"]["dir"];
}

Direction JsonSerial::joystickMaintenuY() {
    if (!_json.contains("joyY")) {
        std::cerr << "La cle \"joyY\" ne se retrouve pas dans le document json." << std::endl;
        return NEUTRE;
    }

    return (Direction)_json["joyY"]["dir"];
}

bool JsonSerial::joystickAppuyeX() {
    if (!_json.contains("joyX")) {
        std::cerr << "La cle \"joyX\" ne se retrouve pas dans le document json." << std::endl;
        return false;
    }

    bool appuye = _json["joyX"]["appuye"];
    _json["joyX"]["appuye"] = false;
    return appuye;
}

bool JsonSerial::joystickAppuyeY() {
    if (!_json.contains("joyY")) {
        std::cerr << "La cle \"joyY\" ne se retrouve pas dans le document json." << std::endl;
        return false;
    }

    bool appuye = _json["joyY"]["appuye"];
    _json["joyY"]["appuye"] = false;
    return appuye;
}

bool JsonSerial::accShake() {
    if (!_json.contains("acc")) {
        std::cerr << "La cle \"acc\" ne se retrouve pas dans le document json." << std::endl;
        return NEUTRE;
    }

    return _json["acc"];
}

void JsonSerial::recv() {
    if (!_recvInProgress) {
        _recvInProgress = true;

        _serial->async_read_some(asio::buffer(_read, sizeof(_read)),
            [this](const asio::error_code& error, size_t bytes_transferred) {
                if (error) {
                    std::cerr << "Erreur lors de la lecture des donnees de l'arduino: " << error.message() << std::endl;
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
                    std::cerr << "Erreur lors de l'envoi des donnees a l'arduino: " << error.message() << std::endl;
                    return;
                }

                _sendInProgress = false;
            });
    }
}
