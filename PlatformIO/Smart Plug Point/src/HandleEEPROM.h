/*
 * This functions to read write data to EEPROM
 * There is a limit in EEPROM (512 Bytes)
 * Read and Write Sctructure
        * First bit is to define length of data  
        * Rest is data
 *We store SSID,Password,Hostname
      *SSID       = 25 bytes of length 0-25 [length,25 charcters]
      *Password   = 25 bytes of legnth 26- 51 [length,25 charcters]
      *Hostname   = 25 bytes of length  52-76 [length,25 charcters]
 
 */
#ifndef HANDLEEEPROM_H
#define HANDLEEEPROM_H

#include "Arduino.h"

class HandleEEPROM
{
public:
     HandleEEPROM(int sizeOfEEPROM);
     bool writeEEPROM(int startAdr, String data);
     String readEEPROM(int startAdr);
     void clearEEPROM(int startAdr, int endAdr);

private:
     int _sizeOfEEPROM;
};

#endif