#include "affichageconsole.h"
#include <conio.h>

#include "jsonserial.h"

int main()
{
    JsonSerial js;
    const char* str = ">{\"test\": 2}<";

    js.openSerialPort("COM5");

    while (true) {
        js.writeSerial(str);

        js.readSerial();
        if (js.bytesAvailable()) {
            js.printData();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}
