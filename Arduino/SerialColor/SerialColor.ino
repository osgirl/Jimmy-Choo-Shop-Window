#include "FastLED.h"


//******** ONLY CHANGE THESE ******************
#define COLOR_ORDER GRB        //Shouldn't need changing - just incase your RGB channels change order
#define CHIPSET     WS2811    //Choose your chipset
#define NUM_LEDS    144         //No. of LEDs in your strip - 48led/m
#define BRIGHTNESS  255        //Overall brightness of the LEDs on a scale from 0(off)-255(max birghtness)
#define DATA_PIN 2  
#define DATA_CLK 4

enum patterns {
  SOLID,
  SINELON, 
  NONE
};

// Define the array of leds
CRGB leds[NUM_LEDS];
CRGB    gColor =  CRGB::Black;
int     currentPattern = NONE;



void setup() { 
      
    Serial.begin(115200);        // connect to the serial port
    

    FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip ); 
    FastLED.setBrightness(BRIGHTNESS);

    fill_solid(leds, NUM_LEDS, gColor);
    FastLED.show();
}

void loop()
{ 
  updateSerial();
  updateLeds();
   
}

void updateLeds()
{
   switch (currentPattern) 
   {
        case SOLID:
            fill_solid(leds, NUM_LEDS, gColor);
            break;
        case SINELON:
            //fill_solid(leds, NUM_LEDS, CRGB::Red);
            sinelon();
            break; 
   }
    
    FastLED.show(); 
    
}
void updateSerial()
{
   // if there's any serial available, read it:
    while (Serial.available() > 0) 
    {
       byte header = Serial.read();
        if(header == 'c')
        {
            byte red = Serial.read();
            byte green = Serial.read();
            byte blue = Serial.read();
            
            // look for the newline. That's the end of your sentence:
            if (Serial.read() == '\n')
            {
               gColor.setRGB( red, green, blue);
            }
         }
         else if(header == '?')
         {
              Serial.print("OK"); 
         }
         else if(header == 'd')
         {
              currentPattern = SINELON;
         }
         else if(header == 's')
         {
              currentPattern = SOLID;
         }

      }
}
void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = beatsin16(20,0,NUM_LEDS);
  //leds[pos] += CHSV( 255, 255, 192);
  leds[pos] += gColor;
}
