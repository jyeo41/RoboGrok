import serial

serial = serial.Serial() # open the serial connection
serial.baudrate = 9600
serial.port = 'COM10'   # found in device manager > ports (COM & LPT) > KitProg USB-UART(COM10)
serial.open()

i = bytearray([255]) # this is how we can send numbers between our PSoC and our computer, can only go up to 255

# send information to the PSoC here
# serial.write(b'10') # 'b' means byte
serial.write(i)


# read values from the PSoC
byte1 = []
byte2 = []
byte_assembled = []
counter_values = []


j = 0
while (j < 200):    # run both loops 200 times to match the 2 second long move from the PSoC code
    byte1 = bytearray([serial.read()])  # read in first 8 bits of the 16 bit counter
    byte2 = bytearray([serial.read()])  # read in second 8 bits 
    byte_assembled = byte2[0] + (byte1[0] * 256)    # assemble by doing the reverse algorithm, solving for counter
    counter_values.append(byte_assembled)   # save the set of values into the array
    j += 1

j = 0
while (j < 200):
    byte1 = bytearray([serial.read()])
    byte2 = bytearray([serial.read()])
    byte_assembled = byte2[0] + (byte1[0] * 256)
    counter_values.append(byte_assembled)
    j += 1
    

serial.close()

# the array 'b' stores the data sent from the PSoC to the PC so we are writing that data
#   to a text file on our PC in order to paste it to excel and create a graph from it.
# the objective is to run our position control code and send the value of the encoder count
#   over the UART connection and save all those values and plot it on excel so we can precisely see
#   how the motion happens.
file = open("Data.txt", "w")
i = 0
while (i < 400):    # 400 times to account for both moves
    file.write("%d\n" % counter_values[i])   # this is similar to printf() syntax from C
    i += 1


file.close()    # write to file won't be successful unless you close the file
# Notes:
# When sending serial.write(b'10') we see on the LCD screen as '48' why?
# This is because we aren't sending the number '10', we are sending the characters '1' and '0'
# So whats ACTUALLY happening is, it's printing out the ASCII code 49 for character '1' then
#   ASCII code 489 for character '0'
