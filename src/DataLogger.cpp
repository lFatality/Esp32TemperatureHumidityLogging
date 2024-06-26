#include "DataLogger.hpp"
#include "Arduino.h"

bool DataLogger::init() {
    Serial.print("connecting to ");
    Serial.println(ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    int ms_waited = 0;
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        ms_waited += 500;
        if(ms_waited >= 5000) {
            // doesnt work, attempt again from the start
            return false;
        }
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    return true;
}

bool DataLogger::sendDataToGoogleSpreadsheet(float temperature, float humidity)
{
    client.flush();
    Serial.print("connecting to ");
    Serial.println(host);
    if (!client.connect(host, httpsPort)) {
        Serial.println("connection failed");
        return false;
    }

    if (client.verify(fingerprint, host)) {
        Serial.println("certificate matches");
    } else {
        Serial.println("certificate doesn't match (should be fine, worked even with this error)");
    }
    String string_temperature =  String(temperature, DEC); 
    String string_humidity =  String(humidity, DEC); 
    String url = "/macros/s/" + gasId + "/exec?temperature=" + string_temperature + "&humidity=" + string_humidity;
    Serial.print("requesting URL: ");
    Serial.println(url);

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
            "Host: " + host + "\r\n" +
            "User-Agent: BuildFailureDetectorESP32\r\n" +
            "Connection: close\r\n\r\n");

    Serial.println("request sent");
    while (client.connected()) {
        String line = client.readStringUntil('\n');
    if (line == "\r") {
        Serial.println("headers received");
        break;
    }
    }
    //String test = client.readString();
    //Serial.println(test);
    String line = client.readStringUntil('\n');
    if (line.startsWith("{\"state\":\"success\"")) {
        Serial.println("esp32/Arduino CI successfull!");
    } else {
        Serial.println(line);
        Serial.println("esp32/Arduino CI has failed (probably caused by wrong interpretation of result)");
    }
    Serial.println("reply was:");
    Serial.println("==========");
    Serial.println(line);
    Serial.println("==========");
    Serial.println("closing connection");
    client.stop();

    return true;
}

float DataLogger::convertToAbsoluteHumidity(float relativeHumidity, float temperature) {
    return (6.112 * std::pow(EULER, (17.67*temperature)/(temperature+243.5))*relativeHumidity*2.1674)/(273.15+temperature);
}