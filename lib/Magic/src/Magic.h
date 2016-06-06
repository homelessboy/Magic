//
// Created by java-xuhui on 2016/3/31.
//

#ifndef MAGIC_H
#define MAGIC_H
#include <FastLED.h>
#include "P.h"

class Magic{
protected:
  CRGB *color=new CRGB[6];
  int cells[54];
  void rotationP(P *ps, bool cw,int size,int step);
  int getIndex(int face,int x,int y);
  int getIndex(int face,int i);
public:
  Magic(CRGB *color);
  Magic();
  void rotationMiddle(int surface,bool cw=true,int step=1);
  void rotationSurface(int surface,bool cw=true,int step=1);
  void rotationCircle(int surface,bool cw=true,int step=1);
  void setColor(CRGB *color);
  void getLed(CRGB *led);
};

#endif //MAGIC_H
