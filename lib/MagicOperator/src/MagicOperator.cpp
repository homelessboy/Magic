#include "MagicOperator.h"

int MagicOperator::getNum(P p){
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
  if(!useSameWay) return Action(-1);
  int side=getSameSide(index1, index2);
  int t1=0,t2=0;
  if(side>=0){
    t1=getNumInCircle(side, index1);
    t2=getNumInCircle(side, index2);
    if (t1%3==t2%3 && t1%3 != 1) {
      return Action(side,t1%3==2);
    }
  }else if(useForMiddle){
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
  if(!useDisWay) return Action(-1);
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
    return Action(side,d1<d2);
  }else if(useForMiddle){
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
    return Action(side,d1<d2,false);
  }
}

bool MagicOperator::isTowCenter(int index1,int index2){
  P p1=P(index1);
  P p2=P(index2);
  return p1.getNum()==8 && p2.getNum()==8;
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

MagicOperator::MagicOperator(Magic *magic){
  this->magic=magic;
}

void MagicOperator::setFace(int frontSide,int downSide){
  this->frontSide=frontSide;
  this->downSide=downSide;
  t=0;
  if(SIDE[frontSide][1]==downSide)
    t=0;
  else if(SIDE[frontSide][0]==downSide)
    t=1;
  else if(SIDE[frontSide][3]==downSide)
    t=2;
  else if(SIDE[frontSide][2]==downSide)
    t=3;
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
  if(isTowCenter(index1, index2)){
    magic->showFace(frontSide,downSide);
    return Action(-1);
  }
  Action ans=getActionSameWay(index1, index2);
  if(ans.surface<0)
    ans=getActionDisWay(index1, index2);
  return ans;
}
