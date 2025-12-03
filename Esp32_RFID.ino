#include <SPI.h>
#include <MFRC522.h>
#define RST_PIN 0        // MFRC522 RST pin
#define SS_PIN 5         // MFRC522 SDA pin
MFRC522 mfrc522(SS_PIN, RST_PIN);     // Create MFRC522 instace
String globalRFID = "";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.print("Scan RFID tag to get UID... ");
}

void loop() {
  // put your main code here, to run repeatedly:
if(!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial())
{
  delay(50);
  return;
}
globalRFID = "";
for (byte i = 0; i< mfrc522.uid.size; i++)
{
  if(mfrc522.uid.uidByte[i]<0x10) globalRFID += "0";
  globalRFID += String(mfrc522.uid.uidByte[i],HEX);
}
  globalRFID.toUpperCase();
  Serial.print("UID tag ");
  Serial.println(globalRFID);
}
