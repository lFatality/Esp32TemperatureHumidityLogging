#include "LedController.hpp"
#include "pins_arduino.h"

void LedController::init() {
  pinMode(GREEN_LED_PIN, OUTPUT);
}

void LedController::setLed(ledEnum led, bool on) {
    switch (led) {
    //case ledEnum::blue:
      // the blue led can not be controlled, it will switch off if you use the battery interface for power supply instead of USB
      // https://github.com/LilyGO/TTGO-T8-ESP32/issues/3
      //on ? digitalWrite(BLUE_LED_PIN, HIGH) : digitalWrite(BLUE_LED_PIN, LOW);
    //  break;
    case ledEnum::green:
      on ? digitalWrite(GREEN_LED_PIN, HIGH) : digitalWrite(GREEN_LED_PIN, LOW);
      break;
    case ledEnum::all:
      on ? digitalWrite(GREEN_LED_PIN, HIGH) : digitalWrite(GREEN_LED_PIN, LOW);
      //on ? digitalWrite(BLUE_LED_PIN, HIGH) : digitalWrite(BLUE_LED_PIN, LOW);
      break;

    default:
      break;
    }
}

void LedController::blinkLed(ledEnum led, uint8_t count, uint16_t onTimeMs, uint16_t offTimeMs) {
    for(int i=0; i<count; ++i) {
        LedController::setLed(led, true);
        delay(onTimeMs);
        LedController::setLed(led, false);
        if(i == count-1) {
          // in the last iteration we dont need to wait
          continue;
        }
        delay(offTimeMs);
    }
}

