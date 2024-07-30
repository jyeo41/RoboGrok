import numpy as np

a1 = 1 # length of link a1 in cm
a2 = 1 # length of link a2 in cm
a3 = 1
a4 = 1

theta_1 = 10 # angle in degrees
theta_2 = 70 # angle in degrees

theta_1 = (theta_1 / 180.0) * np.pi # converting theta 1 to radians
theta_2 = (theta_2 / 180.0) * np.pi

# Setting rotation matrices
R0_1 = [ [np.cos(theta_1), -np.sin(theta_1), 0],
         [np.sin(theta_1), np.cos(theta_1), 0],
         [0, 0, 1] ]
R1_2 = [ [np.cos(theta_2), -np.sin(theta_2), 0],
         [np.sin(theta_2), np.cos(theta_2), 0],
         [0, 0, 1] ]

# Dot product of both matrices
R0_2 = np.dot(R0_1, R1_2)

# This shows us the projection of X2, Y2, Z2 (columns) ON X0, Y0, Z0 (rows)
print("\nRotation Matrix R0_1:")
print(np.matrix(R0_1))


d0_1 = [ [a2 * np.cos(theta_1)],
         [a2 * np.sin(theta_1)],
         [a1] ]
print("\nDisplacement Vector d0_1:")
print(np.matrix(d0_1))

d1_2 = [ [a4 * np.cos(theta_2)],
         [a4 * np.sin(theta_2)],
         [a3] ]
# print('\nMatrix d1_2:')
# print(np.matrix(d1_2))

# Need to tell numpy the direction to concatenate the matrices
# 0 in the second parameter means R0_1 on top, d0_1 on bottom
# 1 in the second parameter means R0_1 on left, d0_1 on right
#   which is what we want for the homogeneous transformation matrix
H0_1 = np.concatenate((R0_1, d0_1), 1)
H0_1 = np.concatenate((H0_1, [ [0, 0, 0, 1] ]), 0)
# print("\nHomogeneous Matrix H0_1:")
# print(np.matrix(H0_1))


H1_2 = np.concatenate((R1_2, d1_2), 1)
H1_2 = np.concatenate((H1_2, [ [0, 0, 0, 1] ]), 0)
# print("\nHomogeneous Matrix H1_2:")
# print(np.matrix(H0_1))

H0_2 = np.dot(H0_1, H1_2)
print("\nHomogeneous Matrix H0_2")
print(np.matrix(H0_2))
