import numpy as np

# rotation matrix
R0_C = [ [1, 0, 0],
         [0, np.cos(np.pi), -np.sin(np.pi)],
         [0, np.sin(np.pi), np.cos(np.pi)] ]

# displacement vector
d0_C = [ [-8],
         [10],
         [0] ]

H0_C = np.concatenate((R0_C, d0_C), 1)  # concatenate left to right
H0_C = np.concatenate((H0_C, [ [0, 0, 0, 1] ]), 0)  # concatenate top down

print(np.matrix(H0_C))

# xc, yc, zc vector in unit of meters
camera_point = [ [1.563],
                 [4.688],
                 [0],
                 [1] ]

base_grid_point = np.dot(H0_C, camera_point)

print('\n')
print(base_grid_point)
