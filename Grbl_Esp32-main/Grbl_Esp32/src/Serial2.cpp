#include "Serial2.h"
#include <Arduino.h>
#include "Grbl.h"

void initSerial2() {

    // Configure the UART2 port (Serial2)
    Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
    delay(1000);  // Wait for the serial port to initialize
    USE_SERIAL.println("initialised");
}

void sendMessage(const char* message) {
    // Send the message through Serial2
    Serial2.println(message);
    USE_SERIAL.println(message);
}
