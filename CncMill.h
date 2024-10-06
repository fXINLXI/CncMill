#ifndef CncMill_H
#define CncMill_H

#include "Arduino.h"
#include <LCD_I2C.h>
#include <SD.h>

#define maxFiles 10

class CncMill{
  public:
    CncMill(int cs, int enc1, int enc2, int encB);
    void begin();//initializes cnc library
    void loadFileNames();//loads filenames to flilenames table and sets _noFiles to real number of files on sd
    void chooseMode();//lets user to choose mill mode
    void gCodemode();

    bool _mode;//0 : test mode, 1 : g-code mode
    int _noFiles;//real number of files on sd
    String fileNames[maxFiles];//max number of files to load
    
  private: 
    int _enc1;//pin connected to 1st pin of encoder
    int _enc2;//pin connected to 2nd pin of encoder
    int _encB;//pin connected to button pin of encoder
    int _cs;//chip select for SD card
    LCD_I2C lcd{0x27, 20, 4};//creates lcd object
};
#endif