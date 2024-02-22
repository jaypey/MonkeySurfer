#include <iostream>
#include <asio.hpp>
#include <json.hpp>

int main()
{
	try {
		asio::io_context io_context;
		asio::serial_port serial(io_context, "COM4");

		serial.set_option(asio::serial_port_base::baud_rate(9600));

		char data[1024];

		while (true) {
			size_t length = serial.read_some(asio::buffer(data, sizeof(data)));
			std::cout.write(data, length);
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	system("pause");
}
