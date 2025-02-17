#include <SoftwareSerial.h>
#include <Wire.h>
#include "SerialTransfer.h"

SerialTransfer wireless_serial;

SoftwareSerial HC12(16, 17); 

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

  radio_data.apple = 1;
  radio_data.banana = 3;
  radio_data.kiwi = 7;
}
void loop()
{
  wireless_serial.sendDatum(radio_data);
}
