#include <stdint.h>
#include "Arduino.h"
#include "CncMill.h"

CncMill::CncMill(int cs,int enc1, int enc2, int encB){
  _enc1=enc1;
  _enc2=enc2;
  _encB=encB;
  _cs=cs;
}

void CncMill::begin(){
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.print("Loading...");
  pinMode(_enc1,INPUT);//sets pin inputs for encoder
  pinMode(_enc2,INPUT);//sets pin inputs for encoder
  pinMode(_encB,INPUT);//sets pin inputs for encoder
  Serial.println("Starting CNC");
  Serial.print("encoder pin1 = ");
  Serial.print(_enc1);
  Serial.print("; encoder pin2 = ");
  Serial.print(_enc2);
  Serial.print("; encoder button pin = ");
  Serial.println(_encB);
  Serial.print("CS pin = ");
  Serial.println(_cs);
}

void CncMill::loadFileNames(){
  bool again=true;
  lcd.setCursor(0,1);
  if(!SD.begin(_cs)){//opens sd card
    Serial.println("SD opening ERROR!!!");
    lcd.print("SD opening ERROR!!!");
    while(1){
      if(!digitalRead(_encB)){//if opening gone wrong, waits to recheck untill encoder button pressed
        Serial.print("retrying... ");
        if(SD.begin(_cs)){
          lcd.setCursor(0,1);
          lcd.print("                   ");
          break;
          }
        else{Serial.println("ERROR");}
      }
    }
  }
  lcd.setCursor(0,1);
  Serial.println("SD opening success");
  lcd.print("SD opening success");

  File root;
  root=SD.open("/pliki/");
  int counter=0;

  while (true) {//loads files
    File entry =  root.openNextFile();

    if (! entry) {//checks if there are any more files on sd. if too many - loads only as many as it is possible
      break;
    }

    if(counter>maxFiles-1){//checks if there are too many files
      Serial.println("too many files!!!");
      lcd.setCursor(0,2);
      lcd.print("               ,MAX!");
      break;
    }

    fileNames[counter]=entry.name();//adds names of files to fileNames
    entry.close();
    counter++;
  }
  root.close();
  _noFiles=counter;
  Serial.println(_noFiles);
  lcd.setCursor(0,2);
  lcd.print(_noFiles);
  lcd.print(" files loaded");//prints how many files loaded
  Serial.println("Loading success");
}

void CncMill::chooseMode(){//lets user to choose mode
  bool mode=1;//if 0 : test mode, if 1 : g-code mode
  uint8_t counter=0;
  bool actual;
  bool prev=digitalRead(_enc1);
  lcd.setCursor(0,3);
  lcd.print("Mode : ");
  lcd.print("g-code");
  while(1){
    actual=digitalRead(_enc1);
    if(actual!=prev){//lets user to choose mode
      counter++;
      mode=(counter/2)%2;
      Serial.println(mode);
      delay(15);
      lcd.setCursor(7,3);
      if(mode){
        lcd.print("g-code");
      }
      else{
        lcd.print("test  ");
      }
    }
    if(!digitalRead(_encB)){//waits untill encoder button pressed and sets mode
      break;
    }
    prev=actual;
  }
  lcd.clear();
}

void CncMill::gCodemode(){
  uint8_t chosen=0;
  while(1){
    switch(_noFiles-chosen){
      case 1:
        lcd.setCursor(0,0);
    }
  }
}