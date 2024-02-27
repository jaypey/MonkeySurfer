#include "jsonserial.h"

JsonSerial::JsonSerial() {
	_context = nullptr;
	_serial = nullptr;

	for (int i = 0; i < JSON_DATA_SIZE; i++)
		_data[i] = 0;
	_length = 0;
}

JsonSerial::~JsonSerial() {
	delete _context;
	delete _serial;
}

void JsonSerial::openSerialPort(const char* port) {
	try {
		_context = new asio::io_context;
		_serial = new asio::serial_port(*_context, port);

		_serial->set_option(asio::serial_port_base::baud_rate(9600));
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

size_t JsonSerial::readSerial() {
	if (!_context || !_serial) {
		std::cout << "Les donnees du port serial ne peuvent pas etre lues, le port serial doit etre ouvert." << std::endl;
		return 0;
	}

	return _length = _serial->read_some(asio::buffer(_data, sizeof(_data)));
}

void JsonSerial::writeSerial(const char* json) {
	if (!_context || !_serial) {
		std::cout << "Aucune donnee ne peut etre ecrite, le port serial doit etre ouvert." << std::endl;
		return;
	}

	_serial->write_some(asio::buffer(json, sizeof(json)));
}

void JsonSerial::printData() {
	std::cout.write(_data, _length);
}
