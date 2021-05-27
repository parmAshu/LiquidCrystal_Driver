#include <Arduino.h>
#include <Wire.h> 
#include "LiquidCrystal_driver.h"

void setup()
{
  Serial.begin(9600); // The baudrate of Serial monitor is set in 9600
  
  delay(2000);

  InitializeLCD(0x27);
  
  Serial.println("Display ready");
}

void loop()
{
    if(Serial.available())
    {
        char ch = Serial.read();

        LCDPrintChar(ch);
    }
}