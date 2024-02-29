#ifndef JSONSERIAL_H
#define JSONSERIAL_H

#include <asio.hpp>
#include <chrono>
#include <iostream>
#include <json.hpp>
#include <thread>

#define BAUD_RATE 112500
#define START_MARKER '>'
#define END_MARKER '<'
#define JSON_BUFFER_SIZE 1024
#define SEND_DELAY 50

class JsonSerial {
public:
    JsonSerial();
    ~JsonSerial();

    void openSerialPort(const char* port);

    void recvJson();
    void sendJson();

    bool boutonAppuye(int indexBtn);
private:
    void recv();
    void send(const char* msg);

    // SERIAL
    asio::io_context* _context;
    asio::serial_port* _serial;
    asio::io_context::work* _work;
    std::thread* _runThread;

    char _read[JSON_BUFFER_SIZE]; // buffer dans lequel asio ecrit directement
    char _msg[JSON_BUFFER_SIZE]; // buffer dans lequel on inscrit le message complet
    char _send[JSON_BUFFER_SIZE];

    bool _recvInProgress;
    bool _readingMsg;
    bool _newData;
    int _ndx; // read index (ecriture dans _msg)

    bool _sendInProgress;

    // JSON
    nlohmann::json _json;
    std::chrono::steady_clock::time_point _lastsend;
};

#endif // JSONSERIAL_H!
