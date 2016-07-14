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
  byte* cellMem[5];
  byte numMeM=0;
  int memChoice=-1;
  unsigned long startTime,lastUpdate,nowTime,timeP,showTime,tmpTimeP;
  unsigned long timeTTT=0;
  unsigned long standbyTime;
  byte circleStep,middleStep,surfaceStep,operatSide;
  bool cw;
  byte circlePS,middlePS,surfacePS,maskRound;

  EEPROMOperator rom=EEPROMOperator();
protected:
  void rotationP(P *ps, bool cw,int size,int step);
  int getIndex(int face,int x,int y);
  int getIndex(int face,int i);
  CRGB getMask(CRGB ledi,CRGB maski);
public:
  Magic(CRGB *led);
  void setFromMem();
  void setDefault();

  void setCell(byte *cell=NULL,bool fromMem=false);
  byte* getCell();
  void setMemDefault();
  void setMemFromMem();
  void saveMem();

  void setMask8(CRGB *mask8=NULL,bool fromMem=false);
  CRGB* getMask8();
  void setMask12(CRGB *mask12=NULL,bool fromMem=false);
  CRGB* getMask12();
  void setColor(CRGB *color=NULL,bool fromMem=false);
  CRGB* getColor();
  void setCirclePS(byte circlePS=3,bool fromMem=false);
  byte getCirclePS();
  void setMiddlePS(byte middlePS=3,bool fromMem=false);
  byte getMiddlePS();
  void setSurfacePS(byte surfacePS=2,bool fromMem=false);
  byte getSurfacePS();
  void setMaskRound(byte maskRound=1,bool fromMem=false);
  byte getMaskRound();
  void setTimeP(unsigned long timeP=500,bool fromMem=false);
  unsigned long getTimeP();
  void setStandbyTime(unsigned long standbyTime=10000,bool fromMem=false);
  unsigned long getStandbyTime();

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
static byte animation[54]={
    3,3,3,
    0,3,0,
    0,3,0,

    3,0,3,
    3,3,3,
    3,0,3,

    3,0,3,
    3,3,0,
    3,0,3,

    3,3,3,
    3,3,3,
    3,3,3,

    4,4,4,
    4,4,4,
    4,4,4,
    5,5,5,
    5,5,5,
    5,5,5,
};
#endif //MAGIC_H
