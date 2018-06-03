#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <pcf8591.h>
#define address 0x48
#define pinbase 64
#define A0 pinbase + 0 
#define A1 pinbase + 1 
#define A2 pinbase + 2 
#define A3 pinbase + 3

int Check_In_Email(char *str);
 
int main(int argc, char** argv)
{
	char emailname[]="6192194457@pm.sprint.com";
	int check;
	system("su - pi -c \"fetchmail > /dev/null\"");
	while(1){
		check=Check_In_Email(emailname);
		if(check==-1){
			printf("Error");
			break;
		}
		else if(check){
			while(1){
				printf("Message Recieved");
			}
		}
	}
   
   return 0;
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
	if(fp) {
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