#include "Arduino.h"
#include "EEPROM.h"
#include "HandleEEPROM.h"


bool writeEEPROM(int startAdr, String data) {
  //Intialize the response ("true" if successfull)
  bool res;
  
  //Start to write
  //Write the length of string [eg:= 4abcd]
  EEPROM.write(startAdr, data.length());

  //read the rest data
  for (int i = 0; i < data.length(); ++i)
  {
    EEPROM.write(startAdr + i+1, data[i]);
  }

  //check wheather successfull or not
  if (EEPROM.commit()) {
    res = true;
  } else {
    res = false;
  }

  return res;
}

String readEEPROM(int startAdr ) {

  //Intialize the output
  String data;
  int dataLength=char(EEPROM.read(startAdr));
  //start reading
  for (int i = startAdr+1; i < startAdr+1+dataLength; ++i)
  {
    data += char(EEPROM.read(i));
  }
  data.trim();
  return data;
}

void clearEEPROM(int startAdr,int endAdr) {

  delay(1000);
  for (int i = startAdr; i < endAdr; i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();
  delay(500);
}
