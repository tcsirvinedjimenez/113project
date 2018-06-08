#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>
#include <ctype.h>
#include <lcd.h>


#define LCD_RS  14               //Register select pin
#define LCD_E   21               //Enable Pin
#define LCD_D4  22               //Data pin 4
#define LCD_D5  23               //Data pin 5
#define LCD_D6  24               //Data pin 6
#define LCD_D7  25               //Data pin 7
#define SWITCH 13
#define LED 4
#define LED2 15
#define LIGHT 16
#define TRIG 12
#define ECHO 3
#define BUZZ 1

int Check_In_Email(char *str);
int Does_File_Exist(char *filename);
void messagecode(int temperature);
int intruder;
int main(int argc, char** argv)
{
	intruder=0;
	struct timespec start, end;
	double delta_us,oldDelta;
	char temp[256];
	char temp2[256];
	int temperature=75;
	time_t timer;
    char buffer1[26];
    char buffer2[26];
    struct tm* tm_info;
	int count = 0;
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
	pinMode (LED2, OUTPUT) ;
	pinMode (LIGHT, INPUT) ;
	pinMode (TRIG, OUTPUT) ;
    pinMode (ECHO, INPUT) ;
	pinMode (BUZZ, OUTPUT) ;
	digitalWrite (BUZZ, LOW) ;
	
	printf("Process Starting\n");
	while(1){
		if(digitalRead(SWITCH)){
			digitalWrite (LED, LOW) ;
			digitalWrite (LED2, LOW) ;
			time(&timer);
			tm_info = localtime(&timer);
			strftime(buffer1, 26, "%H:%M:%S   Temp", tm_info);  
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
			if(intruder==0){
				strcpy(buffer1,"               ");
				lcdPosition(lcd, 0, 0);
				strcpy(buffer1,"                ");
				lcdPosition(lcd, 0, 1);
				lcdPuts(lcd, buffer1);
			}
			digitalWrite (LED, HIGH) ;
			strcpy(buffer1,"out-of-home     ");
			lcdPosition(lcd, 0, 0);
			lcdPuts(lcd, buffer1);
			messagecode(temperature);
			if(intruder==0){
				count = 0;
				pinMode (LIGHT, OUTPUT) ;
				digitalWrite(LIGHT,LOW);
				delay(100);
				pinMode(LIGHT,INPUT);
				while(!digitalRead(LIGHT)){
					count += 1;
				}
				
				digitalWrite(TRIG,LOW);
				delay(2000);

				digitalWrite(TRIG,HIGH);
				delay(1);
				digitalWrite(TRIG,LOW);

				while(!digitalRead(ECHO))
				{
				clock_gettime(CLOCK_MONOTONIC_RAW, &start);	
				} 

				while(digitalRead(ECHO))
				{
				clock_gettime(CLOCK_MONOTONIC_RAW, &end);	
				} 	
				
				delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
				
				if(count>100000 || (oldDelta>delta_us-2000 && oldDelta<delta_us+2000)){
					strcpy(buffer1,"             ");
					lcdPosition(lcd, 0, 0);
					strcpy(buffer1,"             ");
					lcdPosition(lcd, 0, 1);
					strcpy(buffer1,"Intruder Detected");
					lcdPuts(lcd, buffer1);
					lcdPosition(lcd, 0, 1);
					digitalWrite (LED2, HIGH) ;
					digitalWrite (BUZZ, HIGH) ;
					system("echo \"Rasberry Pi\" | mail -s \"Intruder detected Turn off Alarm?\" 6192194457@pm.sprint.com");
					intruder=1;
				}
				oldDelta=delta_us;
			}
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
				intruder=0;
				digitalWrite(LED2, LOW) ;
				digitalWrite (BUZZ, LOW) ;
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