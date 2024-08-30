// Monitor example for TWELITE with Arduino UNO R4: Receive data from App_Tag (ADC)

#include <Arduino.h>
#include "MWings.h"

const int RST_PIN = D11;
const int PRG_PIN = D12;
const int LED_PIN = D13;        // Use on-board LED as indicator

const uint8_t TWE_CHANNEL = 15;
const uint32_t TWE_APP_ID = 0x67726305;

void setup()
{
    // Initialize serial ports
    while (!Serial && millis() < 5000); // Wait for internal USB-UART
    Serial.begin(115200);
    Serial.println("Monitor example for TWELITE with Arduino UNO R4: App_Tag (ADC)");
    Serial1.begin(115200);

    // Initialize TWELITE
    if (Twelite.begin(Serial1,
                      LED_PIN, RST_PIN, PRG_PIN,
                      TWE_CHANNEL, TWE_APP_ID)) {
        Serial.println("Successfully initialized TWELITE");
    } else {
        Serial.println("Failed to initialize TWELITE");
    }

    // Attach an event handler to process packets from App_Tag (ADC)
    Twelite.on([](const ParsedAppTagAdcPacket& packet) {
        Serial.println("");
        Serial.print("Packet Sequence #: ");
        Serial.println(packet.u16SequenceNumber, DEC);
        Serial.print("Source Logical ID: 0x");
        Serial.println(packet.u8SourceLogicalId, HEX);
        Serial.print("Router Serial ID:  0x");
        Serial.println(packet.u32RouterSerialId, HEX);
        Serial.print("LQI:               ");
        Serial.println(packet.u8Lqi, DEC);
        Serial.print("Supply Voltage:    ");
        Serial.print(packet.u16SupplyVoltage, DEC); Serial.println(" mV");
        Serial.print("Analog Input:     ");
        Serial.print(" A1:"); Serial.print(packet.u16AiVoltage[0]); Serial.print(" mV");
        Serial.print(" A3:"); Serial.print(packet.u16AiVoltage[1]); Serial.print(" mV");
    });
}

void loop()
{
    // Update TWELITE
    Twelite.update();
}

/*
 * Copyright (C) 2024 Mono Wireless Inc. All Rights Reserved.
 * Released under MW-OSSLA-1J,1E (MONO WIRELESS OPEN SOURCE SOFTWARE LICENSE AGREEMENT).
 */
