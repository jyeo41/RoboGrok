import serial

serial = serial.Serial() # open the serial connection
serial.baudrate = 9600
serial.port = 'COM10'   # found in device manager > ports (COM & LPT) > KitProg USB-UART(COM10)
serial.open()

i = bytearray([255]) # this is how we can send numbers between our PSoC and our computer, can only go up to 255

# send information to the PSoC here
# serial.write(b'10') # 'b' means byte
serial.write(i)

serial.close()


# Notes:
# When sending serial.write(b'10') we see on the LCD screen as '48' why?
# This is because we aren't sending the number '10', we are sending the characters '1' and '0'
# So whats ACTUALLY happening is, it's printing out the ASCII code 49 for character '1' then
#   ASCII code 489 for character '0'
