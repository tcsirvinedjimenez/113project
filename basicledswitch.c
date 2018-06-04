#include <stdio.h>
#include <wiringPi.h>

// LED Pin - wiringPi pin 0 is BCM_GPIO 17.

#define LED 15
#define SWITCH 4

int main (void)
{
      printf ("Raspberry Pi blink\n") ;
        
          wiringPiSetup () ;
            pinMode (LED, OUTPUT) ;
              pinMode (SWITCH, INPUT) ;
                pullUpDnControl(SWITCH, PUD_UP);

                  while(1)
                        {
                                if(digitalRead(SWITCH)){
                                          digitalWrite (LED, HIGH) ;// On
                                              }else{
                                                        digitalWrite (LED, LOW) ;   // Off
                                                            }
                                                              }
                                                                return 0 ;
}
