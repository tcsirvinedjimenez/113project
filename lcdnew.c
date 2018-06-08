#include <wiringPi.h>          
#include <lcd.h>               
 
//USE WIRINGPI PIN NUMBERS
#define LCD_RS  27               //Register select pin
#define LCD_E   22               //Enable Pin
#define LCD_D4  25              //Data pin 4
#define LCD_D5  24               //Data pin 5
#define LCD_D6  23               //Data pin 6
#define LCD_D7  18               //Data pin 7
 
int main()
{
    int lcd;               
    wiringPiSetup();        
    lcd = lcdInit (2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0);
               
    lcdPuts(lcd, "Hello, world!");   
}
