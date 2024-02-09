/*
  Reads DMX data from channel 1

  By: Dryw Wade
  SparkFun Electronics
  Date: 10/3/2023
  License: GNU. See license file for more information but you can
  basically do whatever you want with this code.
  This example runs two servos and a number of LED's off of 5 DMX channels

  Feel like supporting open source hardware?
  Buy a board from SparkFun! https://www.sparkfun.com/products/15110

  Hardware Connections:
  Connect a Thing Plus board to the SparkFun DMX Shield, and connect a DMX XLR-3
  cable between the shield and another device that inputs DMX data. You can use
  a second board and shield running Example 1!
*/

// Include DMX library
#include <SparkFunDMX.h>
#include <Adafruit_NeoPixel.h>

#define LED 2
#define NUMPIXELS 1
Adafruit_NeoPixel pixels(NUMPIXELS, LED, NEO_GRB + NEO_KHZ800);

// Create DMX object
SparkFunDMX dmx;

// Create serial port to be used for DMX interface. Exact implementation depends
// on platform, this example is for the ESP32
HardwareSerial dmxSerial(0);

// Enable pin for DMX shield (Free pin on Thing Plus or Feather pinout)
uint8_t enPin = 4;
uint8_t txPin = 5;
uint8_t rxPin = 3;

// Number of DMX channels, can be up tp 512
uint16_t numChannels = 512;

void setup()
{
    delay(500);
    // SerialUSB.begin(115200);
    // SerialUSB.println("SparkFun DMX Example 2 - Input");

    // Begin DMX serial port
    dmxSerial.begin(DMX_BAUD, DMX_FORMAT, rxPin, txPin);

    // Begin DMX driver
    dmx.begin(dmxSerial, enPin, numChannels);

    // Set communication direction, which can be changed on the fly as needed
    dmx.setComDir(DMX_WRITE_DIR);

    // SerialUSB.println("DMX initialized!");
}

void loop()
{

    for (uint8_t i = 0; i < 256; i++) {
        dmx.writeByte(i, 1);
        pixels.setPixelColor(0, pixels.Color(10, 0, i));
        pixels.show();
        delay(5);
        dmx.update();
    }
}
