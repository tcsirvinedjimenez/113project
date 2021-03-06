#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <pcf8591.h>
#include <unistd.h>
#define address 0x48
#define pinbase 64
#define A0 pinbase + 0 
#define A1 pinbase + 1 
#define A2 pinbase + 2 
#define A3 pinbase + 3
#include <time.h>
#include <ctype.h>

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
	if(Does_File_Exist("/var/tmp/mail")){
		system("su - pi -c \"rm /var/tmp/mail\"");
	}
	if(Does_File_Exist("/var/tmp/mailcopy")){
		system("su - pi -c \"rm /var/tmp/mailcopy\"");
	}
	printf("Process Starting\n");
	while(1){
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


int Does_File_Exist(char *filename){
   FILE *fp = fopen (filename, "r");
   if (fp!=NULL){ 
	fclose(fp);
   }
   return (fp!=NULL);
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

/*int value;
	float voltage;
	wiringPiSetup();
	pcf8591Setup();
	while(1){
		value= analogRead(A0);
		analogWrite(pinbase+0,value);
		voltage= (float)value/255.0 * 3.3;
		print("ADC value : ,\tVoltage : %.2fV\n",value,voltage);
		delay(100);
	}
*/