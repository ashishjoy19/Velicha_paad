#pragma once
#include<Arduino.h>

#define TX2 22
#define RX2 32

void initSerial2();

void sendMessage(const char* message);

bool waitforOK(unsigned long timeout);

bool waitForModMessage(unsigned long timeout);

void send_colour_data(uint32_t colour_code);