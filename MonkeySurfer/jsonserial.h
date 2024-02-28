#ifndef JSON_H
#define JSON_H

#include <asio.hpp>
#include <functional>
#include <iostream>
#include <thread>

#define JSON_DATA_SIZE 1024

class JsonSerial {
public:
    JsonSerial();
    ~JsonSerial();

    void openSerialPort(const char* port);
    void readSerial();
    void writeSerial(const char* json);

    size_t bytesAvailable();
    
    void printData();
private:
    asio::io_context::work* _work;
    asio::io_context* _context;
    asio::serial_port* _serial;
    std::thread* _contextThread;

    char _data[JSON_DATA_SIZE];

    bool _readAvailable; // flag pour async_read_some
    bool _writeAvailable;

    size_t _bytesAvailable; // 
};

#endif // JSON_H!
