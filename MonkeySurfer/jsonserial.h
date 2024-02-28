#ifndef JSONSERIAL_H
#define JSONSERIAL_H

#include <asio.hpp>
#include <functional>
#include <iostream>
#include <json.hpp>
#include <thread>

#define JSON_DATA_SIZE 1024
#define START_MARKER '>'
#define END_MARKER '<'

class JsonSerial {
public:
    JsonSerial();
    ~JsonSerial();

    void openSerialPort(const char* port);
    void readSerial();
    void writeSerial(const char* json);

    bool msgAvailable();
    
    void printData();
private:
    asio::io_context::work* _work;
    asio::io_context* _context;
    asio::serial_port* _serial;
    std::thread* _contextThread;

    char _serialData[JSON_DATA_SIZE]; // buffer intermediaire pour recevoir les donnees du port serial
    char _msg[JSON_DATA_SIZE]; // buffer contenant la string json entrante (le message complet)

    bool _readAvailable; // flag pour async_read_some
    bool _receivingMsg;
    bool _newData;
    int _ndx; // index d'ecriture des donnees dans _msg

    bool _writeAvailable;
};

#endif // JSONSERIAL_H!
