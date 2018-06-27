#include <Arduino.h>
#include "Declaration.h"
#include <TimedEvent.h>
#include "RfidReader.h"
#include "WebClient.h"
#include "DoorControl.h"
#include "LCD_I2C.h"

RFID_READER reader;
WEB_CLIENT wc;
DOOR_CONTROL door;
LCD_I2C lcd;

void setup() {
  Serial.begin(9600);
  Serial.println(F("Initializing..."));
  reader.setup();
  door.setup();
  lcd.setup();
  wc.setup();
  TimedEvent.addTimer(500, event_rfid);
  TimedEvent.addTimer(20000, event_lcd);
  Serial.println(F("Initialized."));
  lcd.Display("Ready.",0,0);
}

void event_rfid(TimerInformation* Sender) {
  if(reader.ReadTag(UUID))
  {
    Serial.print("Card Detected. ");
    Serial.println("ID: " + UUID);
    lcd.Display(UUID,0,0);
    lcd.Display("           ",0,1);
    //http://210.19.20.195/tll/IOT/testid.asp?ID=12345678
    //http://210.19.20.195/tll/IOT/testid2.asp?ID=12345678

    String URL = "/tll/IOT/testid2.asp?ID=" + UUID;
   
    String respBody="";
    int respCode=-1;
    int ret = wc.webget(URL, respBody, respCode);
    if(ret==0)
    {
      //Serial.println("respCode: " + String(respCode));
      Serial.println("response: " + respBody);
      int resp = respBody.toInt();
      if(resp==0) {lcd.Display("0-Ignore  ",0,1);}
      if(resp==1) {lcd.Display("1-Door    ",0,1); openDoor();}   
      if(resp==2) {lcd.Display("2-Wait    ",0,1);}
      if(resp==3) {lcd.Display("3-Beep    ",0,1); door.BuzzerON();delay(500);door.BuzzerOFF();}
    }
  }
}
void openDoor()
{
  lcd.Display("OPEN      ",0,1);
  door.Open(3000);
  lcd.Display("CLOSE     ",0,1);
}

void event_lcd(TimerInformation* Sender) {
//   lcd.loop();
}

void loop() {
   TimedEvent.loop();
}
