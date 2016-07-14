#include "Trans.h"

void Trans::get(){

  byte head=readBuffer[0];
  getLength=0;
  for(int i=2;i<length;i++){
    if(i%2==0){
      getBuffer[getLength++]=readBuffer[i];
    }
  }
  Serial.println("in get");
  hand(head,getLength);
  Serial.println("end get");
}

Trans::Trans(Magic *magic,MagicOperator *magicOperator){
  this->magic=magic;
  this->magicOperator=magicOperator;
}

void Trans::read(){
  while(Serial1.available()){
    byte read=Serial1.read();
    if(length%2==1 && read == '\n'){
        get();
        length=0;
    }else{
      readBuffer[length]=read;
      length++;
    }
  }
}

void Trans::write(byte head,byte* data ,int length){
  byte* out=new byte[length*2+2];
  out[0]=head;
  out[1]=0;
  for(int i=0;i<length;i++){
    out[i*2+2]=data[i];
    out[i*2+3]=0;
  }
  out[length*2+1]='\n';
  Serial1.write(out,length*2+2);
  Serial1.flush();
}

void Trans::write(byte head, bool value){
  byte* data=new byte[1];
  data[0]=(byte)value;
  write(head,data,1);
}

void Trans::write(byte head, byte value){
  byte* data=new byte[1];
  data[0]=value;
  write(head,data,1);
}

void Trans::write(byte head,unsigned long value){
  byte* data=new byte[4];
  for(int i=3;i>=0;i--){
    byte tmp=value&0xFF;
    value=value>>8;
    data[i]=tmp;
  }
  write(head,data,4);
}

void Trans::write(byte head,CRGB* rgbs,byte length){
  byte* data=new byte[3*length+1];
  data[0]=length;
  for(int i=0;i<length;i++){
    data[i*3+1]=rgbs[i].r;
    data[i*3+2]=rgbs[i].g;
    data[i*3+3]=rgbs[i].b;
  }
  write(head,data,3*length+1);
}

unsigned long Trans::readLong(){
  unsigned long read=0;
  for(int i=0;i<4;i++){
    read=read<<8;
    byte tmp=getBuffer[i];
    read=tmp|read;
  }
  return read;
}

CRGB* Trans::readCRGB(){
  byte length=getBuffer[0];
  CRGB* data=new CRGB[length];
  for(int i=0;i<length;i++){
    data[i]=CRGB(getBuffer[3*i+1],getBuffer[3*i+2],getBuffer[3*i+3]);
  }
  return data;
}

void Trans::hand(byte head,int length){
  Serial.print("head:");
  Serial.println(head);
  switch (head) {
    case CONNECTION_AC:
      write(CONNECTION_AC);
      break;
    case SYNC_AC:
      sync();
      magic->OK(100);
      break;
    case CIRCLE_STEP_AC:
      magic->setCirclePS(getBuffer[0]);
      magic->setMiddlePS(getBuffer[0]);
      magic->OK(100);
      write(CIRCLE_STEP_AC,magic->getCirclePS());
      break;
    case SURFACE_STEP_AC:
      magic->setSurfacePS(getBuffer[0]);
      magic->OK(100);
      write(SURFACE_STEP_AC,magic->getSurfacePS());
      break;
    case SINGLE_OPERATE_AC:
      magicOperator->setSingleWay(getBuffer[0]);
      magic->OK(100);
      write(SINGLE_OPERATE_AC,magicOperator->getSignleWay());
      break;
    case DOUBLE_SAME_AC:
      magicOperator->setDoubleSame(getBuffer[0]);
      magic->OK(100);
      write(DOUBLE_SAME_AC,magicOperator->getDoubleSame());
      break;
    case DOUBLE_DIS_AC:
      magicOperator->setDoubleDis(getBuffer[0]);
      magic->OK(100);
      write(DOUBLE_DIS_AC,magicOperator->getDoubleDis());
      break;
    case TIME_P_AC:
      magic->setTimeP(readLong());
      magic->OK(100);
      write(TIME_P_AC,magic->getTimeP());
      break;
    case MASK_ROUND_AC:
      magic->setMaskRound(getBuffer[0]);
      magic->OK(100);
      write(MASK_ROUND_AC,magic->getMaskRound());
      break;
    case COLOR_AC:
      magic->setColor(readCRGB());
      for(int i=0;i<6;i++){
        Serial.print(magic->getColor()[i].r);
        Serial.print(";");
        Serial.print(magic->getColor()[i].g);
        Serial.print(";");
        Serial.println(magic->getColor()[i].b);
      }
      magic->OK(100);
      write(COLOR_AC,magic->getColor(),6);
      break;
    default:
      break;
  };
}

void Trans::sync(){
  write(CIRCLE_STEP_AC,magic->getCirclePS());
  write(SURFACE_STEP_AC,magic->getSurfacePS());
  write(SINGLE_OPERATE_AC,magicOperator->getSignleWay());
  write(DOUBLE_SAME_AC,magicOperator->getDoubleSame());
  write(DOUBLE_DIS_AC,magicOperator->getDoubleDis());
  write(TIME_P_AC,magic->getTimeP());
  write(MASK_ROUND_AC,magic->getMaskRound());
  write(COLOR_AC,magic->getColor(),6);
}
