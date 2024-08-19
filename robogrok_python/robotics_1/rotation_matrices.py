import numpy as np

theta_1 = 30 # angle in degrees
theta_2 = 60 # angle in degrees

theta_1 = (theta_1 / 180.0) * np.pi # converting theta 1 to radians
theta_2 = (theta_2 / 180.0) * np.pi

# Setting rotation matrices
R0_1 = [ [1, 0, 0],
         [0, np.cos(theta_1), -np.sin(theta_1)],
         [0, np.sin(theta_1), np.cos(theta_1)] ]

R1_2 = [ [np.cos(theta_2), 0, np.sin(theta_2)],
         [0, 1, 0],
         [-np.sin(theta_2), 0, np.cos(theta_2)] ]

# Dot product of both matrices
R0_2 = np.dot(R0_1, R1_2)

# This shows us the projection of X2, Y2, Z2 (columns) ON X0, Y0, Z0 (rows)
print(np.matrix(R0_2))
