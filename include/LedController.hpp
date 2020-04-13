#pragma once

#include "Arduino.h"

#define GREEN_LED_PIN 21

enum ledEnum {
    all,
    green,
    //blue
};

/**
 * Class to control the LEDs of the ESP32.
 */
class LedController {
public:
    LedController() = delete;

    /**
     * Defines the LED pins as output.
     */
    static void init();

    static void setLed(ledEnum led, bool on);
    static void blinkLed(ledEnum led, uint8_t count, uint16_t onTimeMs, uint16_t offTimeMs);

private:

};
