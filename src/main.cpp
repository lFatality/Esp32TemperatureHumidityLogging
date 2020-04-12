#include <Arduino.h>

// spreadsheet: spreadsheet: https://docs.google.com/spreadsheets/d/1Vyy4qgzp645pBN_VU812eClJVZJIYqi_M7j1ywWp0Tw/edit#gid=0
// google script: https://script.google.com/macros/s/AKfycbxh0KWfIYso5BDSDKgFchY8PHbHADLUEGQ_YH0rbknq3a9M5w/exec?temperature=20&humidity=48

//-----------------------------------------------
// Author: Trieu Le
// Email: lethanhtrieuk36@gmail.com
// Publish date: 29-Oct-2017
// Description: This code for demonstration send data from ESP32 into Google Spreadsheet
// Modifyed by Moz for Youtube changel logMaker360 for this video: https://youtu.be/fS0GeaOkNRw 24-02-2018
// update ssid, password and GAS_ID
//-----------------------------------------------

//#include<DHT.h>
#include "DataLogger.hpp"

DataLogger dataLogger;

#define D2 1
#define DHT11 2

#define DHTPIN D2
#define DHTTYPE DHT11

int it = 0;
int ih = 0;

class DHT {
public:
    DHT(uint8_t pin, uint8_t type) {};

    void begin() {

    }

    int readTemperature() {
    static int val = 0.0;
    val = val+1;
    return val;
    }

    int readHumidity() {
    static int val = 0.0;
    val = val+2;
    return val;
    }  

};

void sendData(int tem, int hum);

DHT dht(DHTPIN, DHTTYPE);

void setup() 
{
    // initialize serial output
    Serial.begin(115200);
    Serial.println();
    Serial.println("In Project: Esp32TemperatureHumidityLogging");

    // initialize temperature & humidity sensor
    dht.begin();  // sensor

    //connecting to the local wlan / internet
    dataLogger.init();
}

void loop() 
{
    
    int h = dht.readHumidity();
    int t = dht.readTemperature();
    Serial.print("Temp = ");
    Serial.print(t);
    Serial.print(" HUM= ");
    Serial.println(h);
    it = (int) t;
    ih = (int) h;
    dataLogger.sendDataToGoogleSpreadsheet(it, ih);

    delay(5000);
}
