#!/home/na/.pyenv/shims/python

import os
import sys
import numpy as np
import pandas as pd

data = pd.read_csv(sys.stdin, sep=';')

arr = np.matrix(data.values)

print(arr.sum())
print(arr.max())
print(arr.min())
