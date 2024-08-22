# Important: Download openCV from https://sourceforge.net/projects/opencvlibrary/files
# Find openCVwin folder
# Download 3.2.0 library version
# Run the executable and extract it
# Wait until the extraction is finished and then find the 'opencv' folder
# Go to build > python > 2.7 > choose x64 version > copy cv2.pyd
# Go to Python27 folder > lib > site-packages > paste cv2.pyd into this directory

import numpy as np
import cv2
import serial
np.seterr(divide='ignore', invalid='ignore')

capture = cv2.VideoCapture(0)   # 0 is for the camera number connected to our PC

centimeters_to_pixels_horizontal = 11.8 / 640.0    # 11.8cm width for camera FOV and 640 pixels horizontally
centimeters_to_pixels_vertical = 8.3 / 480.0    # 8.3cm height for camera FOV and 480 pixels horizontally
x0_coordinate = 0
y0_coordinate = 0


# Calculating coordinate transformation from camera coordinate system to the base frame manipulator coordinate system
# The equation is the following:
#
# [ [x0]             [ [xc]
#   [y0]   =  H0_C *   [yc]
#   [z0]               [zc]
#   [ 1] ]             [ 1] ] 
#
# Where X0, Y0, Z0 represents the manipulator base frame, and Xc, Yc, Zc represents the camera coordinate system.
# Once we have the homogeneous matrix H0_C and take the dot product of the camera coordinates, we will get the transformed coordinates
#    for our base frame.
#
# First we do calculations to find our rotation matrix R0_C
rotation_180_x = [ [1, 0, 0],
                   [0, np.cos(np.pi), -np.sin(np.pi)],
                   [0, np.sin(np.pi), np.cos(np.pi)] ]  # needs to be np.pi because we are using radians

converted_radians = (90.0 / 180.0) * np.pi  # converting from 90 degrees to radians
rotation_90_z = [ [np.cos(converted_radians), -np.sin(converted_radians), 0],
                       [np.sin(converted_radians), np.cos(converted_radians), 0],
                       [0, 0, 1] ]

R0_C = np.dot(rotation_180_x, rotation_90_z)

# Displacement vector calculated by hand using a ruler from the base frame to camera frame. Tuned by trial and error.
# In units of centimeters. Original measurements by hand were 8.5 for x and 13.3 for y.
d0_C = [ [8.15],
         [13.65],
         [0] ]
H0_C = np.concatenate((R0_C, d0_C), 1)  # 1 parameter means left to right concatenate
H0_C = np.concatenate((H0_C, [ [0, 0, 0, 1] ]), 0)  # 0 means top down concatenate. We need the [0, 0, 0, 1] vector to complete the HTM


# First capture the background without the target object inside of the picture.
# Convert it to grayscale.
# Convert it to black and white using the threshold method.
# Use the 'center of mass' approach to find the location of the object in units of pixels, for both rows and columns
# Use pixel to centimeter to convert the location of the object in units of cm
# Use a homogenous transformation matrix to convert the position from the camera coordinate system to the base frame

# while loop to capture the first background frame
while(1):
    _,frame = capture.read()    # capture a continuous feed of the camera
    image_gray_1 = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)  # turn the frame into a grayscale
    cv2.imshow('background', image_gray_1)  # show this capture on the desktop

    escape_key = cv2.waitKey(5) # allow user to stop the feed by pressing the 'ESC' key
    if(escape_key == 27):
        break

# while loop to capture the second foreground frame to compare to the background
while(1):
    _,frame = capture.read()
    image_gray_2 = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    cv2.imshow('foreground', image_gray_2)

    # image subtraction technique being used to make the targeted object the brightest compared to a dark background
    # Note: np.int16 is used to convert to unsigned integers to handle possible negative integers when subtracting the matrices.
    #       The values for each pixel of the matrix is from 0 - 255 so it can only handle positive integers.
    #       np.matrix is used to allow mathematical operations on the grayscale frames.
    #       Absolute value is used so no invalid negative numbers remain after the pixel differences are taken.
    #       We error check for pixel values > 255 to keep it within the valid 0-255 range
    image_difference = np.absolute(np.matrix(np.int16(image_gray_2)) - np.matrix(np.int16(image_gray_1)))
    image_difference[image_difference > 255] = 255
    image_difference = np.uint8(image_difference)
    cv2.imshow('difference', image_difference)

    # threshold method to convert from grayscale to true black and white image in terms of machine vision standards
    image_black_white = image_difference
    image_black_white[image_black_white <= 100] = 0
    image_black_white[image_black_white > 100] = 1

    # Algorithm to find the center of a bright object on a dark background of an image
    column_sums = np.matrix(np.sum(image_black_white, 0))    # 0 parameter is for summing columns, 1 is for rows, 2 is for colors
    column_numbers = np.matrix(np.arange(640))  # vector that holds the column numbers
    column_multiply = np.multiply(column_sums, column_numbers) # ELEMENT wise multiplication with vectors/matrices
    column_total = np.sum(column_multiply)  # get the total sum of the column values
    matrix_total = np.sum(np.sum(image_black_white)) # total sum of the difference matrix, we have to np.sum() twice to achieve this
    column_location = column_total / matrix_total   # calculated column center of the bright object in the difference image]

    row_sums = np.matrix(np.sum(image_black_white, 1))  # sum along the rows axis, currently it has 480 rows and 1 column
    row_sums = row_sums.transpose() # transpose the matrix so we have 1 row and 480 columns
    row_numbers = np.matrix(np.arange(480))
    row_multiply = np.multiply(row_sums, row_numbers)
    row_total = np.sum(row_multiply)
    matrix_total = np.sum(np.sum(image_black_white))
    row_location = row_total / matrix_total

    # Convert from unit of pixels to centimeters 
    x_location = column_location * centimeters_to_pixels_horizontal 
    y_location = row_location * centimeters_to_pixels_vertical

    # Vector for the x, y, z locations in the camera frame using the converted x and y locations in centimeters
    point_camera = [ [x_location],
                     [y_location],
                     [0],
                     [1] ]

    # Final operation using our equation for our equation defined at the top
    point_base_frame = np.dot(H0_C, point_camera)

    x0_coordinate = point_base_frame[0]
    y0_coordinate = point_base_frame[1]

    print(x0_coordinate, y0_coordinate)
    
    escape_key = cv2.waitKey(5)
    if(escape_key == 27):
        break

cv2.destroyAllWindows() # close all camera frames

serial = serial.Serial()    # initialize the serial port
serial.baudrate = 9600  # set the baud rate to match our UART top-design block in PSoC Creator
serial.port = 'COM10' # found in windows device manager > ports > KitProg USB-UART
serial.open()   # open the port

x0_coordinate = int(np.uint8(x0_coordinate * 10))   # Multiplying by 10 to get 1 floating point precision.
y0_coordinate = int(np.uint8(y0_coordinate * 10))   # Convert to uint8 so its the appropriate byte length for UART transmission

transmit_x0 = bytearray([x0_coordinate])    # Use python bytearray() function to convert the integers to their byte representation
transmit_y0 = bytearray([y0_coordinate])
serial.write(transmit_x0)   # Finally transmit the integers in their byte converted form
serial.write(transmit_y0)

serial.close()  # Close the port

##### Project Notes #####
#########################
#
# Problem: Weird values when trying to find the image_difference matrix
# Solution: Realized I had to first convert the values to signed 16 bit integers so the calculations could handle potential negative
#           pixel values. This is obviously invalid in an image matrix so then I had to use absolute value to rectify this problem.
#           Afterwards, it was necessary to convert it back to unsigned 8 bit integers to keep the integrity of color matrix.
# 
# Problem: The image_black_white matrix was showing all 0's instead of 1's and 0's.
# Solution: Small error but a critical one. The line [image_black_white <= 100] = 0 HAS to come first, otherwise it'll set all the
#           pixels that got set to 1 immediately to 0 as well which is what we do not want.
#
