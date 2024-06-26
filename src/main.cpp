//-----------------------------------------------
// Author: Trieu Le
// Email: lethanhtrieuk36@gmail.com
// Publish date: 29-Oct-2017
// Description: This code for demonstration send data from ESP32 into Google Spreadsheet
// Modifyed by Moz for Youtube changel logMaker360 for this video: https://youtu.be/fS0GeaOkNRw 24-02-2018
// update ssid, password and GAS_ID
//-----------------------------------------------

#include <Arduino.h>
#include "AdafruitSi7021Driver.hpp"
#include "DataLogger.hpp"
#include "SleepController.hpp"
#include "Wire.h" // i2c
#include "Parameters.hpp"
#include "LedController.hpp"

DataLogger dataLogger;
AdafruitSi7021Driver si7021Driver(&Wire);
SleepController sleepController;

float it = 0;
float ih = 0;
int secondsSinceBoot = 0;

void setup() 
{
    // initialize serial output
    Serial.begin(115200);
    Serial.println();
    Serial.println("Booted / Woken up");
    sleepController.analyzeBoot();
    Serial.println("In Project: Esp32TemperatureHumidityLogging");
    Serial.println("Starting setup");

    // initialize temperature & humidity sensor
    si7021Driver.begin(23, 18);  // sensor

    //connecting to the local wlan / internet
    while(!dataLogger.init()) {
        Serial.println("Connecting to Wifi failed, attempting again");
    };

    // set up Led pins
    LedController::init();

    Serial.println("Setup completed");

    // toggle LED shortly
    // LedController::blinkLed(ledEnum::green, 3, 50, 50);
}

void loop() 
{
    // sample values
    Serial.println("Sampling values");
    float h = si7021Driver.readRelativeHumidity();
    float t = si7021Driver.readTemperature();
    Serial.print("Temp = ");
    Serial.print(t);
    Serial.print(" HUM= ");
    Serial.println(h);
    it = (float) t;
    ih = (float) h;
    dataLogger.sendDataToGoogleSpreadsheet(it, ih);

    // check if it's time to sleep
    Serial.println("Check if it's time to sleep");
    Serial.println(String("Seconds since boot: ") + String(secondsSinceBoot));
    if(secondsSinceBoot >= parameters::desiredUpTimeInSeconds) {
        if(parameters::sleepTimeInSeconds > 0) {
            Serial.println(String("Going to sleep for ") + String(parameters::sleepTimeInSeconds) + String(" seconds"));
            sleepController.sleep(parameters::sleepTimeInSeconds);
            // next call will be setup()
        }
    }

    // wait sample time
    Serial.println(String("Waiting sampling time of ") +
                   String(parameters::samplingPeriodInSeconds) +
                   String(" seconds"));
    delay(parameters::samplingPeriodInSeconds * SECONDS_TO_MS);
    secondsSinceBoot += parameters::samplingPeriodInSeconds;
}
