#include "affichageconsole.h"
#include <conio.h>

#include "jsonserial.h"

int main()
{
    JsonSerial js;

    js.openSerialPort("COM5");
    js.setJson();

    while (true) {
        js.sendJson();
        js.recvJson();
    }
}
