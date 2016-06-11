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

CRGB Magic::getMask(CRGB ledi,CRGB maski){
  if(maski.r==0 && maski.g==0 && maski.b==0){
    return ledi;
  }else{
    return maski;
  }
}

Magic::Magic(CRGB *color,CRGB *mask8,CRGB *mask12,int circlePS,int middlePS,int surfacePS,int maskRound,unsigned long timeP){
  this->color=color;
  this->mask8=mask8;
  this->mask12=mask12;
  this->circlePS=circlePS;
  this->middlePS=middlePS;
  this->surfacePS=surfacePS;
  this->maskRound=maskRound;
  this->timeP=timeP;
  circleStep=0;
  middleStep=0;
  surfaceStep=0;
  operatSide=-1;
  for(int i=0;i<6;i++){
    for(int j=0;j<9;j++){
      cells[getIndex(i, j)]=i;
    }
  }
}

Magic::Magic(){
//  this->color=new CRGB[6];
  circleStep=0;
  middleStep=0;
  surfaceStep=0;
  operatSide=-1;
  circlePS=3;
  middlePS=3;
  surfacePS=2;
  maskRound=1;
  timeP=500;
  color[0]=CRGB(0,0,10);
  color[1]=CRGB(0,10,0);
  color[2]=CRGB(0,10,10);
  color[3]=CRGB(10,0,0);
  color[4]=CRGB(10,0,10);
  color[5]=CRGB(10,10,0);
  mask8[0]=CRGB(15,0,0);mask8[1]=CRGB(30,0,0);mask8[2]=CRGB(60,0,0);mask8[3]=CRGB(0,0,0);
  mask8[4]=CRGB(0,0,0);mask8[5]=CRGB(0,0,0);mask8[6]=CRGB(0,0,0);mask8[7]=CRGB(0,0,0);
  mask12[0]=CRGB(15,0,0);mask12[1]=CRGB(30,0,0);mask12[2]=CRGB(60,0,0);mask12[3]=CRGB(0,0,0);
  mask12[4]=CRGB(0,0,0);mask12[5]=CRGB(0,0,0);mask12[6]=CRGB(0,0,0);mask12[7]=CRGB(0,0,0);
  mask12[8]=CRGB(0,0,0);mask12[9]=CRGB(0,0,0);mask12[10]=CRGB(0,0,0);mask12[12]=CRGB(0,0,0);
  for(int i=0;i<6;i++){
    for(int j=0;j<9;j++){
      cells[getIndex(i, j)]=i;
    }
  }
}
void Magic::setMask8(CRGB *mask8){
  this->mask8=mask8;
}
void Magic::setMask12(CRGB *mask12){
  this->mask12=mask12;
}
void Magic::setCirclePS(int circlePS){
  this->circlePS=circlePS;
}
void Magic::setMiddlePS(int middlePS){
  this->middlePS=middlePS;
}
void Magic::setSurfacePS(int surfacePS){
  this->surfacePS=surfacePS;
}
void Magic::setMaskRound(int maskRound){
  this->maskRound=maskRound;
}
void Magic::setTimeP(unsigned long timeP){
  this->timeP=timeP;
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
  nowTime=millis();
  if(nowTime<showTime){
    for(int i=0;i<54;i++)
      led[i]=SHOW[i];
    return;
  }
  if(startTime>0){

    int step=0;
    if(circleStep>0){
      step=(nowTime-startTime)*12*maskRound/timeP;
      for(int i=0;i<12;i++){
        CRGB mask;
        if(cw){
          mask=mask12[(12+step-i)%12];
        }else{
          mask=mask12[(i+12+step)%12];
        }
        led[CIRCLE[operatSide][i].getIndex()]=getMask(led[CIRCLE[operatSide][i].getIndex()], mask);
      }
    }
    if(middleStep>0){
      step=(nowTime-startTime)*12*maskRound/timeP;
      for(int i=0;i<12;i++){
        CRGB mask;
        if(cw){
          mask=mask12[(12+step-i)%12];
        }else{
          mask=mask12[(i+12+step)%12];
        }
        led[MIDDLE[operatSide][i].getIndex()]=getMask(led[MIDDLE[operatSide][i].getIndex()], mask);
      }
    }
    if(surfaceStep>0){
      step=(nowTime-startTime)*8*maskRound/timeP;
      for(int i=0;i<8;i++){
        CRGB mask;
        if(cw){
          mask=mask8[(8+step-i)%8];
        }else{
          mask=mask8[(i+8+step)%8];
        }
        led[SURFACE[operatSide][i].getIndex()]=getMask(led[SURFACE[operatSide][i].getIndex()], mask);
      }
    }
  }
}

void Magic::update(){
  if(startTime==0&&actionIndex>0){
    startTime=millis();
    lastUpdate=millis();
    if(actions[0].isSide){
      circleStep=circlePS;
      surfaceStep=surfacePS;
      middleStep=0;
    }else{
      circleStep=0;
      surfaceStep=0;
      middleStep=middlePS;
    }
    cw=actions[0].cw;
    operatSide=actions[0].surface;
    for(int i=0;i<actionIndex;i++){
      actions[i]=actions[i+1];
    }
    actionIndex--;
  }
  nowTime=millis();
  if(startTime!=0&&operatSide>=0){
    if(circleStep!=0){
      int circleStepTmp=circlePS-(nowTime-startTime)*circlePS/timeP;
      if(circleStepTmp<circleStep){
        rotationCircle(operatSide,cw,circleStep-circleStepTmp);
        circleStep=circleStepTmp;
      }
    }
    if(surfaceStep!=0){
      int surfaceStepTmp=surfacePS-(nowTime-startTime)*surfacePS/timeP;
      if(surfaceStepTmp<surfaceStep){
        rotationSurface(operatSide,cw,surfaceStep-surfaceStepTmp);
        surfaceStep=surfaceStepTmp;
      }
    }
    if(middleStep!=0){
      int middleStepTmp=middlePS-(nowTime-startTime)*middlePS/timeP;
      if(middleStepTmp<middleStep){
        rotationMiddle(operatSide,cw,middleStep-middleStepTmp);
        middleStep=middleStepTmp;
      }
    }
  }
  if(startTime!=0&&circleStep==0&&surfaceStep==0&&middleStep==0){
    startTime=0;
    operatSide=-1;
  }
}

void Magic::addAction(Action action){
  if(action.surface>=0){
    actions[actionIndex]=action;
    actionIndex++;
  }
}

void Magic::showFace(int front,int down){
  for(int i=0;i<54;i++)
    SHOW[i]=CRGB(0,0,0);
  showTime=millis()+1000;
  for(int i=0;i<9;i++){
    SHOW[down*9+i]=CRGB(10,0,0);
  }
  SHOW[front*9+4]=CRGB(10,0,0);
}
