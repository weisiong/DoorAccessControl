#include <Arduino.h>
#include "Declaration.h"
#include <TimedEvent.h>
#include "RfidReader.h"
#include "WebClient.h"
#include "DoorControl.h"
#include "LednKey.h"

RFID_READER reader;
WEB_CLIENT wc;
DOOR_CONTROL door;
LED_AND_KEY lednkey;

void setup() {
  Serial.begin(9600);
  Serial.println(F("Initializing..."));
  reader.setup();
  door.setup();
  lednkey.setup();
  wc.setup();
  TimedEvent.addTimer(500, event_rfid);
  TimedEvent.addTimer(500, event_lednkey);
  Serial.println(F("Initialized."));
}

void event_rfid(TimerInformation* Sender) {
  if(reader.ReadTag(UUID))
  {
    Serial.print("Card Detected. ");
    Serial.println("ID: " + UUID);
    lednkey.Display(UUID);
    String URL = "/api/DoorAccess?id=" + UUID;
    String respBody="";
    int respCode=-1;
    int ret = wc.webget(URL, respBody, respCode);
    if(ret==0)
    {
      //Serial.println("respCode: " + String(respCode));
      Serial.println("response: " + respBody);
      if(respBody=="\"Pass\"") openDoor();      
      if(respBody=="\"Fail\"") lednkey.Display("FAIL");
    }
    
  }
}

void openDoor()
{
  lednkey.Display("OPEN");
  door.Open(3000);
  lednkey.Display("CLOSE");
}

void event_lednkey(TimerInformation* Sender) {
   lednkey.loop();
   bool btnState = lednkey.isButtonPressed(0);
   if(btnState)
   {
      lednkey.setLed(0,btnState);
      openDoor();
   }

   btnState = lednkey.isButtonPressed(1);
   if(btnState)
   {
      lednkey.setLed(1,btnState);
      lednkey.Display("FAIL");
   }
   
   //lednkey.setLed(5, lednkey.isButtonPressed(5));
   //lednkey.setLed(7, lednkey.isButtonPressed(7));
}

void loop() {
   TimedEvent.loop();
}
