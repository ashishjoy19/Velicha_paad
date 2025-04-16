#include "Serial2.h"
#include "Arduino.h"

void initSerial2() {

    // Configure the UART2 port (Serial2)
    Serial2.begin(9600, SERIAL_8N1, RX2, TX2);

    // Give some time for the serial to initialize
    delay(10000);

    Serial.println("initialised");

    // Wait for "ok" message from Serial2
    if (waitForModMessage(10000)) { // 5000ms timeout
        Serial.println("Received multipen module from Serial2");
        Serial2.println("ok");
    } else {
        Serial.println("Timeout waiting for 'ok' from Serial2");
    }
    
    // Initialize Serial2 for RGB LED communication
    Serial2.begin(115200);  // Use the same baud rate as your end effector expects
}

void sendMessage(const char* message) {
    // Send the message through Serial2
    Serial2.println(message);
    Serial.println(message);
    while (waitforOK(10000))
    {
        Serial.println("waiting");
    }
    // Print the message to the serial monitor for debugging
    Serial.println("Sent");
    if (strcmp(message, "M28") != 1) {
        while (waitforOK(10000))
        {
            Serial.println("waiting");
        }
        Serial.println("ok received");
        return;
    }
}

bool waitforOK(unsigned long timeout) {
    unsigned long startMillis = millis();
    String receivedMessage = "";

    while (millis() - startMillis < timeout) {
        while (Serial2.available()) {
            char ch = Serial2.read();
            receivedMessage += ch;
            if (receivedMessage.endsWith("ok")) {
                return false;
            }
        }
    }
    return true;
}

bool waitForModMessage(unsigned long timeout) {
    unsigned long startMillis = millis();
    String receivedMessage = "";

    while (millis() - startMillis < timeout) {
        while (Serial2.available()) {
            char ch = Serial2.read();
            receivedMessage += ch;
            if (receivedMessage.endsWith("multipen module")) {
                return true;
            }
        }
    }
    return false;
}

void send_colour_data(uint32_t colour_code) {
    // Format the color code as a hexadecimal string
    char buffer[20];
    sprintf(buffer, "M202 O%06X", colour_code);
    
    // Print debug messages to Serial so we can monitor what's happening
    Serial.print("DEBUG: Sending RGB LED command: ");
    Serial.println(buffer);
    Serial.print("DEBUG: Colour code (decimal): ");
    Serial.println(colour_code);
    Serial.print("DEBUG: Colour code (hex): 0x");
    Serial.println(colour_code, HEX);
    
    // Send the formatted command to Serial2
    Serial2.println(buffer);
    
    // Wait for acknowledgment
    if (!waitforOK(5000)) {
        Serial.println("DEBUG: Received OK response from RGB LED controller");
    } else {
        Serial.println("DEBUG: Timeout waiting for OK response from RGB LED controller");
    }
}