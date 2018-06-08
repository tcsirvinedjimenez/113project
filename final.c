#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>
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