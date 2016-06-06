//
// Created by java-xuhui on 2016/3/31.
//
#include "Magic.h"

void Magic::rotationP(P *ps, bool cw, int size, int step) {
  while (step-- > 0) {
    P p = ps[0];
    int tmp = cells[p.getIndex()];
    for (int i = 1; i < size; i++) {
      P next;
      if (!cw) {
        next = ps[i];
      } else {
        next = ps[size - i];
      }
      cells[p.getIndex()] = cells[next.getIndex()];
      p = next;
    }
    cells[p.getIndex()] = tmp;
  }
}

int Magic::getIndex(int face, int x, int y) {
  return face * 9 + x * 3 + y;
}

int Magic::getIndex(int face, int i) {
  return face * 9 + i;
}

Magic::Magic(CRGB *color){
  this->color=color;
  for(int i=0;i<6;i++){
    for(int j=0;j<9;j++){
      cells[getIndex(i, j)]=i;
    }
  }
}

Magic::Magic(){
  this->color=new CRGB[6];
  color[0]=CRGB(0,0,10);
  color[1]=CRGB(0,10,0);
  color[2]=CRGB(0,10,10);
  color[3]=CRGB(10,0,0);
  color[4]=CRGB(10,0,10);
  color[5]=CRGB(10,10,0);
  for(int i=0;i<6;i++){
    for(int j=0;j<9;j++){
      cells[getIndex(i, j)]=i;
    }
  }
}

void Magic::rotationMiddle(int surface, bool cw, int step) {
  rotationP(MIDDLE[surface], cw, 12, step);
}

void Magic::rotationSurface(int surface, bool cw, int step) {
  rotationP(SURFACE[surface], cw, 8, step);
}

void Magic::rotationCircle(int surface, bool cw, int step) {
  rotationP(CIRCLE[surface], cw, 12, step);
}

void Magic::setColor(CRGB *color){
  this->color=color;
}
void Magic::getLed(CRGB *led){
  for(int i=0;i<54;i++){
    led[i]=color[cells[i]];

  }
}
