# python code for Quiz 1-1-5, Question 7-10:
# working out the problem by hand then transcribing the work into python

import numpy as np

# setting values for links
a1 = 1  # in cm
a2 = 2
a3 = 3
d2 = 1

theta_1 = 15    # in degrees
theta_1 = (theta_1 / 180.0) * np.pi   # converting to radians

# setting rotation matrices
R0_1_Z_Rotation = [ [np.cos(theta_1), -np.sin(theta_1), 0],
                    [np.sin(theta_1), np.cos(theta_1), 0],
                    [0, 0, 1] ]

R0_1_Base = [ [-1, 0, 0],
              [0, 0, 1],
              [0, 1, 0] ]

R0_1 = np.dot(R0_1_Z_Rotation, R0_1_Base)   # Order is important, Z Rotation comes before the Base matrix.
                                                # This is because we're rotating on Z0, instead of Y1

R1_2 = [ [1, 0, 0],
         [0, 1, 0],
         [0, 0, 1] ]

# setting displacement vectors
d0_1 = [ [0],
         [0],
         [a1] ]

d1_2 = [ [0],
         [0],
         [a2 + a3 + d2] ]

# setting row 4 matrix to create the homogenous transformation matrices
h_row_4 = [ [0, 0, 0, 1] ]


H0_1 = np.concatenate((R0_1, d0_1), 1)      # setting the second flag to 1 to indicate this is left to right concatenation
H0_1 = np.concatenate((H0_1, h_row_4), 0)   # second flag to 0 to indicate top down concatenation

print("\n R0_1 Version 1:")
print(np.matrix(R0_1))

print("\n R0_1 Version 2:")
print(np.matrix(R0_1))

print("\n")
print(np.matrix(d0_1))

print("\n")
print(np.matrix(H0_1))


H1_2 = np.concatenate((R1_2, d1_2), 1)
H1_2 = np.concatenate((H1_2, h_row_4), 0)


print("\n\n")
print(np.matrix(R1_2))

print("\n")
print(np.matrix(d1_2))

print("\n")
print(np.matrix(H1_2))


# Creating the final homogenous transformation matrix and printing it out
H0_2 = np.dot(H0_1, H1_2)
print("\n\n\n")
print(np.matrix(H0_2))
