#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>
#include <ctype.h>
#include <lcd.h>

#define LCD_RS  11               //Register select pin
#define LCD_E   10               //Enable Pin
#define LCD_D4  6               //Data pin 4
#define LCD_D5  5               //Data pin 5
#define LCD_D6  4               //Data pin 6
#define LCD_D7  1               //Data pin 7

int Check_In_Email(char *str);
int Does_File_Exist(char *filename);

int main(int argc, char** argv)
{
	char emailname[]="6192194457@pm.sprint.com";
	char strtemp[]="temp?";
	int check[2]={0};
	char temp[256];
	char temp2[256];
	float temperature=0.0;
	time_t timer;
    char buffer1[26];
    char buffer2[26];
    struct tm* tm_info;
	
	int lcd;                
    wiringPiSetup();
	
	if (lcd = lcdInit (2, 16,4, LCD_RS, LCD_E ,LCD_D4 , LCD_D5, LCD_D6,LCD_D7,0,0,0,0)){
            printf ("lcd init failed! \n");
            return -1 ;
    }
	
	if(Does_File_Exist("/var/tmp/mail")){
		system("su - pi -c \"rm /var/tmp/mail\"");
	}
	if(Does_File_Exist("/var/tmp/mailcopy")){
		system("su - pi -c \"rm /var/tmp/mailcopy\"");
	}
	printf("Process Starting\n");
	while(1){

        time(&timer);
        tm_info = localtime(&timer);
        
		strftime(buffer1, 26, "    %H:%M:%S", tm_info);  
        strftime(buffer2, 26, "%m:%d:%Y Temp:", tm_info);
		lcdPosition(lcd, 0, 0);
        lcdPuts(lcd, buffer1);
		lcdPosition(lcd, 0, 1);
        lcdPuts(lcd, buffer2);
		
		system("su - pi -c \"fetchmail > /dev/null\"");
		if(Does_File_Exist("/var/tmp/mail")){
			check[0]=Check_In_Email(emailname);
			if(check[0]==-1){
				printf("File Error 0\n");
			}
			else if(check[0]){
				printf("Message Recieved\n");
			}
			//check for temp command
			check[1]=Check_In_Email(strtemp);
			if(check[1]==-1){
				printf("File Error 1\n");
			}
			else if(check[1]){
				strcpy(temp, "echo \"Rasberry Pi\" | mail -s \"Temperature is ");
				gcvt(temperature, 6, temp2);
				strcat(temp,temp2);
				strcat(temp, "\" dannyjim2020@gmail.com");
				system(temp);
			}
		}
		if(Does_File_Exist("/var/tmp/mail")){
			system("su - pi -c \"rm /var/tmp/mail\"");
		}
	}
   
   return 0;
}