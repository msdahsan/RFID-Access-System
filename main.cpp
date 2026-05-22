#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>


#define SS_PIN 53
#define RST_PIN 13
#define BUZZER_PIN 11
const int RS = 7, EN = 6, D4 = 5, D5 = 4, D6 = 3, D7 = 2;
unsigned long timePassed = 0;

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

void setup()
{
 lcd.begin(16, 2);
 SPI.begin(); // Initiate SPI bus
 mfrc522.PCD_Init(); // Initiate MFRC522
 lcd.print("Scan Card");
}


void loop()
{
 timePassed = millis();
 // Look for new cards
 if (!mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial()) return; 

 String content= "";
 for (byte i = 0; i < mfrc522.uid.size; i++)
 {
 content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
 content.concat(String(mfrc522.uid.uidByte[i], HEX));
 }
 content.toUpperCase();
 lcd.clear();
 if (content.substring(1) == "06 9E CE 01") 
 {
 lcd.print("AUTHORIZED ACCESS");
 tone(BUZZER_PIN, 1500);
 delay(1500);
 noTone(BUZZER_PIN);
 }
else {
  lcd.print("ACCESS DENIED");
  tone(BUZZER_PIN, 200);
  delay(1500);
  noTone(BUZZER_PIN);
 }
lcd.clear();
lcd.print("Scan Card");
}
