

#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#define USE_SERIAL Serial

WiFiMulti wifiMulti;
String mac_address;

void setup() {

    USE_SERIAL.begin(115200);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    wifiMulti.addAP("asu-m", "12345678");
    mac_address = WiFi.macAddress();

}

void loop() {
    // wait for WiFi connection
    if((wifiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        USE_SERIAL.print("[HTTP] begin...\n");
        // configure traged server and url
        http.begin("http://54.203.235.138:1234/getValue?mac="+ mac_address); //HTTP

        USE_SERIAL.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println(payload);
                setColors(payload.c_str());
                
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }

    delay(5000);
}


void setColors(String str_data)
{
  
  int firstCommaIndex = str_data.indexOf(',');
  int secondCommaIndex = str_data.indexOf(',', firstCommaIndex+1);
  String param0 = str_data.substring(0, firstCommaIndex);
  String param1 = str_data.substring(firstCommaIndex+1, secondCommaIndex);
  String param2 = str_data.substring(secondCommaIndex+1);

  float value0 = param0.toFloat();
  float value1 = param1.toFloat();
  float value2 = param2.toFloat();

    Serial.print(value0); 
    Serial.print(" ");   
    Serial.print(value1); 
    Serial.print(" ");     
    Serial.print(value2);
    Serial.println();


    // Now set colors here using value0, value1, value2.


    
}
