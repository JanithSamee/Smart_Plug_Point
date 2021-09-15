/*
 * This functions to read write data to EEPROM
 * There is a limit in EEPROM (512 Bytes)
 * Read and Write Sctructure
        * First bit is to define length of data  
        * Rest is data
 *We store SSID,Password,Hostname
      *SSID       = 20 bytes of length 0-20 [length,20 charcters]
      *Password   = 12 bytes of legnth 21- 34 [length,12 charcters]
      *Hostname   = 20 bytes of length  35-56 [length,20 charcters]
 
 */


#include "Arduino.h"

bool writeEEPROM(int startAdr, String data);
String readEEPROM(int startAdr );
void clearEEPROM(int startAdr,int endAdr);
