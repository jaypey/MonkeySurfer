#include "jsonserial.h"

JsonSerial::JsonSerial() {
    _work = nullptr;
    _context = nullptr;
    _serial = nullptr;
    _contextThread = nullptr;

    _serialData[0] = '\0';
    _msg[0] = '\0';

    _readAvailable = false;
    _receivingMsg = false;
    _newData = false;
    _ndx = 0;

    _writeAvailable = false;
    _lastWrite = std::chrono::steady_clock::now();
    _elapsed = std::chrono::milliseconds(0);
}

JsonSerial::~JsonSerial() {
    delete _work;
    delete _context;
    delete _serial;
    delete _contextThread;
}

void JsonSerial::openSerialPort(const char* port) {
    if (_serial && _serial->is_open()) {
        std::cerr << "Port serial deja ouvert." << std::endl;
        return;
    }

    try {
        _context = new asio::io_context;
        _work = new asio::io_context::work(*_context);
        _serial = new asio::serial_port(*_context, port);
        _contextThread = new std::thread([this]() {_context->run(); });

        _serial->set_option(asio::serial_port_base::baud_rate(9600));

        _readAvailable = true;
        _writeAvailable = true;
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur: " << e.what() << std::endl;
    }
}

void JsonSerial::setJson() {
    _sendJson["score"] = 123;
    _sendJson["bouclierTempsRestantMs"] = 1500;
    _sendJson["powerUpTempsRestantMs"] = 600;
}

void JsonSerial::sendJson() {
    _now = std::chrono::steady_clock::now();
    _elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(_now - _lastWrite);
    if (_elapsed.count() >= WRITE_MAX_ELAPSED_TIME_MS) {
        _jstr = _sendJson.dump();
        _jstr.insert(0, 1, '>');
        _jstr.append(1, '<');
        writeSerial(_jstr.c_str());

        _lastWrite = std::chrono::steady_clock::now();
    }

}

void JsonSerial::recvJson() {
    readSerial();
    if (msgAvailable()) {
        printData();
    }
}

void JsonSerial::readSerial() {
    if (!_serial || !_serial->is_open()) {
        std::cerr << "Les donnees du port serial ne peuvent pas etre lues, le port serial doit etre ouvert." << std::endl;
        return;
    }

    if (_readAvailable && !_newData) {
        _readAvailable = false;

        _serial->async_read_some(asio::buffer(_serialData, sizeof(_serialData)),
            [this](const asio::error_code& error, size_t bytesTransferred) {
                if (error) {
                    std::cerr << "Erreur readSerial: " << error.message() << std::endl;
                    return;
                }

                for (int i = 0; i < bytesTransferred;) {
                    if (_newData)
                        continue; // On stop la lecture tant qu'un nouveau message peut etre lu

                    if (_receivingMsg) {
                        if (_serialData[i] != END_MARKER) {
                            _msg[_ndx] = _serialData[i];
                            _ndx++;
                            if (_ndx >= JSON_DATA_SIZE) {
                                _ndx = JSON_DATA_SIZE - 1;
                            }
                        }
                        else {
                            _msg[_ndx] = '\0';
                            _receivingMsg = false;
                            _ndx = 0;
                            _newData = true;
                        }
                    }
                    else if (_serialData[i] == START_MARKER) {
                        _receivingMsg = true;
                    }

                    i++;
                }

                _readAvailable = true;
            });
    }
}

void JsonSerial::writeSerial(const char* data) {
    if (!_serial || !_serial->is_open()) {
        std::cerr << "Aucune donnee ne peut etre ecrite, le port serial doit etre ouvert." << std::endl;
        return;
    }

    if (_writeAvailable) {
        _writeAvailable = false;

        _serial->async_write_some(asio::buffer(data, std::strlen(data)),
            [this](const asio::error_code& error, size_t bytesTransferred) {
                _writeAvailable = true;
                if (error)
                    std::cerr << "Erreur writeSerial: " << error.message() << std::endl;
            });
    }
}

bool JsonSerial::msgAvailable() {
    return _newData;
}

void JsonSerial::printData() {
    std::cout << _msg << std::endl;
    _newData = false;
}
