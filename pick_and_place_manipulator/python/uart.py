import serial

serial = serial.Serial()
serial.baudrate = 9600
serial.port = 'COM10'   # found in Ports section of device manager, KitProg USB-UART
serial.open()

serial.write(b'10')

i = bytearray([50])
serial.write(i)


serial.close()
