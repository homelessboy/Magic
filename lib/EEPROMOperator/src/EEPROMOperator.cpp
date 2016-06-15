#include "EEPROMOperator.h"

void EEPROMOperator::saveCells(byte *cells){
  byte tmp=0;
  byte *save=new byte[18];
  byte index=0;
  for(int i=0;i<54;i++){
    if(i%3==0){
      tmp=cells[i];
    }else if(i%3==1){
      tmp=tmp*6+cells[i];
    }else {
      tmp=tmp*6+cells[i];
      save[index]=tmp;
      index++;
    }
  }  
  for(int i=0;i<18;i++){
    EEPROM.write(CELLS_START+i, save[i]);
  }
  delete(save);
}

byte* EEPROMOperator::getCells(){
  byte* get=new byte[54];
  byte tmp;
  for(int i=0;i<18;i++){
    tmp=EEPROM.read(CELLS_START+i);
    get[i*3+2]=tmp%6;
    tmp=tmp/6;
    get[i*3+1]=tmp%6;
    get[i*3]=tmp/6;
  }
  return get;
}
