#ifndef MAGICOPERATOR_H
#define MAGICOPERATOR_H

#include "Magic.h"
#include "Keypad.h"
#include "EEPROMOperator.h"

class MagicOperator{
private:
  Magic *magic;
  byte frontSide=0,downSide=4;
  bool doubleSame=true,doubleDis=true,singleWay=true;
  int t;
  byte keys[54];
  byte keyNum=0;
  Keypad *kpd;
  bool actionEnd=true;
  EEPROMOperator rom=EEPROMOperator();
  void(* resetFunc) (void) = 0;
protected:
  int getNum(P p,int t=-1,int frontSide=-1);//postion[0前后，1左右，2上下]
  int getSide(int side);//0:右；  1：下；  2：左；  3：上； 4：对面；5：自己；
  int getRightSide();
  int getDownSide();
  int getLeftSide();
  int getUpSide();
  int getBackSide();
  int getFrontSide();
  Action getActionSameWay(int index1,int index2);
  Action getActionDisWay(int index1,int index2);
  bool isAllCenter();
  int getSameSide(int index1,int index2);
  int getSameMiddle(int index1,int index2);
  int getNumInCircle(int side,int index);
  int getNumInMiddle(int side,int index);
  void removeKey(int index);
public:
  MagicOperator(Magic *magic,Keypad *kpd);
  void setDoubleSame(bool doubleSame=true,bool fromMem=false);
  bool getDoubleSame();
  void setDoubleDis(bool doubleDis=true,bool fromMem=false);
  bool getDoubleDis();
  void setSingleWay(bool singleWay=true,bool fromMem=false);
  bool getSignleWay();
  void setFaceInit(byte frontSide=0,byte downSide=4,bool fromMem=false);

  void update();
  int getT(int frontSide,int downSide);
  int setFace();
  int goBack();
  int save();
  int clear();
  int random();
  int resetAll();
  Action getAction(int index);//前后->左右;上下->前后;左右->上下
  Action getAction(int index1,int index2);

};
//d=surfaceD[frontSide][t][p.face];
//t:
//  0:DOWN[frontSide]=downside;
//  1:RIGHT[frontSide]=downSide;
//  2:UP[frontSide]=downSide;
//  3:LEFT[frontSide]=downSide;
static byte surfaceD[6][4][6]={
  {
    {0,0,0,0,0,0},
    {2,2,6,2,2,2},
    {4,4,4,4,4,4},
    {6,6,6,6,6,6},
  },
  {
    {0,0,0,0,6,2},
    {2,2,2,4,0,4},
    {4,4,4,4,2,6},
    {6,6,6,6,4,2},
  },
  {
    {0,0,0,0,4,4},
    {6,2,2,2,6,6},
    {4,4,4,4,0,0},
    {2,6,6,6,2,2},
  },
  {
    {0,0,0,0,2,6},
    {2,6,2,2,4,0},
    {4,4,4,4,6,2},
    {6,2,6,6,0,4},
  },
  {
    {0,2,4,6,0,4},
    {2,4,6,0,2,2},
    {4,6,0,2,4,0},
    {6,0,2,4,6,6},
  },
  {
    {0,6,4,2,4,0},
    {2,0,6,4,2,2},
    {4,2,0,6,0,4},
    {6,4,2,0,6,6},
  },
};
#endif //MAGICOPERATOR_H
