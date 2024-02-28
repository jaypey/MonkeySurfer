#include "affichageconsole.h"
#include <conio.h>

#include "jsonserial.h"

int main()
{
    JsonSerial js;
    const char* str = ">{\"btnAppuye\": true}<";

    auto begin = std::chrono::steady_clock::now();

    js.openSerialPort("COM5");

    while (true) {
        // Ecriture
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - begin);
        if (elapsed.count() >= 200) {
            js.writeSerial(str);
            begin = std::chrono::steady_clock::now();
        }

        // Lecture
        js.readSerial();
        if (js.msgAvailable()) {
            js.printData();
        }
    }
}
