#include <iostream>
#include <asio.hpp>
#include <json.hpp>
#include "affichageconsole.h"
#include <conio.h>


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

/* int main()
{
    Jeu j;
    Menu m;
    AffichageConsole a(&j, &m);

    while (m.getEtat() != Menu::EtatMenu::QUITTER) {
        if (m.getEtat() == Menu::EtatMenu::JEU) {
            a.afficherJeu();
            if (_kbhit() && _getch() == 'q') {
                m.setEtat(Menu::EtatMenu::PRINCIPAL);
                continue;
            }
        }
        else {
            m.update();
            a.afficherMenu();
        }
    }

}
*/
