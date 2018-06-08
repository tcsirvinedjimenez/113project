#!/usr/bin/env python
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
LCD_RS = 26         #LCD Reset
LCD_E  = 19       #LCD Enable
LCD_D4 = 13         #LCD Bit 4
LCD_D5 = 06         #LCD Bit 5
LCD_D6 = 05         #LCD Bit 6
LCD_D7 = 11         #LCD Bit 7
LCD_WIDTH = 16      #LCD Device Width
LCD_LINE_1 = 0x80   #LCD RAM address for the 1st Line
LCD_LINE_2 = 0xC0   #LCD RAM address for the 2nd Line
E_PULSE = 0.00005   #LCD Pulse Time
E_DELAY = 0.00005   #LCD Delay Time
LCD_CHR = True
LCD_CMD = False
LCDLine1 = ""
LCDLine2 = ""

def lcd_init():
    # Initialise display
    lcd_byte(0x33,LCD_CMD)
    lcd_byte(0x32,LCD_CMD)
    lcd_byte(0x28,LCD_CMD)
    lcd_byte(0x0C,LCD_CMD)
    lcd_byte(0x06,LCD_CMD)
    lcd_byte(0x01,LCD_CMD)

def lcd_string(message):
    # Send string to display
    message = message.ljust(LCD_WIDTH," ")
    for i in range(LCD_WIDTH):
        lcd_byte(ord(message[i]),LCD_CHR)

def lcd_byte(bits, mode):
    # Send byte to data pins
    # bits = data
    # mode = True  for character
    #      = False for command

    GPIO.output(LCD_RS, mode)

    # High bits
    GPIO.output(LCD_D4, False)
    GPIO.output(LCD_D5, False)
    GPIO.output(LCD_D6, False)
    GPIO.output(LCD_D7, False)
    if bits&0x10 == 0x10:
        GPIO.output(LCD_D4, True)
    if bits&0x20 == 0x20:
        GPIO.output(LCD_D5, True)
    if bits&0x40 == 0x40:
        GPIO.output(LCD_D6, True)
    if bits&0x80 == 0x80:
        GPIO.output(LCD_D7, True)

    # Toggle 'Enable' pin
    time.sleep(E_DELAY)
    GPIO.output(LCD_E, True)
    time.sleep(E_PULSE)
    GPIO.output(LCD_E, False)
    time.sleep(E_DELAY)

    # Low bits
    GPIO.output(LCD_D4, False)
    GPIO.output(LCD_D5, False)
    GPIO.output(LCD_D6, False)
    GPIO.output(LCD_D7, False)
    if bits&0x01 == 0x01:
        GPIO.output(LCD_D4, True)
    if bits&0x02 == 0x02:
        GPIO.output(LCD_D5, True)
    if bits&0x04 == 0x04:
        GPIO.output(LCD_D6, True)
    if bits&0x08 == 0x08:
        GPIO.output(LCD_D7, True)

    # Toggle 'Enable' pin
    time.sleep(E_DELAY)
    GPIO.output(LCD_E, True)
    time.sleep(E_PULSE)
    GPIO.output(LCD_E, False)
    time.sleep(E_DELAY)

if __name__=='__main__':
	 try:
		# LCD GPIO Setup
		 GPIO.setup(LCD_E, GPIO.OUT)
		 GPIO.setup(LCD_RS, GPIO.OUT)
		 GPIO.setup(LCD_D4, GPIO.OUT)
		 GPIO.setup(LCD_D5, GPIO.OUT)
		 GPIO.setup(LCD_D6, GPIO.OUT)
		 GPIO.setup(LCD_D7, GPIO.OUT)

		# Initialise display
		 lcd_init()
		 LCDLine1 = "Hello World!"
		 lcd_byte(LCD_LINE_1, LCD_CMD)
		 lcd_string(LCDLine1)
					  
		 while True:  
			 #Wait 1 seconds
			 time.sleep(1)
			 PiTime = time.strftime("Time:  %H:%M:%S", time.localtime())
			 PiDate = time.strftime("Date:%d %b %Y", time.localtime())
			 LCDLine1 = PiDate
			 LCDLine2 = PiTime
			 lcd_byte(LCD_LINE_1, LCD_CMD)
			 lcd_string(LCDLine1)
			 lcd_byte(LCD_LINE_2, LCD_CMD)
			 lcd_string(LCDLine2)
	 except KeyboardInterrupt: 
		 pass
	 # Shutdown         lcd_byte(LCD_LINE_1, LCD_CMD)
	 lcd_string(" Goodbye :)")
	 lcd_byte(LCD_LINE_2, LCD_CMD)
	 lcd_string(" ")
	 GPIO.cleanup()