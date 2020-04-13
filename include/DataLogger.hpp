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

    /**
     * @brief Initializes the data logger by connecting to the local wifi.
     */
    bool init();

    /**
     * @brief Transmits data to the previously defined Google Spreadsheet.
     * 
     * The time of the transfer is automatically logged (date & time).
     * 
     * @param temperature
     * @param humidity
     */
    bool sendDataToGoogleSpreadsheet(float temperature, float humidity);

    /**
     * @brief Converts a relative humidity (RH) value to absolute humidity.
     * 
     * Formula taken from here: https://carnotcycle.wordpress.com/2012/08/04/how-to-convert-relative-humidity-to-absolute-humidity/
     * @note The formula is accurate within 0.1% for values between -30°C and +35°C.
     * 
     * @param relativeHumidity Measured RH value
     * @param temperature Temperature (°C) that was measured when the RH value was taken
     */
    float convertToAbsoluteHumidity(float relativeHumidity, float temperature);

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
