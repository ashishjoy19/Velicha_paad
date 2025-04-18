#include "Serial2.h"
#include <Arduino.h>
#include "Grbl.h"

void initSerial2() {

    // Configure the UART2 port (Serial2)
    Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
    delay(1000);  // Wait for the serial port to initialize
}

void sendMessage(const char* msg) {
    grbl_send(CLIENT_SERIAL, msg);
    Serial2.print(msg);
}
