# Important: Download openCV from https://sourceforge.net/projects/opencvlibrary/files
# Find openCVwin folder
# Download 3.2.0 library version
# Run the executable and extract it
# Wait until the extraction is finished and then find the 'opencv' folder
# Go to build > python > 2.7 > choose x64 version > copy cv2.pyd
# Go to Python27 folder > lib > site-packages > paste cv2.pyd into this directory

import numpy as np
import cv2

cap = cv2.VideoCapture(0)   # our camera variable and each camera connected to our PC has a number starting from 0

while(1):
    # read() reads the next frame coming from the video camera
    # frame is the variable thats going to hold the frame captured from the camera
    #   the _, is for a boolean variable that will say whether a frame capture was successful or not but
    #   in this case, we aren't using this variable so we use _, instead
    _,frame = cap.read()

    # add np.matrix() so we can do matrix operations on these frames
    red = np.matrix(frame[:, :, 2])    # the ':' means to copy all the rows and columns, 2 means copy third layer which is Red
    green = np.matrix(frame[:, :, 1])  # in openCV the layer ordering goes blue 1st, green 2nd, red 3rd
    blue = np.matrix(frame[:, :, 0])   # we are getting the individual color matrices by splitting one matrix into several ones

    # we have to use int16 because remember, each pixel is represented by a value between 0:255.
    # if the green matrix value is bigger, this would result in a negative number, but our 8 bit numbers
    #   can't handle negative numbers in that range so we would get undefined behavior.
    # int16 means we give room to handle positive AND negative numbers because it's 16 bit SIGNED integers
    red_only = np.int16(red) - np.int16(green) - np.int16(blue)

    # these two lines say, for every number that is negative, and every number that is greater than 255
    #   in this matrix, should be assigned to their respective numbers. This is because for an image matrix
    #   to be valid, we cannot have numbers that are outside of the valid range of 0:255
    red_only[red_only < 0] = 0
    red_only[red_only > 255] = 255

    # Algorithm to find the center of a bright object on a dark background in an image
    column_sums = np.matrix(np.sum(red_only, 0))    # the 0 parameter is for cols, 1 is for rows, 2 is for colors
    column_numbers = np.matrix(np.arange(640))  # vector that holds the number of each column of the entire matrix
    column_mult = np.multiply(column_sums, column_numbers)  # does ELEMENT WISE multiplication with vectors/matrices
    total = np.sum(column_mult) # column mult is a vector, only one axis so no need for second parameter
    matrix_sum = np.sum(np.sum(red_only))   # sum of all the pixels in red only matrix
    column_location = total / matrix_sum    # column center of the bright object in the image

    print(column_location)  # value changes as the bright object moves left and right in the image frame
    
    red_only = np.uint8(red_only)
    
    # image show function, 'figure 1' is the name of the image, frame is what will be shown
    cv2.imshow('rgb', frame)   
    cv2.imshow('red', red)
    cv2.imshow('green', green)
    cv2.imshow('blue', blue)
    cv2.imshow('red_only', red_only)

    k = cv2.waitKey(5)  # wait for 5 milliseconds everytime we go through the loop and save the key press
    if k == 27: # if the key press is the ESC key (code 27), then we break out of the loop
        break

cv2.destroyAllWindows()

print(frame)
