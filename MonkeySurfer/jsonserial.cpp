#include "jsonserial.h"

JsonSerial::JsonSerial() {
    _work = nullptr;
    _context = nullptr;
    _serial = nullptr;
    _contextThread = nullptr;

    _data[0] = '\0';

    _readAvailable = false;
    _writeAvailable = false;
    _bytesAvailable = 0;
}

JsonSerial::~JsonSerial() {
    delete _work;
    delete _context;
    delete _serial;
    delete _contextThread;
}

void JsonSerial::openSerialPort(const char* port) {
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
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void JsonSerial::readSerial() {
    if (!_serial || !_serial->is_open()) {
        std::cerr << "Les donnees du port serial ne peuvent pas etre lues, le port serial doit etre ouvert." << std::endl;
        return;
    }

    if (_readAvailable) {
        _readAvailable = false;

        _serial->async_read_some(asio::buffer(_data, sizeof(_data)),
            [this](const asio::error_code& error, size_t bytesTransferred) {
                _readAvailable = true;
                if (!error)
                    _bytesAvailable += bytesTransferred;
                else
                    std::cerr << "Erreur readSerial: " << error.message() << std::endl;
            });
    }
}

void JsonSerial::writeSerial(const char* json) {
    if (!_serial || !_serial->is_open()) {
        std::cerr << "Aucune donnee ne peut etre ecrite, le port serial doit etre ouvert." << std::endl;
        return;
    }

    if (_writeAvailable) {
        _writeAvailable = false;

        _serial->async_write_some(asio::buffer(json, std::strlen(json)),
            [this](const asio::error_code& error, size_t bytesTransferred) {
                if (bytesTransferred < 13) {
                    std::cout << "PROBLEM PROBLEM PROBLEM PROBLEM PROBLEM " << std::endl;
                }
                _writeAvailable = true;
                if (error)
                    std::cerr << "Erreur writeSerial: " << error.message() << std::endl;
            });
    }
}

size_t JsonSerial::bytesAvailable() {
    return _bytesAvailable;
}

void JsonSerial::printData() {
    std::cout.write(_data, _bytesAvailable);
    _bytesAvailable = 0;
}
