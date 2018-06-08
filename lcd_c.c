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
void delay(void);

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
	sendString("EdSim51 LCD Module Simulation");
	setDdRamAddress(0x40); // set address to start of second line
	sendString("Based on Hitachi HD44780");
}

// LCD Module instructions -------------------------------------------
// To understand why the pins are being set to the particular values in the functions
// below, see the instruction set.
// A full explanation of the LCD Module: HD44780.pdf

void returnHome(void) {
	ditigalWrite(RS,LOW);
	ditigalWrite(DB7,LOW);
	ditigalWrite(DB6,LOW);
	ditigalWrite(DB5,LOW);
	ditigalWrite(DB4,LOW);
	ditigalWrite(E,HIGH);
	ditigalWrite(E,LOW);
	ditigalWrite(DB5,HIGH);
	ditigalWrite(E,HIGH);
	ditigalWrite(E,LOW);
	delay();
}	

void entryModeSet(int id, int s) {
	ditigalWrite(RS,LOW);
	ditigalWrite(DB7,LOW);
	ditigalWrite(DB6,LOW);
	ditigalWrite(DB5,LOW);
	ditigalWrite(DB4,LOW);
	ditigalWrite(E,HIGH);
	ditigalWrite(E,LOW);
	ditigalWrite(DB6,HIGH);
	if(id == 1){
		ditigalWrite(DB5,HIGH);
	}else if(id == 0){
		ditigalWrite(DB5,LOW); 
	}
	if(s == 1){
		ditigalWrite(DB4,HIGH);
	}else if(s == 0){
		ditigalWrite(DB4,LOW); 
	}
	ditigalWrite(E,HIGH);
	ditigalWrite(E,LOw);
	delay();
}

void displayOnOffControl(int display, int cursor, int blinking) {
	ditigalWrite(DB7,LOW);
	ditigalWrite(DB6,LOW);
	ditigalWrite(DB5,LOW);
	ditigalWrite(DB4,LOW);
	ditigalWrite(E,HIGH);
	ditigalWrite(E,LOW);
	ditigalWrite(DB7,HIGH);
	if(display == 1){
		ditigalWrite(DB6,HIGH);
	}else if(display == 0){
		ditigalWrite(DB6,LOW); 
	}
	if(cursor == 1){
		ditigalWrite(DB5,HIGH);
	}else if(cursor == 0){
		ditigalWrite(DB5,LOW); 
	}
	if(blinking == 1){
		ditigalWrite(DB4,HIGH);
	}else if(blinking == 0){
		ditigalWrite(DB4,LOW); 
	}
	ditigalWrite(E,HIGH);
	ditigalWrite(E,LOW);
	delay();
}

void cursorOrDisplayShift(int sc, int rl) {
	ditigalWrite(RS,LOW);
	ditigalWrite(DB7,LOW);
	ditigalWrite(DB6,LOW);
	ditigalWrite(DB5,LOW);
	ditigalWrite(DB4,HIGH);
	ditigalWrite(E,HIGH);
	ditigalWrite(E,LOW);
	if(sc == 1){
		ditigalWrite(DB7,HIGH);
	}else if(sc == 0){
		ditigalWrite(DB7,LOW); 
	}
	if(rl == 1){
		ditigalWrite(DB6,HIGH);
	}else if(rl == 0){
		ditigalWrite(DB6,LOW); 
	}
	ditigalWrite(E,HIGH);
	ditigalWrite(E,LOW);
	delay();
}

void functionSet(void) {
	// The high nibble for the function set is actually sent twice. Why? See 4-bit operation
	// on pages 39 and 42 of HD44780.pdf.
	ditigalWrite(DB7,LOW);
	ditigalWrite(DB6,LOW);
	ditigalWrite(DB5,HIGH);
	ditigalWrite(DB4,LOW);
	ditigalWrite(RS,LOW);
	ditigalWrite(E,HIGH);
	ditigalWrite(E,LOW);
	delay();
	ditigalWrite(E,HIGH);
	ditigalWrite(E,LOW);
	ditigalWrite(DB7,HIGH);
	ditigalWrite(E,HIGH);
	ditigalWrite(E,LOW);
	delay();
}

void setDdRamAddress(char address) {
	ditigalWrite(RS,LOW);
	ditigalWrite(DB7,HIGH);
	if(getBit(address, 6) == 1){
		ditigalWrite(DB6,HIGH);
	}else{
		ditigalWrite(DB6,LOW); 
	}
	if(getBit(address, 5) == 1){
		ditigalWrite(DB5,HIGH);
	}else{
		ditigalWrite(DB5,LOW); 
	}
	if(getBit(address, 4) == 1){
		ditigalWrite(DB4,HIGH);
	}else{
		ditigalWrite(DB4,LOW); 
	}
	ditigalWrite(E,HIGH);
	ditigalWrite(E,LOW);
	if(getBit(address, 3) == 1){
		ditigalWrite(DB7,HIGH);
	}else{
		ditigalWrite(DB7,LOW); 
	}
	if(getBit(address, 2) == 1){
		ditigalWrite(DB6,HIGH);
	}else{
		ditigalWrite(DB6,LOW); 
	}
	if(getBit(address, 1) == 1){
		ditigalWrite(DB5,HIGH);
	}else{
		ditigalWrite(DB5,LOW); 
	}
	if(getBit(address, 0) == 1){
		ditigalWrite(DB4,HIGH);
	}else{
		ditigalWrite(DB4,LOW); 
	}
	ditigalWrite(E,HIGH);
	ditigalWrite(E,LOW);
	delay();
}

void sendChar(char c) {
	if(getBit(c, 7) == 1){
		ditigalWrite(DB7,HIGH);
	}else{
		ditigalWrite(DB7,LOW); 
	}
	if(getBit(c, 6) == 1){
		ditigalWrite(DB6,HIGH);
	}else{
		ditigalWrite(DB6,LOW); 
	}
	if(getBit(c, 5) == 1){
		ditigalWrite(DB5,HIGH);
	}else{
		ditigalWrite(DB5,LOW); 
	}
	if(getBit(c, 4) == 1){
		ditigalWrite(DB4,HIGH);
	}else{
		ditigalWrite(DB4,LOW); 
	}
	ditigalWrite(RS,HIGH);
	ditigalWrite(E,HIGH);
	ditigalWrite(E,LOW);
	if(getBit(c, 3) == 1){
		ditigalWrite(DB7,HIGH);
	}else{
		ditigalWrite(DB7,LOW); 
	}
	if(getBit(c, 2) == 1){
		ditigalWrite(DB6,HIGH);
	}else{
		ditigalWrite(DB6,LOW); 
	}
	if(getBit(c, 1) == 1){
		ditigalWrite(DB5,HIGH);
	}else{
		ditigalWrite(DB5,LOW); 
	}
	if(getBit(c, 0) == 1){
		ditigalWrite(DB4,HIGH);
	}else{
		ditigalWrite(DB4,LOW); 
	}
	ditigalWrite(E,HIGH);
	ditigalWrite(E,LOW);
	delay();
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

void delay(void) {
	char c;
	for (c = 0; c < 50; c++);
}
