#include <Arduino.h>
#include "LednKey.h"

#define STB_PIN 5
#define CLK_PIN 6
#define DAT_PIN 7

void LED_AND_KEY::sendCommand(uint8_t value)
{
  digitalWrite(STB_PIN, LOW);
  shiftOut(DAT_PIN, CLK_PIN, LSBFIRST, value);
  digitalWrite(STB_PIN, HIGH);
}

void LED_AND_KEY::reset()
{
  sendCommand(0x40); // set auto increment mode
  digitalWrite(STB_PIN, LOW);
  shiftOut(DAT_PIN, CLK_PIN, LSBFIRST, 0xc0);   // set starting address to 0
  for(uint8_t i = 0; i < 16; i++)
  {
    shiftOut(DAT_PIN, CLK_PIN, LSBFIRST, 0x00);
  }
  digitalWrite(STB_PIN, HIGH);
}

void LED_AND_KEY::setup() {
  pinMode(STB_PIN, OUTPUT);
  pinMode(CLK_PIN, OUTPUT);
  pinMode(DAT_PIN, OUTPUT);

  sendCommand(0x8f);  // activate
  reset();
}

uint8_t LED_AND_KEY::readButtons(void)
{
  uint8_t buttons = 0;
  digitalWrite(STB_PIN, LOW);
  shiftOut(DAT_PIN, CLK_PIN, LSBFIRST, 0x42);

  pinMode(DAT_PIN, INPUT);

  for (uint8_t i = 0; i < 4; i++)
  {
    uint8_t v = shiftIn(DAT_PIN, CLK_PIN, LSBFIRST) << i;
    buttons |= v;
  }

  pinMode(DAT_PIN, OUTPUT);
  digitalWrite(STB_PIN, HIGH);
  return buttons;
}


void LED_AND_KEY::setLed(uint8_t position,uint8_t value)
{
  pinMode(DAT_PIN, OUTPUT);
  sendCommand(0x44);
  digitalWrite(STB_PIN, LOW);
  shiftOut(DAT_PIN, CLK_PIN, LSBFIRST, 0xC1 + (position << 1));
  shiftOut(DAT_PIN, CLK_PIN, LSBFIRST, value);
  digitalWrite(STB_PIN, HIGH);
}

bool LED_AND_KEY::isButtonPressed(int buttonPos)
{
  uint8_t buttons = readButtons();
  uint8_t mask = 0x1 << buttonPos;
  return ( (buttons & mask) == mask?true:false);
}

void LED_AND_KEY::loop()
{
   //setDspSeg(10, 0);
   //setDspSeg(11, 1);
   //setDspSeg(12, 2);
   //setDspSeg(13, 3);
   //setDspSeg(14, 4);
   //setDspSeg(15, 5);
   //setDspSeg(1, 6);
   //setDspSeg(0, 7);

  //setLed(3, isButtonPressed(3));
  //setLed(5, isButtonPressed(5));
  //setLed(7, isButtonPressed(7));
}

void LED_AND_KEY::setDspSeg(uint8_t value, uint8_t position)
{
  pinMode(DAT_PIN, OUTPUT); 
  sendCommand(0x44);
  digitalWrite(STB_PIN, LOW);
  shiftOut(DAT_PIN, CLK_PIN, LSBFIRST, 0xC0 + (position << 1));
  byte bytVal = ASC2HEXSEG(value);   //byte bytVal = BCD2HEXSEG(value);
  shiftOut(DAT_PIN, CLK_PIN, LSBFIRST, bytVal);
  digitalWrite(STB_PIN, HIGH);
}

void LED_AND_KEY::Display(String Message)
{
    char s[9];
    Message.toCharArray(s,9);
    for (int i = 0; i < sizeof(s) - 1; i++)
    {
      //Serial.print(char(s[i]));
      setDspSeg(s[i], i);
    }
    //Serial.println("");
}


byte LED_AND_KEY::ASC2HEXSEG(char Digit)
{
   byte ret1=0;
   switch(Digit)
   {
    case '0': 
    case 'o':
    case 'O':
      ret1 = 0x3F;
      break;
    case '1':
    case 'i':
    case 'I':
      ret1 = 0x06;
      break;
    case '2':
      ret1 = 0x5B;
      break;
    case '3':
      ret1 = 0x4F;
      break;
    case '4':
      ret1 = 0x66;
      break;
    case '5':
    case 's':
    case 'S':
      ret1 = 0x6D;
      break;
    case '6':
      ret1 = 0x7D;
      break;
    case '7':
      ret1 = 0x07;
      break;
    case '8':
      ret1 = 0x7F;
      break;
    case '9':
      ret1 = 0x6F;
      break;
    case 'a':
    case 'A':
      ret1 = 0x77;
      break;
    case 'b':
    case 'B':
      ret1 = 0x7C;
      break;  
    case 'c':
    case 'C':
      ret1 = 0x39;
      break;  
    case 'd':
    case 'D':
      ret1 = 0x5E;
      break;       
    case 'e':
    case 'E':
      ret1 = 0x79;
      break;   
    case 'f':
    case 'F':
      ret1 = 0x71;
      break;
    case 'p':
    case 'P':
      ret1 = 0x73;
      break;       
    case 'n':
    case 'N':
      ret1 = 0x37;
      break;        
    case 'l':
    case 'L':
      ret1 = 0x38;
      break;        
   }
   return ret1;
}


byte LED_AND_KEY::BCD2HEXSEG(int Digit)
{
   byte ret=0;
   switch(Digit)
   {
    case 0:
      ret = 0x3F;
      break;
    case 1:
      ret = 0x06;
      break;
    case 2:
      ret = 0x5B;
      break;
    case 3:
      ret = 0x4F;
      break;
    case 4:
      ret = 0x66;
      break;
    case 5:
      ret = 0x6D;
      break;
    case 6:
      ret = 0x7D;
      break;
    case 7:
      ret = 0x07;
      break;
    case 8:
      ret = 0x7F;
      break;
    case 9:
      ret = 0x6F;
      break;
    case 10:
      ret = 0x77;
      break;
    case 11:
      ret = 0x7C;
      break;  
    case 12:
      ret = 0x58;
      break;  
    case 13:
      ret = 0x5E;
      break;       
    case 14:
      ret = 0x79;
      break;   
    case 15:
      ret = 0x71;
      break;             
   }
   return ret;
}
