#include "SPI.h"
#include "MFRC522.h"
#define SS_PIN 10
#define RST_PIN 9

int button_state = 0;
int buttonPin = 7;
int ledIndicator = 2;
int doorDelay = 800;

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

int qtyOfCards = 2;
String registeredCards[] = {
  "46:0C:C8:0A",
  "46:0C:C8:0F", //gulbahar
  "46:0C:C8:0S"
};


void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  pinMode (buttonPin,INPUT_PULLUP);
  pinMode (ledIndicator,OUTPUT);
  digitalWrite(ledIndicator, 0);
}


void loop() {
  buttonModule();
  rfidModule();
}


void openDoor(){
  Serial.println("door open called");
  digitalWrite(ledIndicator, 1);
  delay(doorDelay);
  digitalWrite(ledIndicator, 0);
  delay(500); // for electrical security
}


void validateCard(String ID_key){
  for (int i = 0; i < qtyOfCards; i++){
    if (ID_key.indexOf(registeredCards[i]) >= 0){
      openDoor();
      Serial.println(registeredCards[i]);
    }
  }
}


void buttonModule(){
  button_state = digitalRead(buttonPin);
  if (button_state == 0){
    openDoor();
  }
}


void rfidModule(){
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  String ID_key = "";
  for (byte i = 0; i < 4; i++) {
    ID_key +=
    (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
    String(rfid.uid.uidByte[i], HEX) +
    (i!=3 ? ":" : "");
  }
  ID_key.toUpperCase();

  Serial.print("Card key: ");
  Serial.println(ID_key);

  validateCard(ID_key);

  delay(1000);

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}