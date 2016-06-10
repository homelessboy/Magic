//
// Created by java-xuhui on 2016/3/31.
//

#ifndef MAGIC_H
#define MAGIC_H
#include <FastLED.h>

#include "Action.h"
#include "P.h"

class Magic{
private:
  CRGB *color=new CRGB[6];
  CRGB *mask8=new CRGB[8];
  CRGB *mask12=new CRGB[12];
  Action *actions=new Action[56];
  int actionIndex=0;
  int cells[54];
  unsigned long startTime,lastUpdate,nowTime,timeP;
  int circleStep,middleStep,surfaceStep,operatSide;
  bool cw;
  int circlePS,middlePS,surfacePS,maskRound;
protected:
  void rotationP(P *ps, bool cw,int size,int step);
  int getIndex(int face,int x,int y);
  int getIndex(int face,int i);
  CRGB getMask(CRGB ledi,CRGB maski);
public:
  Magic(CRGB *color,CRGB *mask8,CRGB *mask12,int circlePS=3,int middlePS=3,int surfacePS=2,int maskRound=1,unsigned long timeP=500);
  Magic();
  void setMask8(CRGB *mask8);
  void setMask12(CRGB *mask12);
  void setCirclePS(int circlePS);
  void setMiddlePS(int middlePS);
  void setSurfacePS(int surfacePS);
  void setMaskRound(int maskRound);
  void setTimeP(unsigned long timeP);
  void rotationMiddle(int surface,bool cw=true,int step=1);
  void rotationSurface(int surface,bool cw=true,int step=1);
  void rotationCircle(int surface,bool cw=true,int step=1);
  void setColor(CRGB *color);
  void getLed(CRGB *led);
  void update();
  void addAction(Action action);
  void showFace(int front,int down);
};

#endif //MAGIC_H
