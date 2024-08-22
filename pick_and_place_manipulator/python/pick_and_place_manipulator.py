# Important: Download openCV from https://sourceforge.net/projects/opencvlibrary/files
# Find openCVwin folder
# Download 3.2.0 library version
# Run the executable and extract it
# Wait until the extraction is finished and then find the 'opencv' folder
# Go to build > python > 2.7 > choose x64 version > copy cv2.pyd
# Go to Python27 folder > lib > site-packages > paste cv2.pyd into this directory

import numpy as np
import cv2
np.seterr(divide='ignore', invalid='ignore')

capture = cv2.VideoCapture(0)   # 0 is for the camera number connected to our PC

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

##    print(column_location)

    row_sums = np.matrix(np.sum(image_black_white, 1))  # sum along the rows axis, currently it has 480 rows and 1 column
    row_sums = row_sums.transpose() # transpose the matrix so we have 1 row and 480 columns
    row_numbers = np.matrix(np.arange(480))
    row_multiply = np.multiply(row_sums, row_numbers)
    row_total = np.sum(row_multiply)
    matrix_total = np.sum(np.sum(image_black_white))
    row_location = row_total / matrix_total

##    print(row_location)

    print(column_location, row_location)
    
    escape_key = cv2.waitKey(5)
    if(escape_key == 27):
        break

cv2.destroyAllWindows()


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
#
#
#

