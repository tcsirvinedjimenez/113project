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


static const int segmentDigits [] =
{
// a  b  c  d  e  f  g     Segments
// 6  5  4  3  2  1  0,	// wiringPi pin No.

   1, 1, 1, 1, 1, 1, 0,	// 0
   0, 1, 1, 0, 0, 0, 0,	// 1
   1, 1, 0, 1, 1, 0, 1,	// 2
   1, 1, 1, 1, 0, 0, 1,	// 3
   0, 1, 1, 0, 0, 1, 1,	// 4
   1, 0, 1, 1, 0, 1, 1,	// 5
   1, 0, 1, 1, 1, 1, 1,	// 6
   1, 1, 1, 0, 0, 0, 0,	// 7
   1, 1, 1, 1, 1, 1, 1,	// 8
   1, 1, 1, 1, 0, 1, 1,	// 9
   1, 1, 1, 0, 1, 1, 1,	// A
   0, 0, 1, 1, 1, 1, 1,	// b
   1, 0, 0, 1, 1, 1, 0,	// C
   0, 1, 1, 1, 1, 0, 1,	// d
   1, 0, 0, 1, 1, 1, 1,	// E
   1, 0, 0, 0, 1, 1, 1,	// F
   0, 0, 0, 0, 0, 0, 0,	// blank
} ;

char display [8] ;
//these are the pins
static int digits   [6] = {  7, 11, 10, 13, 12, 14    } ;
static int segments [7] = {  6,  5,  4,  3,  2,  1, 0 } ;



PI_THREAD (displayDigits)
{
  int digit, segment ;
  int index, d, segVal ;

  piHiPri (50) ;

  for (;;)
  {
    for (digit = 0 ; digit < 6 ; ++digit)
    {
      for (segment = 0 ; segment < 7 ; ++segment)
      {
	d = toupper (display [digit]) ;
	/**/ if ((d >= '0') && (d <= '9'))	// Digit
	  index = d - '0' ;
	else if ((d >= 'A') && (d <= 'F'))	// Hex
	  index = d - 'A' + 10 ;
	else
	  index = 16 ;				// Blank

	segVal = segmentDigits [index * 7 + segment] ;

	digitalWrite (segments [segment], segVal) ;
      }
      digitalWrite (digits [digit], 1) ;
      delay (2) ;
      digitalWrite (digits [digit], 0) ;
    }
  }
}
int main(int argc, char** argv){
	int i, c ;

	wiringPiSetup () ;

	// 7 segments
	for (i = 0 ; i < 7 ; ++i){
		digitalWrite(segments [i],0); 
		pinMode (segments [i], OUTPUT); 
	}

	// 6 digits
	for (i = 0 ; i < 6 ; ++i){ 
		digitalWrite(digits[i],0);   
		pinMode (digits[i],OUTPUT); 
	}

	strcpy (display, "      ") ;
	piThreadCreate (displayDigits) ;
	delay (10) ;
	while(1){
		while (time (NULL) == tim){
			delay(5);
		}
		delay(5);
		tim = time (NULL) ;
		t = localtime (&tim) ;
		sprintf (display, "%02d%02d%02d", t->tm_hour, t->tm_min, t->tm_sec) ;
	}
	return 0;
}
