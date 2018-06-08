#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>
#include <ctype.h>
#include <lcd.h>

#define LCD_RS  11               //Register select pin
#define LCD_E   21               //Enable Pin
#define LCD_D4  22               //Data pin 4
#define LCD_D5  23               //Data pin 5
#define LCD_D6  24               //Data pin 6
#define LCD_D7  25               //Data pin 7
#define SWITCH 4
#define LED 15

int Check_In_Email(char *str);
int Does_File_Exist(char *filename);
void messagecode(int temperature);

int main(int argc, char** argv)
{
	
	char temp[256];
	char temp2[256];
	int temperature=0;
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
	
	//led  and switch code
	pinMode (SWITCH, INPUT) ;
    pullUpDnControl(SWITCH, PUD_UP);
	pinMode (LED, OUTPUT) ;
	
	printf("Process Starting\n");
	while(1){
		if(digitalRead(SWITCH)){
			digitalWrite (LED, LOW) ;
			time(&timer);
			tm_info = localtime(&timer);
			
			strftime(buffer1, 26, "%H:%M:%S  Temp", tm_info);  
			strftime(buffer2, 26, "%m:%d:%Y  ", tm_info);
			gcvt(temperature, 6, temp2);
			strcat(buffer2,temp2);
			lcdPosition(lcd, 0, 0);
			lcdPuts(lcd, buffer1);
			lcdPosition(lcd, 0, 1);
			lcdPuts(lcd, buffer2);
			messagecode(temperature);
		}
		else{
			digitalWrite (LED, HIGH) ;
			strcpy(buffer1,"out-of-home");
			lcdPosition(lcd, 0, 0);
			lcdPuts(lcd, buffer1);
			messagecode(temperature);
			//if(/*motion or light detect*/){
				//strcpy(buffer1,"Intruder Detected");
				//lcdPuts(lcd, buffer1);
				//lcdPosition(lcd, 0, 1);
				
				//system("echo \"Rasberry Pi\" | mail -s \"Intruder detected Turn off Alarm?\" 6192194457@pm.sprint.com");
				
			//}
		}
		
		
	}
   
   return 0;
}
int Does_File_Exist(char *filename){
   FILE *fp = fopen (filename, "r");
   if (fp!=NULL){ 
	fclose(fp);
   }
   return (fp!=NULL);
}

void messagecode(int temperature){
	int check[2]={0};
	char emailname[]="6192194457@pm.sprint.com";
	char strtemp[]="temp?";
	char temp[256];
	char temp2[256];
	
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


int Check_In_Email(char *str){
	FILE *fp;
	int count = 0;
	char temp[512];
	
	if((fp = fopen("/var/tmp/mail", "r")) == NULL) {
		return(-1);
	}
	while(fgets(temp, 512, fp) != NULL) {
		if((strstr(temp, str)) != NULL) {
			count++;
		}
	}
	if(fp!=NULL) {
		fclose(fp);
	}
	if(count > 0) {
		return(1);
	}
	else{
		return(0);
	}
   	

}