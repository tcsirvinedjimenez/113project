nclude <stdio.h>
#include <wiringPi.h>

// LED Pin - wiringPi pin 0 is BCM_GPIO 17.

#define TRIG 12
#define ECHO 3

int main (void)
{
    printf ("Raspberry Pi Sonic Measurement \n") ;
    float start_time;
    float end_time;
    int distance;

    wiringPiSetup () ;
    pinMode (TRIG, OUTPUT) ;
    pinMode (ECHO, INPUT) ;
    //pullUpDnControl(SWITCH, PUD_UP);
    digitalWrite(TRIG,LOW);
    delay(2000);

    digitalWrite(TRIG,HIGH);
    delay(1);
    digitalWrite(TRIG,LOW):

    while(!digitalRead(ECHO))
    {
	
    } 

    while(digitalRead(ECHO))
    {
	
    } 	
     
    return 0 ;
}
