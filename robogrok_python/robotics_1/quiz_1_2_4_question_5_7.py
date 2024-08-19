import numpy as np

matrix = [ [25, 97, 42, 21],
           [14, 245, 167, 63],
           [32, 255, 115, 14],
           [15, 0, 21, 51] ]

column_total = np.matrix(np.sum(matrix, 0))
column_numbers = [ [1, 2, 3, 4] ]
column_mult = np.multiply(column_total, column_numbers)
column_total = np.sum(column_mult)
matrix_sum = np.sum(np.sum(matrix))
column_location = float(column_total) / matrix_sum

print("column location:")
print(column_location)


row_total = np.matrix(np.sum(matrix, 1))    # gives a horizontal vector for some reason, even though its rows
row_numbers = [ [1, 2, 3, 4] ]  
row_mult = np.multiply(row_total, row_numbers)
row_total = np.sum(row_mult)
row_location = float(row_total) / matrix_sum

print("\nrow location:")
print(row_location)
