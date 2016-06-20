#include <FastLED.h>
#include "Magic.h"
#include "MagicOperator.h"

#define LED_PIN     2
#define COLOR_ORDER RGB
#define CHIPSET     WS2811
#define NUM_LEDS    54

CRGB leds[NUM_LEDS];

const byte ROWS = 6; //four rows
const byte COLS = 9; //three columns
char keys[6][9] = {
  {1, 2, 3, 4, 5, 6, 7, 8, 9},
  {10, 11, 12, 13, 14, 15, 16, 17,18},
  {19, 20, 21, 22, 23, 24, 25, 26,27},
  {28, 29, 30, 31, 32, 33, 34, 35,36},
  {37, 38, 39, 40, 41, 42, 43, 44,45},
  {46, 47, 48, 49, 50, 51, 52, 53,54},
};
byte rowPins[ROWS] = {32, 33, 34, 35, 36, 37}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {22, 23, 24, 25, 26, 27, 28, 29, 30}; //connect to the column pinouts of the kpd
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

Magic magic=Magic(leds);
MagicOperator magicOperator=MagicOperator(&magic,&kpd);
unsigned long startTimeF,startTimeC;
int fram;

void setup(){
  Serial.begin(9600);
  FastLED.addLeds<CHIPSET,LED_PIN,COLOR_ORDER>(leds,NUM_LEDS).setCorrection(TypicalLEDStrip);
  magic.getLed();
  FastLED.show();
  startTimeF=millis();
  startTimeC=millis();
  // magic.addAction(Action(0));
  // magic.addAction(Action(1));
  // magic.addAction(Action(4,true,false));
  magicOperator.setFace(1, 4);
  // magic.addAction(magicOperator.getAction(0+1*9));
  // magic.addAction(magicOperator.getAction(1+1*9));
  // magic.addAction(magicOperator.getAction(2+1*9));
  // magic.addAction(magicOperator.getAction(3+1*9));
  // magic.addAction(magicOperator.getAction(4+1*9));
  // magic.addAction(magicOperator.getAction(5+1*9));
  // magic.addAction(magicOperator.getAction(6+1*9));
  // magic.addAction(magicOperator.getAction(7+1*9));
  // magic.addAction(magicOperator.getAction(8+1*9));
  Serial.println("hello");
}

void loop(){
  magicOperator.update();
  if((millis()-startTimeC>1000/300)){
    magic.update();
    startTimeC=millis();
  }
  if((millis()-startTimeF>1000/60)){
    magic.getLed();
    FastLED.show();
    // Serial.println(fram);
    if(60<=++fram){
      fram=0;
      startTimeF=millis();
    }
  }
}
