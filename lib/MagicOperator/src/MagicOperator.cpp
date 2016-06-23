#include "MagicOperator.h"

int MagicOperator::getNum(P p,int t,int frontSide){
  if(t<0)
    t=this->t;
  if(frontSide<0)
    frontSide=this->frontSide;
  return SURFACE[0][(surfaceD[frontSide][t][p.face]+p.getNum())%8].getNum();
}

//0:右；  1：下；  2：左；  3：上； 4：对面；5：自己；
int MagicOperator::getSide(int side){
  if(side==4||side == 5)
    return SIDE[frontSide][side];
  return SIDE[frontSide][(side-t+4)%4];
}
int MagicOperator::getRightSide(){
  return getSide(0);
}
int MagicOperator::getDownSide(){
  return getSide(1);
}
int MagicOperator::getLeftSide(){
  return getSide(2);
}
int MagicOperator::getUpSide(){
  return getSide(3);
}
int MagicOperator::getBackSide(){
  return getSide(4);
}
int MagicOperator::getFrontSide(){
  return getSide(5);
}

Action MagicOperator::getActionSameWay(int index1,int index2){
  if(!doubleSame) return Action(-1);
  int side=getSameSide(index1, index2);
  int t1=0,t2=0;
  if(side>=0){
    t1=getNumInCircle(side, index1);
    t2=getNumInCircle(side, index2);
    if (t1%3==t2%3 && t1%3 != 1) {
      return Action(side,t1%3==2);
    }
  }else {
    side=getSameMiddle(index1, index2);
    if(side < 0) return Action(-1);
    t1=getNumInMiddle(side, index1);
    t2=getNumInMiddle(side, index2);
    if(t1%3==t2%3 && t1%3!=1){
      return Action(side,t1%3==2,false);
    }
  }
  return Action(-1);
}

Action MagicOperator::getActionDisWay(int index1,int index2){
  if(!singleWay) return Action(-1);
  int side=getSameSide(index1,index2);
  int t1=0,t2=0;
  int d1,d2;
  if(side>=0){
    t1=getNumInCircle(side, index1);
    t2=getNumInCircle(side, index2);
    if(t2>t1){
      d1=t2-t1;
      d2=12+t1-t2;
    }else{
      d2=t1-t2;
      d1=12+t2-t1;
    }
    if(d1==d2)
      return Action(-1);
    return Action(side,d1<d2);
  }else {
    side=getSameMiddle(index1, index2);
    if(side < 0) return Action(-1);
    t1=getNumInMiddle(side, index1);
    t2=getNumInMiddle(side, index2);
    if(t2>t1){
      d1=t2-t1;
      d2=12+t1-t2;
    }else{
      d2=t1-t2;
      d1=12+t2-t1;
    }
    if(d1==d2)
      return Action(-1);
    return Action(side,d1<d2,false);
  }
}

bool MagicOperator::isAllCenter(){
  P p;
  for(int i=0;i<keyNum;i++){
    if(P(keys[i]).getNum()!=8)
      return false;
  }
  return true;
}

int MagicOperator::getSameSide(int index1,int index2){
  for(int i=0;i<6;i++){
    int t=0;
    for(int j=0;j<12;j++){
      if(CIRCLE[i][j].getIndex()==index1)
        t++;
      if(CIRCLE[i][j].getIndex()==index2)
        t++;
    }
    if(t==2)
      return i;
  }
  return -1;
}

int MagicOperator::getSameMiddle(int index1, int index2){
  for(int i=0;i<6;i++){
    int t=0;
    for(int j=0;j<12;j++){
      if(MIDDLE[i][j].getIndex()==index1)
        t++;
      if(MIDDLE[i][j].getIndex()==index2)
        t++;
    }
    if(t==2)
      return i;
  }
  return -1;
}

int MagicOperator::getNumInCircle(int side,int index){
  if(side < 0) return -1;
  for(int i=0;i<12;i++){
    if(CIRCLE[side][i].getIndex()==index)
      return i;
  }
  return -1;
}

int MagicOperator::getNumInMiddle(int side, int index){
  if(side < 0) return -1;
  for(int i=0;i<12;i++){
    if(MIDDLE[side][i].getIndex()==index)
      return i;
  }
  return -1;
}

void MagicOperator::removeKey(int index){
  for(int i=index;i<keyNum-1;i++){
    keys[i]=keys[i+1];
  }
  keyNum--;
}

MagicOperator::MagicOperator(Magic *magic,Keypad *kpd){
  this->magic=magic;
  this->kpd=kpd;
 if(rom.isNewone()){
    setDoubleSame();
    setDoubleDis();
    setSingleWay();
    setFaceInit();
  }else{
    setDoubleSame(rom.getDobuleSame(),true);
    setDoubleDis(rom.getDoubleDis(),true);
    setSingleWay(rom.getSingleWay(),true);
    setFaceInit(rom.getFrontSide(),rom.getDownSide(),true);
  }
}

void MagicOperator::setDoubleSame(bool doubleSame,bool fromMem){
  this->doubleSame=doubleSame;
  if(!fromMem)
    rom.setDoubleSame(doubleSame);
}
bool MagicOperator::getDoubleSame(){
  return doubleSame;
}
void MagicOperator::setDoubleDis(bool doubleDis,bool fromMem){
  this->doubleDis=doubleDis;
  if(!fromMem)
    rom.setDoubleDis(doubleDis);
}
bool MagicOperator::getDoubleDis(){
  return doubleDis;
}
void MagicOperator::setSingleWay(bool singleWay,bool fromMem){
  this->singleWay=singleWay;
  if(!fromMem)
    rom.setSingleWay(singleWay);
}
bool MagicOperator::getSignleWay(){
  return singleWay;
}


void MagicOperator::update(){
  if(!kpd->getKeys())  return;
  bool haveReleased=false;
  for(int i=0;i<LIST_MAX;i++){
    switch(kpd->key[i].kstate){
      case PRESSED:
        if(kpd->key[i].stateChanged){
          actionEnd=true;
          keys[keyNum]=kpd->key[i].kcode;
          keyNum++;
        }
        break;
      case RELEASED:
        haveReleased=true;
        break;
      default:
        break;
    }
  }
  if(haveReleased && actionEnd){
    switch (keyNum) {
      case 1:
        magic->addAction(getAction(keys[0]));
        break;
      case 2:
        magic->addAction(getAction(keys[0],keys[1]));
        break;
      case 3:
        if(setFace()<0)
          goBack();
        break;
      case 4:
        if(save()<0)
          if(clear()<0)
            random();
        break;
      default:
        break;
    }
  }
  if(haveReleased){
    actionEnd=false;
    for(int i=0;i<LIST_MAX;i++){
      if(kpd->key[i].kstate==RELEASED)
        removeKey(i);
    }
    // for(int i=0;i<keyNum;i++)
    //   Serial.println(keys[i]);
  }

}

void MagicOperator::setFaceInit(byte frontSide,byte downSide,bool fromMem){
  this->frontSide=frontSide;
  this->downSide=downSide;
  t=getT(frontSide,downSide)>=0?getT(frontSide,downSide):t;
  if(!fromMem){
    rom.setFrontSide(frontSide);
    rom.setDownSide(downSide);
  }
}

int MagicOperator::getT(int frontSide,int downSide){
  int tmpT=-1;
  if(SIDE[frontSide][1]==downSide)
    tmpT=0;
  else if(SIDE[frontSide][0]==downSide)
    tmpT=1;
  else if(SIDE[frontSide][3]==downSide)
    tmpT=2;
  else if(SIDE[frontSide][2]==downSide)
    tmpT=3;
  return tmpT;
}

int MagicOperator::setFace(){
  int side=-1;
  int tmpT;
  int down;
  int front;
  P plist[3]={
    P(keys[0]),
    P(keys[1]),
    P(keys[2]),
  };
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      if(i!=j){
        tmpT=getT(plist[i].face, plist[j].face);
        if(tmpT>=0&&getNum(plist[i],tmpT,plist[i].face)==3&&getNum(plist[3-i-j],tmpT,plist[i].face)==7){
          setFaceInit(plist[i].face, plist[j].face);
          magic->showFace(plist[i].face, plist[j].face);
          return 0;
        }
      }
    }
  }
  return -1;
}

int MagicOperator::goBack(){
  if(isAllCenter()){
    magic->goBack();
    return 1;
  }
  return -1;
}
int MagicOperator::save(){
  if(isAllCenter()){
    magic->save();
    return 1;
  }
  return -1;
}
int MagicOperator::clear(){
  int side=P(keys[0]).face;
  for(int i=0;i<4;i++){
    P tmpP=P(keys[i]);
    if(tmpP.face!=side)
      return -1;
    if(tmpP.getNum()%2!=0 || tmpP.getNum()==8)
      return -1;
  }
  magic->setCell();
  magic->OK();
}
int MagicOperator::random(){
  int side=P(keys[0]).face;
  for(int i=0;i<4;i++){
    P tmpP=P(keys[i]);
    if(tmpP.face!=side||tmpP.getNum()%2!=1)
      return -1;
  }
  magic->random();
}

Action MagicOperator::getAction(int index){
  P p=P(index);
  if(p.getNum()==8)
    return Action(-1);
  if (p.getNum()==1) {
    return Action(SIDE[p.face][0],true,false);
  }else if(p.getNum()==3){
    return Action(SIDE[p.face][1],true,false);
  }else if(p.getNum()==5){
    return Action(SIDE[p.face][2],true,false);
  }else if(p.getNum()==7){
    return Action(SIDE[p.face][3],true,false);
  }
  if(!singleWay) return Action(-1);
  int num=getNum(p);
  if(num<0) return Action(-1);
  if(p.face==frontSide){
    if(num==0){
      return Action(getLeftSide(),false);
    }else if(num==2){
      return Action(getRightSide());
    }else if(num==4){
      return Action(getRightSide(),false);
    }else if(num==6){
      return Action(getLeftSide());
    }
  }else if(p.face==getBackSide()){
    if(num==0){
      return Action(getRightSide(),false);
    }else if(num==2){
      return Action(getLeftSide());
    }else if(num==4){
      return Action(getLeftSide(),false);
    }else if(num==6){
      return Action(getRightSide());
    }
  }else if(p.face==getUpSide()){
    if(num==0){
      return Action(getBackSide());
    }else if(num==2){
      return Action(getBackSide(),false);
    }else if(num==4){
      return Action(getFrontSide());
    }else if(num==6){
      return Action(getFrontSide(),false);
    }
  }else if(p.face==getDownSide()){
    if(num==0){
      return Action(getFrontSide());
    }else if(num==2){
      return Action(getFrontSide(),false);
    }else if(num==4){
      return Action(getBackSide());
    }else if(num==6){
      return Action(getBackSide(),false);
    }
  }else if(p.face==getLeftSide()){
    if(num==0){
      return Action(getUpSide());
    }else if(num==2){
      return Action(getUpSide(),false);
    }else if(num==4){
      return Action(getDownSide());
    }else if(num==6){
      return Action(getDownSide(),false);
    }
  }else if(p.face==getRightSide()){
    if(num==0){
      return Action(getUpSide());
    }else if(num==2){
      return Action(getUpSide(),false);
    }else if(num==4){
      return Action(getDownSide());
    }else if(num==6){
      return Action(getDownSide(),false);
    }
  }
  return Action(-1);
}
Action MagicOperator::getAction(int index1, int index2){
  if(isAllCenter()){
    magic->showFace(frontSide,downSide);
    return Action(-1);
  }
  Action ans=getActionSameWay(index1, index2);
  if(ans.surface<0)
    ans=getActionDisWay(index1, index2);
  return ans;
}
