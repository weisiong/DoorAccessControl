#include <Wire.h> 
#include "LiquidCrystal_I2C.h"
#include "LCD_I2C.h"
//I2C pins declaration
LiquidCrystal_I2C lcdiic(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

void LCD_I2C::setup() {
	lcdiic.begin(16,2);//Defining 16 columns and 2 rows of lcd display
	lcdiic.backlight();//To Power ON the back light
	//lcdiic.backlight();// To Power OFF the back light
}

void LCD_I2C::Display(String Message, int x, int y)
{
	lcdiic.setCursor(x,y);
	lcdiic.print(Message);
}

void LCD_I2C::loop()
{
   //Write your code
	lcdiic.setCursor(0,0); //Defining positon to write from first row,first column .
	lcdiic.print(" E7 Tech Demo "); //You can write 16 Characters per line .
	delay(1000);//Delay used to give a dynamic effect
	lcdiic.setCursor(0,1);  //Defining positon to write from second row,first column .
	lcdiic.print(" Like | Share");
	delay(8000); 

	lcdiic.clear();//Clean the screen
	lcdiic.setCursor(0,0); 
	lcdiic.print(" SUBSCRIBE ");
	lcdiic.setCursor(0,1);
	lcdiic.print(" E7 Tech ");
	delay(8000); 
}
