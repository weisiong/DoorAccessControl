#include <Arduino.h>
#include "DoorControl.h"

#define DOOR_PIN 2

void DOOR_CONTROL::setup() {
  pinMode(DOOR_PIN, OUTPUT);
}

void DOOR_CONTROL::Open(int closeAfterSecs)
{
   Serial.println("DoorOpen" );
   digitalWrite(DOOR_PIN, LOW);
   delay(closeAfterSecs);
   Close();
}

void DOOR_CONTROL::Close()
{
  Serial.println("DoorClose");
  digitalWrite(DOOR_PIN, HIGH);
}
