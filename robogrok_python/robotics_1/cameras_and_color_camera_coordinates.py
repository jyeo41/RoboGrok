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

centimeters_to_pixels = 11.9 / 640.0    # 11.9cm width for camera FOV and 640 pixels horizontally

rotation_180_x = [ [1, 0, 0],
                   [0, np.cos(np.pi), -np.sin(np.pi)],
                   [0, np.sin(np.pi), np.cos(np.pi)] ]  # needs to be np.pi because we are using radians

negative_93_radians = (-93.0 / 180.0) * np.pi

rotation_neg_93_z = [ [np.cos(negative_93_radians), -np.sin(negative_93_radians), 0],
                       [np.sin(negative_93_radians), np.cos(negative_93_radians), 0],
                       [0, 0, 1] ]

R0_C = np.dot(rotation_180_x, rotation_neg_93_z)
d0_C = [ [-1.9],
         [-0.37],
         [0] ]

H0_C = np.concatenate((R0_C, d0_C), 1)
H0_C = np.concatenate((H0_C, [ [0, 0, 0, 1] ]), 0)

# print(np.matrix(H0_C))

while(1):
    # read() reads the next frame coming from the video camera
    # frame is the variable thats going to hold the frame captured from the camera
    #   the _, is for a boolean variable that will say whether a frame capture was successful or not but
    #   in this case, we aren't using this variable so we use _, instead
    _,frame = cap.read()

    # used to convert an image to grayscale imitating the way the human eye perceives color
    gray_image1 = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    cv2.imshow('background', gray_image1)

    k = cv2.waitKey(5)  # wait for 5 milliseconds everytime we go through the loop and save the key press
    if k == 27: # if the key press is the ESC key (code 27), then we break out of the loop
        break

while(1):
    _,frame = cap.read()

    gray_image2 = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    cv2.imshow('foreground', gray_image2)

    # taking the absolute value of the difference means we can account for both cases where the object
    #   is brighter or darker than the background
    difference = np.absolute(np.matrix(np.int16(gray_image1)) - np.matrix(np.int16(gray_image2)))
    difference[difference > 255] = 255

    difference = np.uint8(difference)
    cv2.imshow('difference', difference)

    # using thresholding to set the bounds for converting grayscale to black and white image.
    # order of operation is important, we need <= 100 first otherwise, if we have > 100 first and those set
    #   all those values to 1, then <= 100 would catch all those values that got changed to 1 and we don't want that
    black_white = difference
    black_white[black_white <= 100] = 0
    black_white[black_white > 100] = 1

    # Algorithm to find the center of a bright object on a dark background in an image
    column_sums = np.matrix(np.sum(black_white, 0))    # the 0 parameter is for cols, 1 is for rows, 2 is for colors
    column_numbers = np.matrix(np.arange(640))  # vector that holds the number of each column of the entire matrix
    column_mult = np.multiply(column_sums, column_numbers)  # does ELEMENT WISE multiplication with vectors/matrices
    total = np.sum(column_mult) # column mult is a vector, only one axis so no need for second parameter
    matrix_sum = np.sum(np.sum(black_white))   # sum of all the pixels in red only matrix

    # print("Matrix sum: ")
    # print(matrix_sum)
    column_location = total / matrix_sum    # column center of the bright object in the image

    # multiply by pixels to get units in centimeters.
    # remember, column_location is in unit pixels
    x_location = column_location * centimeters_to_pixels

    
    row_sums = np.matrix(np.sum(black_white, 1))    # the 0 parameter is for cols, 1 is for rows, 2 is for colors
    row_sums = row_sums.transpose() # converting from 480 rows and 1 column, to 1 row and 480 columns
    row_numbers = np.matrix(np.arange(480))  # vector that holds the row number of the entire matrix
    row_mult = np.multiply(row_sums, row_numbers)  # does ELEMENT WISE multiplication with vectors/matrices
    row_total = np.sum(row_mult) # column mult is a vector, only one axis so no need for second parameter
    matrix_sum = np.sum(np.sum(black_white))   # sum of all the pixels in red only matrix
    row_location = row_total / matrix_sum    # column center of the bright object in the image

    # multiply by pixels to get units in centimeters.
    # remember, column_location is in unit pixels.
    y_location = row_location * centimeters_to_pixels

    point_camera = [ [x_location],
                     [y_location],
                     [0],
                     [1] ]
    
    point_base_grid = np.dot(H0_C, point_camera)

    x0 = point_base_grid[0]
    y0 = point_base_grid[1]

    print(x0, y0)

    # Note: To find the Y position up and down, we have to do the same calculation for the rows as well.
    #   The value this print statement gives us is in PIXELS and only in the X position. The unit pixels is our
    #   cameras native unit. If we want this to be useful for our robot for picking up an object, it needs to be
    #   converted to centimeters. The position of the object is also relative to the camera's 0 position, which
    #   is the top left corner of the screen.
    #   If we want to find the location of an object that our robot can pick up, we're also going to need to
    #   convert the location of the object into the frame of our manipulator.
    # print(column_location)
    
    k=cv2.waitKey(5)
    if k == 27:
        break

cv2.destroyAllWindows()



# print(frame)
