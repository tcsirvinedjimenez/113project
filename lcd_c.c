#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define DB7 25
#define DB6 24
#define DB5 23
#define DB4 22
#define RS 14
#define E 21

void returnHome(void);
void entryModeSet(int id, int s);
void displayOnOffControl(int display, int cursor, int blinking);
void cursorOrDisplayShift(int sc, int rl);
void functionSet(void);
void setDdRamAddress(char address);

void sendChar(char c);
void sendString(char* str);
int getBit(char c, char bitNumber);

void main(void) {
	// the setup stuff 
	wiringPiSetup();
	pinMode(DB7, OUTPUT);
	pinMode(DB6, OUTPUT);
	pinMode(DB5, OUTPUT);
	pinMode(DB4, OUTPUT);
	pinMode(RS, OUTPUT);
	pinMode(E, OUTPUT);

	functionSet();
	entryModeSet(1, 0); // increment and no shift
	displayOnOffControl(1, 1, 1); // display on, cursor on and blinking on
	setDdRamAddress(0x00);
	sendString("test");
	//setDdRamAddress(0x40); // set address to start of second line
	//sendString("Based on Hitachi HD44780");
	
	while(1){
	}
}

// LCD Module instructions -------------------------------------------
// To understand why the pins are being set to the particular values in the functions
// below, see the instruction set.
// A full explanation of the LCD Module: HD44780.pdf

void returnHome(void) {
	digitalWrite(RS,LOW);
	digitalWrite(DB7,LOW);
	digitalWrite(DB6,LOW);
	digitalWrite(DB5,LOW);
	digitalWrite(DB4,LOW);
	digitalWrite(E,HIGH);
	digitalWrite(E,LOW);
	digitalWrite(DB5,HIGH);
	digitalWrite(E,HIGH);
	digitalWrite(E,LOW);
	delay(100);
}	

void entryModeSet(int id, int s) {
	digitalWrite(RS,LOW);
	digitalWrite(DB7,LOW);
	digitalWrite(DB6,LOW);
	digitalWrite(DB5,LOW);
	digitalWrite(DB4,LOW);
	digitalWrite(E,HIGH);
	digitalWrite(E,LOW);
	digitalWrite(DB6,HIGH);
	if(id == 1){
		digitalWrite(DB5,HIGH);
	}else if(id == 0){
		digitalWrite(DB5,LOW); 
	}
	if(s == 1){
		digitalWrite(DB4,HIGH);
	}else if(s == 0){
		digitalWrite(DB4,LOW); 
	}
	digitalWrite(E,HIGH);
	digitalWrite(E,LOW);
	delay(100);
}

void displayOnOffControl(int display, int cursor, int blinking) {
	digitalWrite(DB7,LOW);
	digitalWrite(DB6,LOW);
	digitalWrite(DB5,LOW);
	digitalWrite(DB4,LOW);
	digitalWrite(E,HIGH);
	digitalWrite(E,LOW);
	digitalWrite(DB7,HIGH);
	if(display == 1){
		digitalWrite(DB6,HIGH);
	}else if(display == 0){
		digitalWrite(DB6,LOW); 
	}
	if(cursor == 1){
		digitalWrite(DB5,HIGH);
	}else if(cursor == 0){
		digitalWrite(DB5,LOW); 
	}
	if(blinking == 1){
		digitalWrite(DB4,HIGH);
	}else if(blinking == 0){
		digitalWrite(DB4,LOW); 
	}
	digitalWrite(E,HIGH);
	digitalWrite(E,LOW);
	delay(100);
}

void cursorOrDisplayShift(int sc, int rl) {
	digitalWrite(RS,LOW);
	digitalWrite(DB7,LOW);
	digitalWrite(DB6,LOW);
	digitalWrite(DB5,LOW);
	digitalWrite(DB4,HIGH);
	digitalWrite(E,HIGH);
	digitalWrite(E,LOW);
	if(sc == 1){
		digitalWrite(DB7,HIGH);
	}else if(sc == 0){
		digitalWrite(DB7,LOW); 
	}
	if(rl == 1){
		digitalWrite(DB6,HIGH);
	}else if(rl == 0){
		digitalWrite(DB6,LOW); 
	}
	digitalWrite(E,HIGH);
	digitalWrite(E,LOW);
	delay(100);
}

void functionSet(void) {
	// The high nibble for the function set is actually sent twice. Why? See 4-bit operation
	// on pages 39 and 42 of HD44780.pdf.
	digitalWrite(DB7,LOW);
	digitalWrite(DB6,LOW);
	digitalWrite(DB5,HIGH);
	digitalWrite(DB4,LOW);
	digitalWrite(RS,LOW);
	digitalWrite(E,HIGH);
	digitalWrite(E,LOW);
	delay(100);
	digitalWrite(E,HIGH);
	digitalWrite(E,LOW);
	digitalWrite(DB7,HIGH);
	digitalWrite(E,HIGH);
	digitalWrite(E,LOW);
	delay(100);
}

void setDdRamAddress(char address) {
	digitalWrite(RS,LOW);
	digitalWrite(DB7,HIGH);
	if(getBit(address, 6) == 1){
		digitalWrite(DB6,HIGH);
	}else{
		digitalWrite(DB6,LOW); 
	}
	if(getBit(address, 5) == 1){
		digitalWrite(DB5,HIGH);
	}else{
		digitalWrite(DB5,LOW); 
	}
	if(getBit(address, 4) == 1){
		digitalWrite(DB4,HIGH);
	}else{
		digitalWrite(DB4,LOW); 
	}
	digitalWrite(E,HIGH);
	digitalWrite(E,LOW);
	if(getBit(address, 3) == 1){
		digitalWrite(DB7,HIGH);
	}else{
		digitalWrite(DB7,LOW); 
	}
	if(getBit(address, 2) == 1){
		digitalWrite(DB6,HIGH);
	}else{
		digitalWrite(DB6,LOW); 
	}
	if(getBit(address, 1) == 1){
		digitalWrite(DB5,HIGH);
	}else{
		digitalWrite(DB5,LOW); 
	}
	if(getBit(address, 0) == 1){
		digitalWrite(DB4,HIGH);
	}else{
		digitalWrite(DB4,LOW); 
	}
	digitalWrite(E,HIGH);
	digitalWrite(E,LOW);
	delay(100);
}

void sendChar(char c) {
	if(getBit(c, 7) == 1){
		digitalWrite(DB7,HIGH);
	}else{
		digitalWrite(DB7,LOW); 
	}
	if(getBit(c, 6) == 1){
		digitalWrite(DB6,HIGH);
	}else{
		digitalWrite(DB6,LOW); 
	}
	if(getBit(c, 5) == 1){
		digitalWrite(DB5,HIGH);
	}else{
		digitalWrite(DB5,LOW); 
	}
	if(getBit(c, 4) == 1){
		digitalWrite(DB4,HIGH);
	}else{
		digitalWrite(DB4,LOW); 
	}
	digitalWrite(RS,HIGH);
	digitalWrite(E,HIGH);
	digitalWrite(E,LOW);
	if(getBit(c, 3) == 1){
		digitalWrite(DB7,HIGH);
	}else{
		digitalWrite(DB7,LOW); 
	}
	if(getBit(c, 2) == 1){
		digitalWrite(DB6,HIGH);
	}else{
		digitalWrite(DB6,LOW); 
	}
	if(getBit(c, 1) == 1){
		digitalWrite(DB5,HIGH);
	}else{
		digitalWrite(DB5,LOW); 
	}
	if(getBit(c, 0) == 1){
		digitalWrite(DB4,HIGH);
	}else{
		digitalWrite(DB4,LOW); 
	}
	digitalWrite(E,HIGH);
	digitalWrite(E,LOW);
	delay(100);
}

// -- End of LCD Module instructions
// --------------------------------------------------------------------

void sendString(char* str) {
	int index = 0;
	while (str[index] != 0) {
		sendChar(str[index]);
		index++;
	}
}

int getBit(char c, char bitNumber) {
	return (c >> bitNumber) & 1;
}
