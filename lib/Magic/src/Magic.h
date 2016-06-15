//
// Created by java-xuhui on 2016/3/31.
//

#ifndef MAGIC_H
#define MAGIC_H
#define randomx(x) (rand()%x)

#include <FastLED.h>

#include "Action.h"
#include "P.h"
#include "EEPROMOperator.h"

class Magic{
private:
  CRGB *led;
  CRGB *color=new CRGB[6];
  CRGB *mask8=new CRGB[8];
  CRGB *mask12=new CRGB[12];
  CRGB *SHOW=new CRGB[54];

  Action *actions=new Action[56];
  int actionIndex=0;
  byte* cells;
  byte* cellMeM[5];
  byte numMeM=0;
  int memChoice=-1;
  unsigned long startTime,lastUpdate,nowTime,timeP,showTime,tmpTimeP;
  unsigned long timeTTT=0;
  byte circleStep,middleStep,surfaceStep,operatSide;
  bool cw;
  int circlePS,middlePS,surfacePS,maskRound;

  EEPROMOperator romOperator=EEPROMOperator();
protected:
  void rotationP(P *ps, bool cw,int size,int step);
  int getIndex(int face,int x,int y);
  int getIndex(int face,int i);
  CRGB getMask(CRGB ledi,CRGB maski);
public:
  Magic(CRGB *led);
  void setDefault();
  void clear(bool ok=true);
  void setMask8(CRGB *mask8=NULL);
  CRGB* getMask8();
  void setMask12(CRGB *mask12=NULL);
  CRGB* getMask12();
  void setColor(CRGB *color=NULL);
  CRGB* getColor();
  void setCirclePS(byte circlePS=3);
  byte getCirclePS();
  void setMiddlePS(byte middlePS=3);
  byte getMiddlePS();
  void setSurfacePS(byte surfacePS=2);
  byte getSurfacePS();
  void setMaskRound(byte maskRound=1);
  byte getMaskRound();
  void setTimeP(unsigned long timeP=500);
  unsigned long getTimeP();
  void rotationMiddle(int surface,bool cw=true,int step=1);
  void rotationSurface(int surface,bool cw=true,int step=1);
  void rotationCircle(int surface,bool cw=true,int step=1);

  void getLed();
  void update();
  void addAction(Action action);
  void showFace(int front,int down);
  void random(int i=20,unsigned long timeRandom=200);

  void save();
  void goBack();
  void choice();

  void OK(unsigned long time=500);
  void NOTOK(unsigned long time=500);
};

#endif //MAGIC_H
