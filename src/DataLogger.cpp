#include "DataLogger.hpp"

DataLogger::DataLogger() {
    
}

bool DataLogger::init() {
    Serial.print("connecting to ");
    Serial.println(ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    return true;
}

bool DataLogger::sendDataToGoogleSpreadsheet(int temperature, int humidity)
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
        Serial.println("certificate doesn't match");
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
    String line = client.readStringUntil('\n');
    if (line.startsWith("{\"state\":\"success\"")) {
        Serial.println("esp32/Arduino CI successfull!");
    } else {
        Serial.println(line);
        Serial.println("esp32/Arduino CI has failed");
    }
    Serial.println("reply was:");
    Serial.println("==========");
    Serial.println(line);
    Serial.println("==========");
    Serial.println("closing connection");
    client.stop();

    return true;
} 