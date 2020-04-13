#pragma once

#include "Arduino.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>

// project
#include "Environment.hpp"

/**
 * Class to log temperature and humidity data in a google spreadsheet.
 */
class DataLogger {
public:
    DataLogger() = default;

    bool init();

    /**
     * Transmits data to the previously defined Google Spreadsheet.
     * The time of the transfer is automatically logged (date & time).
     * 
     * @param temperature
     * @param humidity
     */
    bool sendDataToGoogleSpreadsheet(float temperature, float humidity);

private:
    const char* ssid = env::wifi::ssid; ///< name of your wifi network
    const char* password = env::wifi::password; ///< wifi pasword
    const char* host = "script.google.com";
    const int httpsPort = 443;
    WiFiClientSecure client; ///< Use WiFiClientSecure class to create TLS connection
    // SHA1 fingerprint of the certificate, don't care with your GAS service
    const char* fingerprint = "46 B2 C3 44 9C 59 09 8B 01 B6 F9 BD 4C FB 00 74 91 2F EF F6";
    String gasId = env::gas::id; ///< your GAS service id
    int it;
    int ih;
};
