# Important: Download openCV from https://sourceforge.net/projects/opencvlibrary/files
# Find openCVwin folder
# Download 3.2.0 library version
# Run the executable and extract it
# Wait until the extraction is finished and then find the 'opencv' folder
# Go to build > python > 2.7 > choose x64 version > copy cv2.pyd
# Go to Python27 folder > lib > site-packages > paste cv2.pyd into this directory

import numpy as np
import cv2

capture = cv2.VideoCapture(0)   # 0 is for the camera number connected to our PC

# first capture the background without the target object inside of the picture
# convert it to grayscale
# convert it to black and white using the threshold algorithm
# use the 'center of mass' approach to find the location of the object in units of pixels, for both row and cols
# use pixel to centimeter to convert the location of the object in units of cm
# use a homogenous transformation matrix to convert the position from the camera coordinate system to the base frame

while(1):
    _,frame = capture.read()    # capture a continuous feed of the camera
    gray_image_1 = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)  # turn the frame into a grayscale
    cv2.imshow('background', gray_image_1)  # show this capture on the desktop

    escape_key = cv2.waitKey(5) # allow user to stop the feed by pressing the 'ESC' key
    if(escape_key == 27):
        break

cv2.destroyAllWindows()
