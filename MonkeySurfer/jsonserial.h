#ifndef JSONSERIAL_H
#define JSONSERIAL_H

#include "asio/include/asio.hpp"
#include <chrono>
#include <iostream>
#include "json/json.hpp"
#include <thread>
#include "direction.h"
#include "nullstream.h"

#define BAUD_RATE 112500
#define START_MARKER '>'
#define END_MARKER '<'
#define JSON_BUFFER_SIZE 1024
#define SEND_DELAY 50

#define errout null /* "null" pour ignorer les erreurs, "std::cerr" pour les afficher */

class JsonSerial {
public:
    JsonSerial();
    ~JsonSerial();

    void openSerialPort(const char* port);

    void recvJson();
    void sendJson();

    void recvPrint();

    // Read
    bool boutonAppuye(int indexBtn);
    bool boutonMaintenu(int indexBtn);
    bool joystickMaintenu(Direction dir, bool repeat = false);
    bool accShake();

    // Write
    void lcd(const char* msg_row_1, const char* msg_row_2);
    void led(int numero);
    void bar(int numero);
    void vibration(bool vibre);
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
    nlohmann::json _recvjson;
    nlohmann::json _sendjson;
    std::chrono::steady_clock::time_point _lastsend;
};

#endif // JSONSERIAL_H!
