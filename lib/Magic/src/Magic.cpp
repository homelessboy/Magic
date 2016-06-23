//
// Created by java-xuhui on 2016/3/31.
//
#include "Magic.h"

void Magic::rotationP(P *ps, bool cw, int size, int step) {
  while (step-- > 0) {
    P p = ps[0];
    byte tmp = cells[p.getIndex()];
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

Magic::Magic(CRGB *led){
  this->led=led;
  if(rom.isNewone()){
    setDefault();
  }else{
    setFromMem();
  }
}

void Magic::setFromMem(){
  circleStep=0;
  middleStep=0;
  surfaceStep=0;
  operatSide=-1;
  setCirclePS(rom.getCirclePS(),true);
  setMiddlePS(rom.getMiddlePS(),true);
  setSurfacePS(rom.getSurfacePS(),true);
  setMaskRound(rom.getMaskRound(),true);
  setTimeP(rom.getTimeP(),true);
  setMask8(rom.getMask8(),true);
  setMask12(rom.getMask12(),true);
  setColor(rom.getColor(),true);
  setCell(rom.getCell(),true);
  setMemFromMem();
}

void Magic::setDefault(){
  circleStep=0;
  middleStep=0;
  surfaceStep=0;
  operatSide=-1;
  setCirclePS();
  setMiddlePS();
  setSurfacePS();
  setMaskRound();
  setTimeP();
  setMask8();
  setMask12();
  setColor();
  setCell();
  setMemDefault();
}

void Magic::setCell(byte *cell,bool fromMem){
  if(cell==NULL){
    cell=new byte[54];
    for(byte i=0;i<6;i++)
      for(int j=0;j<9;j++)
        cell[getIndex(i, j)]=i;
  }
  delete(cells);
  this->cells=cell;
  if(!fromMem)
    rom.setCell(cell);
}

byte* Magic::getCell(){
  return cells;
}

void Magic::setMemDefault(){
  for(int i=0;i<5;i++){
    delete (cellMem[i]);
    cellMem[i]=new byte[54];
    numMeM=0;
    saveMem();
  }
}

void Magic::setMemFromMem(){
  for(int i=0;i<5;i++){
    delete(cellMem[i]);
    cellMem[i]=new byte[54];
  }
  numMeM=rom.getMemNum();
  for(int i=0;i<numMeM;i++){
    cellMem[i]=rom.getMem(i);
  }
}

void Magic::saveMem(){
  rom.setMemNum(numMeM);
  for(int i=0;i<numMeM;i++)
    rom.setMem(cellMem[i], i);
}

void Magic::setMask8(CRGB *mask8,bool fromMem){
  if(mask8==NULL){
    mask8=new CRGB[8];
    mask8[0]=CRGB(15,0,0);mask8[1]=CRGB(30,0,0);mask8[2]=CRGB(60,0,0);mask8[3]=CRGB(0,0,0);
    mask8[4]=CRGB(0,0,0);mask8[5]=CRGB(0,0,0);mask8[6]=CRGB(0,0,0);mask8[7]=CRGB(0,0,0);
  }
  delete(this->mask8);
  this->mask8=mask8;
  if(!fromMem)
    rom.setMask8(mask8);
}
CRGB* Magic::getMask8(){
  return mask8;
}
void Magic::setMask12(CRGB *mask12,bool fromMem){
  if(mask12==NULL){
    mask12=new CRGB[12];
    mask12[0]=CRGB(15,0,0);mask12[1]=CRGB(30,0,0);mask12[2]=CRGB(60,0,0);mask12[3]=CRGB(0,0,0);
    mask12[4]=CRGB(0,0,0);mask12[5]=CRGB(0,0,0);mask12[6]=CRGB(0,0,0);mask12[7]=CRGB(0,0,0);
    mask12[8]=CRGB(0,0,0);mask12[9]=CRGB(0,0,0);mask12[10]=CRGB(0,0,0);mask12[11]=CRGB(0,0,0);
  }
  delete(this->mask12);
  this->mask12=mask12;
  if(!fromMem)
    rom.setMask12(mask12);
}
CRGB* Magic::getMask12(){
  return mask12;
}
void Magic::setColor(CRGB *color,bool fromMem){
  if(color==NULL){
    color=new CRGB[6];
    color[0]=CRGB(0,0,10);
    color[1]=CRGB(0,10,0);
    color[2]=CRGB(0,10,10);
    color[3]=CRGB(10,0,0);
    color[4]=CRGB(10,0,10);
    color[5]=CRGB(10,10,0);
  }
  delete (this->color);
  this->color=color;
  if(!fromMem)
    rom.setColor(color);
}
CRGB* Magic::getColor(){
  return color;
}
void Magic::setCirclePS(byte circlePS,bool fromMem){
  this->circlePS=circlePS;
  if(!fromMem)
    rom.setCirclePS(circlePS);
}
byte Magic::getCirclePS(){
  return circlePS;
}
void Magic::setMiddlePS(byte middlePS,bool fromMem){
  this->middlePS=middlePS;
  if(!fromMem)
    rom.setMiddlePS(middlePS);
}
byte Magic::getMiddlePS(){
  return middlePS;
}
void Magic::setSurfacePS(byte surfacePS,bool fromMem){
  this->surfacePS=surfacePS;
  if(!fromMem)
    rom.setSurfacePS(surfacePS);
}
byte Magic::getSurfacePS(){
  return surfacePS;
}
void Magic::setMaskRound(byte maskRound,bool fromMem){
  this->maskRound=maskRound;
  if(!fromMem)
    rom.setMaskRound(maskRound);
}
byte Magic::getMaskRound(){
  return maskRound;
}
void Magic::setTimeP(unsigned long timeP,bool fromMem){
  this->timeP=timeP;
  if(!fromMem)
    rom.setTimeP(timeP);
}
unsigned long Magic::getTimeP(){
  return timeP;
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

void Magic::getLed(){
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
      if(circleStepTmp<0)
        circleStepTmp=0;
      if(circleStepTmp<circleStep){
        rotationCircle(operatSide,cw,circleStep-circleStepTmp);
        circleStep=circleStepTmp;
      }
    }
    if(surfaceStep!=0){
      int surfaceStepTmp=surfacePS-(nowTime-startTime)*surfacePS/timeP;
      if(surfaceStepTmp<0)
        surfaceStepTmp=0;
      if(surfaceStepTmp<surfaceStep){
        rotationSurface(operatSide,cw,surfaceStep-surfaceStepTmp);
        surfaceStep=surfaceStepTmp;
      }
    }
    if(middleStep!=0){
      int middleStepTmp=middlePS-(nowTime-startTime)*middlePS/timeP;
      if(middleStepTmp<0)
        middleStepTmp=0;
      if(middleStepTmp<middleStep){
        rotationMiddle(operatSide,cw,middleStep-middleStepTmp);
        middleStep=middleStepTmp;
      }
    }
  }
  if(startTime!=0&&circleStep==0&&surfaceStep==0&&middleStep==0){
    startTime=0;
    operatSide=-1;
    if(actionIndex==0&&tmpTimeP>0){
      timeP=tmpTimeP;
      tmpTimeP=0;
    }
    rom.setCell(cells);
  }
}

void Magic::addAction(Action action){
  if(action.surface>=0){
    actions[actionIndex]=action;
    actionIndex++;
    if(memChoice>=0)
      choice();
  }
}

void Magic::showFace(int front,int down){
  for(int i=0;i<54;i++)
    SHOW[i]=CRGB(0,0,0);
  showTime=millis()+1000;
  for(int i=0;i<9;i++){
    SHOW[down*9+i]=CRGB(10,0,0);
  }
  SHOW[front*9+1]=CRGB(10,0,0);
  SHOW[front*9+3]=CRGB(10,0,0);
  SHOW[front*9+4]=CRGB(10,0,0);
  SHOW[front*9+5]=CRGB(10,0,0);
  SHOW[front*9+7]=CRGB(10,0,0);
}

void Magic::random(int i,unsigned long timeRandom){
  if(tmpTimeP==0){
    tmpTimeP=timeP;
    timeP=timeRandom;
  }
  srand(millis());
  for(int i=0;i<20;i++){
    int t=randomx(18);
    int side=(t/2)%6;
    if(t>15)
      side=5;
    addAction(Action(side,t%2==1,t/2>=6));
  }
 OK();
}

void Magic::save(){
  numMeM++;
  if(numMeM>5)
    numMeM=5;
  for(int i=numMeM;i>1;i--){
    cellMem[i-1]=cellMem[i-2];
  }
  delete(cellMem[0]);
  cellMem[0]=new byte[54];
  for(int i=0;i<54;i++){
    cellMem[0][i]=cells[i];
  }
  saveMem();
  OK();
}

void Magic::goBack(){
  if(!numMeM>0)
    return;
  memChoice++;
  if(memChoice>=numMeM)
    memChoice=0;
  for(int i=0;i<54;i++)
    cells[i]=cellMem[memChoice][i];
  OK(300);
}

void Magic::choice(){
  byte* tmp=cellMem[memChoice];
  for(int i=memChoice;i>0;i--){
    cellMem[i]=cellMem[i-1];
  }
  cellMem[0]=tmp;
  memChoice=-1;
}

void Magic::OK(unsigned long time){
  for(int i=0;i<54;i++)
    led[i]=CRGB(0,10,0);
  FastLED.show();
  delay(time);
}

void Magic::NOTOK(unsigned long time){
  for(int i=0;i<54;i++)
    led[i]=CRGB(10,0,0);
  FastLED.show();
  delay(time);
}
