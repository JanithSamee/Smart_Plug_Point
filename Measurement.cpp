#include "Arduino.h"
#include "Measurement.h"

float  getCurrentValue(int ReadPin){
  float averageADC=0;
  for(int i=0;i<100;i++){
    averageADC+=analogRead(ReadPin) ;
  }
  averageADC =averageADC/(float)100;
  
  //sensor  Parameters
  int sensitivity= 100;  //100 mV/A
  int meanVoltage=2500;   // in mV
  
  float Vout= ((averageADC)/1023)*5000;  //in millivolts
  float current =(Vout -meanVoltage)/(float)sensitivity; //in Amphere
  delay(1000);
  
  if (current<0){
    current=current*(-1);
  }
  current=current;
  return current;
}

float getVoltageValue(){
 return 230;
}
