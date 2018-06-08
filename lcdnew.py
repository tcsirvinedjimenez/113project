from RPLCD import CharLCD
lcd = CharLCD(cols=16, rows=2, pin_rs=26, pin_e=19, pins_data=[13, 06, 05, 11])
lcd.write_string(u'Hello world!')