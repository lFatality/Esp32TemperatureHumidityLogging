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

DataLogger dataLogger;
AdafruitSi7021Driver si7021Driver(&Wire);
SleepController sleepController;

float it = 0;
float ih = 0;
int msSinceBoot = 0;

void setup() 
{
    // initialize serial output
    Serial.begin(115200);
    sleepController.analyzeBoot();
    Serial.println();
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
    float h = si7021Driver.readHumidity();
    float t = si7021Driver.readTemperature();
    Serial.print("Temp = ");
    Serial.print(t);
    Serial.print(" HUM= ");
    Serial.println(h);
    it = (float) t;
    ih = (float) h;
    dataLogger.sendDataToGoogleSpreadsheet(it, ih);

    delay(5000);
    msSinceBoot += 5000;
    // sample values for 30s, then go into deep sleep for 1 minute
    if(msSinceBoot >= 30000) {
        sleepController.sleep(60);
        // next call will be setup()
    }
}
