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

	}
	double reading = temp/100.0;
	double resistance = reading * 6.05 - 72.0;
	printf("R: %f\n",resistance);
  return 0 ;
}
