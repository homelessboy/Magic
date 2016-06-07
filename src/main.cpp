#include <FastLED.h>
#include "Magic.h"

#define LED_PIN     2
#define COLOR_ORDER RBG
#define CHIPSET     WS2811
#define NUM_LEDS    54

CRGB leds[NUM_LEDS];

Magic magic=Magic();
unsigned long startTimeF,startTimeC;
int fram;

void setup(){
  Serial.begin(9600);
  FastLED.addLeds<CHIPSET,LED_PIN,COLOR_ORDER>(leds,NUM_LEDS).setCorrection(TypicalLEDStrip);
  magic.getLed(leds);
  FastLED.show();
  startTimeF=millis();
  startTimeC=millis();
  magic.addAction(Action(0));
  magic.addAction(Action(1));
  magic.addAction(Action(4,true,false));
}

void loop(){
  if((millis()-startTimeC>1000/300)){
    magic.update();
    startTimeC=millis();
  }
  if((millis()-startTimeF>1000/60)){
    magic.getLed(leds);
    FastLED.show();
    // Serial.println(fram);
    if(60<=++fram){
      fram=0;
      startTimeF=millis();
    }
  }
}
