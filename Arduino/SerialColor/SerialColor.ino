#include "FastLED.h"


//******** ONLY CHANGE THESE ******************
#define COLOR_ORDER GRB        //Shouldn't need changing - just incase your RGB channels change order
#define CHIPSET     WS2811    //Choose your chipset
#define NUM_LEDS    144         //No. of LEDs in your strip - 48led/m
#define BRIGHTNESS  255        //Overall brightness of the LEDs on a scale from 0(off)-255(max birghtness)
#define DATA_PIN 2  
#define DATA_CLK 4

// Define the array of leds
CRGB leds[NUM_LEDS];
CRGB    gColor =  CRGB::Black;

void setup() { 
      
    Serial.begin(115200);        // connect to the serial port
    

    FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip ); 
    FastLED.setBrightness(BRIGHTNESS);

    fill_solid(leds, NUM_LEDS, gColor);
    FastLED.show();
}

void loop() { 

//  if(Serial.available()){
//     byte header = Serial.read();
//      if(header == 'c')
//      {
//         while (Serial.available() > 0) {
//            int val = Serial.read();
//         }
//         fill_solid(leds, NUM_LEDS, CRGB::Red);
//         FastLED.show();
//         Serial.println("Color received");
//      }
//       else if(header == '?')
//      {
//           Serial.print("OK"); 
//      }
//  } 

    // if there's any serial available, read it:
    while (Serial.available() > 0) {
     byte header = Serial.read();
      if(header == 'c')
      {
          fill_solid(leds, NUM_LEDS, CRGB::Red);
          FastLED.show(); 
          byte red = Serial.read();
          byte green = Serial.read();
          byte blue = Serial.read();

          // look for the newline. That's the end of your sentence:
          if (Serial.read() == '\n') {
            // constrain the values to 0 - 255 
      
             gColor.r = red;
             gColor.g = green;
             gColor.b = blue;
      
             fill_solid(leds, NUM_LEDS, gColor);
             FastLED.show(); 

//              while (Serial.available() > 0) {
//                int val = Serial.read();
//              }

             break;
          }
          }
          else if(header == '?')
          {
               Serial.print("OK"); 
               break;
          }
     
     }
}
