#include <ArduinoJson.h>



void setup() {
    Serial.begin(9600);
    
    const char* input = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\": [48.75,2.30]}"; // input stream

    StaticJsonDocument<256> doc; // 256 bytes just an arbitrary number.. in a real use case we should use arduinoJson assistant this will tell us our mem size 

    DeserializationError err = deserializeJson(doc, input);// call the derializationJson() and checked for error

    if (err) {
      Serial.print("ERROR: ");
      Serial.print(err.c_str());
      return;
    }

// extrating the values
  const char* sensor = doc["sensor"];
  long time = doc["time"];
  float lat = doc["data"][0];
  float lon = doc["data"][1];

  Serial.println(sensor);
  Serial.println(time);
  Serial.println(lat, 6);
  Serial.println(lon, 6);

  }


void loop() {
  // put your main code here, to run repeatedly:

}
