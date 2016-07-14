#ifndef TRANS_H
#define TRANS_H

#include "MagicOperator.h"

static const byte CONNECTION_AC=0x01;
static const byte SYNC_AC=0x02;
static const byte CIRCLE_STEP_AC=0x03;
static const byte SURFACE_STEP_AC=0x04;
static const byte SINGLE_OPERATE_AC=0x05;
static const byte DOUBLE_SAME_AC=0x06;
static const byte DOUBLE_DIS_AC=0x07;
static const byte TIME_P_AC=0x08;
static const byte MASK_ROUND_AC=0x09;
static const byte COLOR_AC=0x0A;
static const byte STANDBY_TIME_AC=0x0B;

class Trans{
private:
  Magic *magic;
  MagicOperator *magicOperator;
  EEPROMOperator rom=EEPROMOperator();
  byte readBuffer[1000];//=new byte[1024];
  int length=0;
  byte getBuffer[1000];//r=new byte[1024];
  int getLength=0;
  void get();
  void hand(byte head,int length);
  void sync();
public:
  Trans(Magic *magic,MagicOperator *magicOperator);
  void read();
  void write(byte head,byte* data=NULL,int length=0);
  void write(byte head,bool value);
  void write(byte head,byte value);
  void write(byte head,unsigned long value);
  void write(byte head,CRGB* rgbs,byte length);
  unsigned long readLong();
  CRGB* readCRGB();
};

#endif //TRANS_H
