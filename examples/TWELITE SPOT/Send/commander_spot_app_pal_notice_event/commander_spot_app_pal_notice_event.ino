// Commander example for TWELITE SPOT: Send 0x90 event command to App_PAL (NOTICE)

#include <Arduino.h>
#include "MWings.h"

const int RST_PIN = 5;
const int PRG_PIN = 4;
const int LED_PIN = 18;

const int8_t RX1_PIN = 16;
const int8_t TX1_PIN = 17;

const uint8_t TWE_CHANNEL = 15;
const uint32_t TWE_APP_ID = 0x67726305;
const uint8_t TWE_RETRY_COUNT = 2;
const uint8_t TWE_TX_POWER = 3;

const uint8_t TWE_TARGET_LID = 0x01;

AppPalNoticeEventCommand command;

void printCommand();
void printHelp();

void setup()
{
    // Initialize serial ports
    Serial.begin(115200);
    Serial.println("Commander example for TWELITE SPOT: App_PAL (NOTICE), Event ID");
    Serial2.begin(115200, SERIAL_8N1, RX1_PIN, TX1_PIN);

    // Initialize TWELITE
    Twelite.begin(Serial2,
                  LED_PIN, RST_PIN, PRG_PIN,
                  TWE_CHANNEL, TWE_APP_ID,
                  TWE_RETRY_COUNT, TWE_TX_POWER);

    // Prepare initial App_PAL command
    command.u8DestinationLogicalId = TWE_TARGET_LID;
    command.u8EventId = 0x00;

    // Print help message
    printHelp();
}

void loop()
{
    // Update TWELITE
    Twelite.update();

    // Process input
    if (Serial.available()) {
        int c = Serial.read();
        if ('0' <= c and c <= '9') {
            command.u8EventId = c - '0';
            Serial.print("Set event id to 0x");
            Serial.println(command.u8EventId, HEX);
        } else if ('a' <= c and c <= 'f') {
            command.u8EventId = c - 'a' + 0xA;
            Serial.print("Set event id to 0x");
            Serial.println(command.u8EventId, HEX);
        } else if ('A' <= c and c <= 'F') {
            command.u8EventId = c - 'A' + 0xA;
            Serial.print("Set event id to 0x");
            Serial.println(command.u8EventId, HEX);
        } else {
            switch (c) {
            case ' ': {
                if (Twelite.send(command)) {
                    Serial.println("Sent command below:");
                    printCommand();
                } break;
            }
            case 'h': {
                printHelp(); break;
            }
            default: break;
            }
        }
    }
}

void printCommand()
{
    Serial.print("Event ID: 0x");
    Serial.println(command.u8EventId, HEX);
    Serial.println("");
}

void printHelp()
{
    Serial.println("Keys:");
    Serial.println("Event ID: '0'-'9' / 'a'-'f' / 'A'-'F'");
    Serial.println("-----------------");
    Serial.println("Send: SPACE");
    Serial.println("Help: 'h'");
    Serial.println("");
}

/*
 * Copyright (C) 2023 Mono Wireless Inc. All Rights Reserved.
 * Released under MW-OSSLA-1J,1E (MONO WIRELESS OPEN SOURCE SOFTWARE LICENSE AGREEMENT).
 */
