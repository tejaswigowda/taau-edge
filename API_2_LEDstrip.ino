//httpClient-controller

//LED stuff
#include <FastLED.h>
#include "heltec.h"

#define NUM_LEDS  18
#define LED_PIN   2

CRGB leds[NUM_LEDS];

uint8_t colorIndex[NUM_LEDS];
uint8_t whichPalette = 0;

// Gradient palette "girlcat_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/rc/tn/girlcat.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.
//greens gradient
DEFINE_GRADIENT_PALETTE( greenish_gp ) {
    0, 173,229, 51,
   73, 139,199, 45,
  140,  46,176, 37,
  204,   7, 88,  5,
  255,   0, 24,  0};

//yello gradient
// Gradient palette "bhw1_07_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_07.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 8 bytes of program space.

DEFINE_GRADIENT_PALETTE( yellow_gp ) {
    0, 232, 65,  1,
  255, 229,227,  1};

//red gradient
// Gradient palette "cw5_068_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/cw/5/tn/cw5-068.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 8 bytes of program space.

DEFINE_GRADIENT_PALETTE( red_gp ) {
    0, 203, 21,  1,
  255,  83,  1,  2};
//sunset
// Gradient palette "Sunset_Real_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Sunset_Real.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE( Sunset_Real_gp ) {
    0, 120,  0,  0,
   22, 179, 22,  0,
   51, 255,104,  0,
   85, 167, 22, 18,
  135, 100,  0,103,
  198,  16,  0,130,
  255,   0,  0,160};


/*
DEFINE_GRADIENT_PALETTE( greenblue_gp ) {
    0,    0,  194,  255,     //light blue
   46,    3,    0,  246,     //dark blue
  176,   55,  222,   70,     //bright green
  255,    0,  194,  255      //light blue
};

DEFINE_GRADIENT_PALETTE( orangepink_gp ) {
    0,  255,  100,    0,     //orange
   90,  255,    0,  255,     //magenta
  150,  255,  100,    0,     //orange
  255,  255,  100,    0      //orange
};

DEFINE_GRADIENT_PALETTE( browngreen_gp ) {
    0,    6,  255,    0,     //green
   71,    0,  255,  153,     //bluegreen
  122,  200,  200,  200,     //gray
  181,  110,   61,    6,     //brown
  255,    6,  255,    0      //green
};
*/
CRGBPalette16 currentPalette(Sunset_Real_gp);
CRGBPalette16 targetPalette(greenish_gp);
//


#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#define USE_SERIAL Serial

WiFiMulti wifiMulti;
String mac_address;

void setup() {

//LED setup
FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);

  Serial.begin(57600);

  //Fill the colorIndex array with random numbers
  for (int i = 0; i < NUM_LEDS; i++) {
    colorIndex[i] = random8();
  }
//
    USE_SERIAL.begin(115200);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    wifiMulti.addAP("58B233", "72ULAEG386681");
    mac_address = WiFi.macAddress();

}

//wifi stuff
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

    delay(3000);
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

  



  // map the sensor range to a range of 3 color options:
   //int whichPalette = map(value0, case 0 , sensorMax, , );


  if (value0 < 0 || value0 > 100) {
    // Print an error
  }
  else if (value0 <= 20) { // Between 80 and 100
    targetPalette = greenish_gp;
     
  }
  else if (value0 <= 40) {    // Between 20 and 80

    targetPalette = yellow_gp;
        
  }
  else if (value0 <= 100){  // Anything that doesn't match the above cases
    targetPalette = red_gp;
      

  }

  currentPalette = targetPalette;
  
  // nblendPaletteTowardPalette( currentPalette, targetPalette, 200 );

// Color each pixel from the palette using the index from colorIndex[]
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette(currentPalette, colorIndex[i]);
  }
    FastLED.show();


/*

  EVERY_N_SECONDS(5) {
    whichPalette++;
    if (whichPalette > 2) whichPalette = 0;
    Serial.println(currentPalette[0]);
    FastLED.show();
 }


 EVERY_N_MILLISECONDS(5){
    for (int i = 0; i < NUM_LEDS; i++) {
      colorIndex[i]++;
}

 }
*/
}
