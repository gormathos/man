#!/home/na/.pyenv/shims/python

import os
import sys
import numpy as np

data = np.load("input.npz")

L = data.files

for i in L:
  #print(data[i])
  a = data[i][np.where((data[i] > 0) & (data[i] < 10))]
  print(np.size(a))
  print(*a)
  print('sum =', np.sum(a))
