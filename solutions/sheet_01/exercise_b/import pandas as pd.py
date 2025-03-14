import pandas as pd
import numpy as np
from io import StringIO

# Provided data as a string
data = """
0:00.64,0.62,0.00,1288
0:00.63,0.62,0.00,1472
0:00.63,0.62,0.00,1360
0:00.63,0.62,0.00,1476
0:00.63,0.63,0.00,1332
0:00.63,0.62,0.00,1360
0:00.63,0.62,0.00,1440
0:00.63,0.62,0.00,1440
0:00.63,0.62,0.00,1288
0:00.63,0.62,0.00,1440
0:00.63,0.63,0.00,1412
"""

# Read the data into a pandas DataFrame
df = pd.read_csv(StringIO(data), header=None, names=['T1', 'T2', 'T3', 'S'])

# Compute mean and variance for each column
mean_values = df.mean()
variance_values = df.var()

# Print the results
print("Mean values:")
print(mean_values)
print("\nVariance values:")
print(variance_values)