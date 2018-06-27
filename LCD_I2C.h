#ifndef HEADER_LCD_I2C
#define HEADER_LCD_I2C

class LCD_I2C{
    public:
      void setup(void);
      void loop();
      void Display(String Message, int x, int y);
};
   
#endif
