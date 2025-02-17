#include <Arduino.h>

#include <SoftwareSerial.h>
#include <Wire.h>
#include "SerialTransfer.h"

SerialTransfer wireless_serial;

SoftwareSerial HC12(10, 11); 

struct SendData
{
  int apple;
  int banana;
  int kiwi;
} radio_data;

void setup()
{
  Serial.begin(9600);
  HC12.begin(9600); 

  wireless_serial.begin(HC12);
}

void loop()
{
  if (wireless_serial.available())
  {
    wireless_serial.rxObj(radio_data);

    Serial.print(radio_data.apple);
    Serial.print("  ");
    Serial.print(radio_data.banana);
    Serial.print("  "); 
    Serial.println(radio_data.kiwi);
  }
}
