#ifndef HEADER_LED_AND_KEY
#define HEADER_LED_AND_KEY

class LED_AND_KEY{
    public:
      void setup(void);
      void loop();
      void setLed(uint8_t value, uint8_t position);
      uint8_t readButtons(void);
      void reset();
      void sendCommand(uint8_t value);
      bool isButtonPressed(int buttonPos);
      void setDspSeg(uint8_t value, uint8_t position);
      byte BCD2HEXSEG(int Digit);
      byte ASC2HEXSEG(char Digit);
      void Display(String Message);
};
   
#endif
