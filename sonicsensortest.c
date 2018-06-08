#include <stdio.h>
#include <wiringPi.h>
#include <time.h>

// LED Pin - wiringPi pin 0 is BCM_GPIO 17.

#define TRIG 12
#define ECHO 3

int main (void)
{
    printf ("Raspberry Pi Sonic Measurement \n") ;
    struct timespec start, end;
    int distance;

    wiringPiSetup () ;
    pinMode (TRIG, OUTPUT) ;
    pinMode (ECHO, INPUT) ;
    //pullUpDnControl(SWITCH, PUD_UP);
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
	
    uint64_t delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
    distance = delta_us*17150;
    printf("Distance: %f",distance);
     
    return 0 ;
}
