#include <LoRa.h>
#include <SPI.h>
 
#define ss 5
#define rst 14
#define dio0 2

int counter = 0;
 
void setup() 
{
  Serial.begin(9600); 
  // while (!Serial);
  Serial.println("LoRa Sender");
 
  LoRa.setPins(ss, rst, dio0);    //setup LoRa transceiver module
  
  while (!LoRa.begin(434E6))     //freq
      LoRa.setSpreadingFactor(6);  
      LoRa.setPreambleLength(8);
      LoRa.setSignalBandwidth(125E3); 
      LoRa.setTxPower(20); 
  {
    Serial.println(".");
    delay(500);//time send
  }
  LoRa.setSyncWord(0xA5);
  Serial.println("LoRa Initializing OK!");
}
 
void loop() 
{
  Serial.print("Sending packet: ");
  Serial.println(counter);
  Serial.println(counter%2);
  LoRa.beginPacket();   //Send LoRa packet to receiver
  LoRa.print("xvvv kmzdo mdso mdsp mdsk msdop ndmjo ndspj ndsoj ndso dsoi mdsoi jmdso sdmoi doi jsdoi jdoi jdsv vjnvisvvosovsosmvsmssomssiovdsmvsdfsfssv");//packet64bytesmax
  LoRa.print(counter);
  LoRa.endPacket();
 


  delay(2000);
}
