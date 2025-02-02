#include <SPI.h>
#include <LoRa.h>


#define ss 10
#define rst 9
#define dio0 2

void setup() {
  //initialize Serial Monitor
  Serial.begin(9600);
  while (!Serial);
  Serial.println("LoRa Receiver");

  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);
  
  //replace the LoRa.begin(---E-) argument with your location's frequency 
  //433E6 for Asia
  //866E6 for Europe
  //915E6 for North America
  while (!LoRa.begin(434E6)) { 
    Serial.println(".");
    delay(500);
  }
   // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSyncWord(0xA5);
  Serial.println("LoRa Initializing OK!");

  
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      String LoRaData = LoRa.readString();
      Serial.println(LoRaData); 
    }

    // print RSSI of packet

    Serial.print("[sx1278] RSSI: ");
    Serial.println(LoRa.packetRssi());
    Serial.print("[SX1278] SNR:");
    Serial.print(LoRa.packetSnr());
    Serial.println(F(" dB"));
    Serial.print("[SX1278] Freq Error:");
    Serial.print(LoRa.packetFrequencyError());
    Serial.println(F(" HZ"));
  /*  Serial.print("[SX1278] parsePacket:");
    Serial.print(LoRa.parsePacket());*/

  }
}
