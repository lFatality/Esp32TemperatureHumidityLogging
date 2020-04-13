#include <Arduino.h>

// spreadsheet: spreadsheet: https://docs.google.com/spreadsheets/d/1Vyy4qgzp645pBN_VU812eClJVZJIYqi_M7j1ywWp0Tw/edit#gid=0
// execute google script: https://script.google.com/macros/s/AKfycbxh0KWfIYso5BDSDKgFchY8PHbHADLUEGQ_YH0rbknq3a9M5w/exec?temperature=20&humidity=48

//-----------------------------------------------
// Author: Trieu Le
// Email: lethanhtrieuk36@gmail.com
// Publish date: 29-Oct-2017
// Description: This code for demonstration send data from ESP32 into Google Spreadsheet
// Modifyed by Moz for Youtube changel logMaker360 for this video: https://youtu.be/fS0GeaOkNRw 24-02-2018
// update ssid, password and GAS_ID
//-----------------------------------------------

#include "AdafruitSi7021Driver.hpp"
#include "DataLogger.hpp"
#include "SleepController.hpp"
#include "Wire.h" // i2c
#include "Parameters.hpp"

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
    si7021Driver.begin();  // sensor

    //connecting to the local wlan / internet
    while(!dataLogger.init()) {
        Serial.println("Connecting to Wifi failed, attempting again");
    };

    Serial.println("Setup completed");
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
