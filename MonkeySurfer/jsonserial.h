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
#define WRITE_MAX_ELAPSED_TIME_MS 200

class JsonSerial {
public:
    JsonSerial();
    ~JsonSerial();

    void openSerialPort(const char* port);

    void setJson();
    void sendJson();
    void recvJson();
private:
    // SERIAL
    void readSerial();
    void writeSerial(const char* data);
    bool msgAvailable();
    void printData();

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
    std::string _jstr; // string dans lequel le dump du contenu du doc json est fait
    std::chrono::steady_clock::time_point _lastWrite;
    std::chrono::steady_clock::time_point _now;
    std::chrono::milliseconds _elapsed;

    // JSON
    nlohmann::json _sendJson;
    nlohmann::json _recvJson;
};

#endif // JSONSERIAL_H!
