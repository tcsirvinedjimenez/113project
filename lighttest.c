#include <stdio.h>
#include <wiringPi.h>


#define	LED	15
#define SWITCH 4
#define LIGHT 16 

int main (void)
{
  printf ("Raspberry Pi blink\n") ;
  
  wiringPiSetup () ;
  pinMode (LED, OUTPUT) ;
  pinMode (LIGHT, INPUT) ;
  //pullUpDnControl(SWITCH, PUD_UP);

  while(1)
  {
    int count = 0;
    wiringPiSetup () ;
    pinMode (LIGHT, OUTPUT) ;
    digitalWrite(LIGHT,LOW);
    delay(100);

    pinmode(LIGHT,INPUT);

    while(!digitalRead(LIGHT)){
      count += 1;
    }
    printf("count: %d \n",count);
  }
  return 0 ;
}