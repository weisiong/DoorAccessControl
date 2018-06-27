#include <Arduino.h>
#include "DoorControl.h"

#define DOOR_PIN 2
#define BUZZER_PIN 6

void DOOR_CONTROL::setup() {
  pinMode(DOOR_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void DOOR_CONTROL::Open(int closeAfterSecs)
{
   Serial.println("DoorOpen" );
   digitalWrite(DOOR_PIN, LOW);
   BuzzerON();
   delay(closeAfterSecs);
   Close();
   BuzzerOFF();
}

void DOOR_CONTROL::Close()
{
  Serial.println("DoorClose");
  digitalWrite(DOOR_PIN, HIGH);
}

void DOOR_CONTROL::BuzzerON()
{
  Serial.println("BuzzerON");
  digitalWrite(BUZZER_PIN, HIGH);
  //delay(1000);
  //digitalWrite(BUZZER_PIN, LOW);
}

void DOOR_CONTROL::BuzzerOFF()
{
  Serial.println("BuzzerOFF");
  digitalWrite(BUZZER_PIN, LOW);
}
