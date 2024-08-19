import numpy as np

theta_1 = 90 # angle in degrees
theta_2 = 0 # angle in degrees
theta_3 = 0 # angle in degrees
theta_4 = 0 # angle in degrees
theta_5 = 0 # angle in degrees
theta_6 = 0 # angle in degrees

theta_1 = (theta_1 / 180.0) * np.pi # converting theta 1 to radians
theta_2 = (theta_2 / 180.0) * np.pi
theta_3 = (theta_3 / 180.0) * np.pi
theta_4 = (theta_4 / 180.0) * np.pi
theta_5 = (theta_5 / 180.0) * np.pi
theta_6 = (theta_6 / 180.0) * np.pi

# Setting rotation matrices
R0_1 = [ [np.cos(theta_1), 0, np.sin(theta_1)],
         [np.sin(theta_1), 0, -np.cos(theta_1)],
         [0, 1, 0] ]

R1_2 = [ [-np.sin(theta_2), 0, np.cos(theta_2)],
         [np.cos(theta_2), 0, np.sin(theta_2)],
         [0, 1, 0] ]

R2_3 = [ [1, 0, 0],
         [0, 1, 0],
         [0, 0, 1]]

R3_4 = [ [np.cos(theta_4), 0, -np.sin(theta_4)],
         [np.sin(theta_4), 0, np.cos(theta_4)],
         [0, -1, 0] ]

R4_5 = [ [np.cos(theta_5), 0, np.sin(theta_5)],
         [np.sin(theta_5), 0, -np.cos(theta_5)],
         [0, 1, 0] ]

R5_6 = [ [np.cos(theta_6), -np.sin(theta_6), 0],
         [np.sin(theta_6), np.cos(theta_6), 0],
         [0, 0, 1] ]

# Dot product of both matrices
R0_2 = np.dot(R0_1, R1_2)
R2_4 = np.dot(R2_3, R3_4)
R4_6 = np.dot(R4_5, R5_6)

R0_4 = np.dot(R0_2, R2_4)
R0_6 = np.dot(R0_4, R4_6)

# This shows us the projection of X2, Y2, Z2 (columns) ON X0, Y0, Z0 (rows)
print('\nR0_1 = ')
print (np.matrix(R0_1))

print('\nR1_2 = ')
print(np.matrix(R1_2))

print('\nR2_3 = ')
print(np.matrix(R2_3))

print('\nR3_4 = ')
print(np.matrix(R3_4))

print('\nR4_5 = ')
print(np.matrix(R4_5))

print('\nR5_6 = ')
print(np.matrix(R5_6))

print('\n\nR0_6 = ')
print(np.matrix(R0_6))

