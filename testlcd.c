#include <wiringPi.h>           //WiringPi headers
#include <lcd.h>                //LCD headers from WiringPi
#include <stdio.h>              //Needed for the printf function below
#include <time.h>
#include <ctype.h>

//Pin numbers below are the WiringPi pin numbers

#define LCD_RS  11               //Register select pin
#define LCD_E   10               //Enable Pin
#define LCD_D4  6               //Data pin 4
#define LCD_D5  5               //Data pin 5
#define LCD_D6  4               //Data pin 6
#define LCD_D7  1               //Data pin 7

int main()
{
    int lcd;                //Handle for LCD
    wiringPiSetup();        //Initialise WiringPi

    //Initialise LCD(int rows, int cols, int bits, int rs, int enable, int d0, int d1, int d2, int d3, int d4, int d5, int d6, int d7)
    if (lcd = lcdInit (2, 16,4, LCD_RS, LCD_E ,LCD_D4 , LCD_D5, LCD_D6,LCD_D7,0,0,0,0)){
            printf ("lcd init failed! \n");
            return -1 ;
    }
    lcdPosition(lcd,0,0);  //Position cursor on the first line in the first column
    lcdPuts(lcd, "HELLO WORLD");  //Print the text on the LCD at the current cursor postion
    getchar();                      //Wait for key press
	 while(1){
        time_t timer;
        char buffer_date[26];
        char buffer_time[26];
        struct tm* tm_info;

        time(&timer);
        tm_info = localtime(&timer);

        strftime(buffer_date, 26, "%m-%d %H:%M", tm_info);
        //strftime(buffer_time, 26, "Time: %H:%M:%S", tm_info);

        lcdPosition(lcd, 0, 0);
        lcdPuts(lcd, buffer_date);

        //lcdPosition(lcd, 0, 1);
       // lcdPuts(lcd, buffer_time);

	}
}
