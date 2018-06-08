#include <stdio.h>
#include <wiringPi.h>
#include <time.h> 
#include <math.h>

#define	APIN 2
#define BPIN 7 

int main (void)
{
  printf ("Raspberry Pi Temp\n") ;
  
  wiringPiSetup () ;
  struct timespec start, end;
	double temp = 0;
	int i;
	for(i = 0; i<100; i++){
	  pinMode (APIN, INPUT);
  	pinMode (BPIN, OUTPUT);
		digitalWrite(BPIN,LOW);
		delay(100);
  	pinMode (BPIN, INPUT);
  	pinMode (APIN, OUTPUT);
		digitalWrite(APIN,HIGH);
		clock_gettime(CLOCK_MONOTONIC_RAW, &start);
		while(!digitalRead(BPIN)){
			continue;
		}
		clock_gettime(CLOCK_MONOTONIC_RAW, &end);
		temp = temp + (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_nsec - start.tv_nsec) / 1000.0;	
		printf("looped \n");	
	}
	double reading = temp/100.0;
	double resistance = reading * 6.05 - 939;
	float b = 3800.0;
	float r0 = 1000.0;
	float t0 = 273.15;
	float t25 = t0 + 25.0;
	float inv_T = (1.0/t25) + (1.0/b) * log(resistance/r0); 
	float real_temp = .9 * ((1.0/inv_T)-t0);
	printf("Temp: %f \n");

  return 0 ;
}
