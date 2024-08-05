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
    
    red = frame[:, :, 2]    # the ':' means to copy all the rows and columns, 2 means copy third layer which is Red
    green = frame[:, :, 1]  # in openCV the layer ordering goes blue 1st, green 2nd, red 3rd
    blue = frame[:, :, 0]   # we are getting the individual color matrices by splitting one matrix into several ones

    # image show function, 'figure 1' is the name of the image, frame is what will be shown
    cv2.imshow('rgb', frame)   
    cv2.imshow('red', red)
    cv2.imshow('green', green)
    cv2.imshow('blue', blue)

    k = cv2.waitKey(5)  # wait for 5 milliseconds everytime we go through the loop and save the key press
    if k == 27: # if the key press is the ESC key (code 27), then we break out of the loop
        break

cv2.destroyAllWindows()

print(frame)
