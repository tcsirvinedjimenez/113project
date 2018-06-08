from RPLCD-0.4.0 import CharLCD
lcd = CharLCD(cols=16, rows=2, pin_rs=26, pin_e=19, pins_data=[13, 6, 5, 11])
lcd.write_string(u'Hello world!')