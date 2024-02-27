#ifndef JSON_H
#define JSON_H

#include <asio.hpp>
#include <iostream>

#define JSON_DATA_SIZE 1024

class JsonSerial {
public:
	JsonSerial();
	~JsonSerial();

	void openSerialPort(const char* port);
	size_t readSerial();
	void writeSerial(const char* json);

	void printData();
private:
	asio::io_context* _context;
	asio::serial_port* _serial;

	char _data[JSON_DATA_SIZE];
	size_t _length;
};

#endif // JSON_H!
