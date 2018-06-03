#include <stdio.h>
#include <wiringPi.h>

// LED Pin - wiringPi pin 0 is BCM_GPIO 17.

#define	LED  15
#define SWITCH 4
#define LIGHT 16

int main (void)
{
  printf ("Raspberry Pi blink\n") ;
  
  wiringPiSetup () ;
  pinMode (LED, OUTPUT) ;
  pinMode (LIGHT, INPUT);
  //pinMode (SWITCH, INPUT) ;
  pullUpDnControl(LIGHT, PUD_OFF);

  while(1)
  {
    //if(digitalRead(LIGHT)){
      //digitalWrite (LED, HIGH) ;// On
    //}else{
      //digitalWrite (LED, LOW) ;	// Off
    //}
	if(digitalRead(LIGHT)){
		printf("on \n");
		delay(1000);
	}
	else{
		printf("off \n");
		delay(1000);
	}	
  }
  return 0 ;
}