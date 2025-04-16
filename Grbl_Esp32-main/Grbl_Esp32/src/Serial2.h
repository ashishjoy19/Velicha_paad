// Serial2Communication.h
#pragma once

// Define UART2 pins
#define RXD2 32
#define TXD2 22

// Function declarations
void initSerial2();
void sendMessage(const char* message);