#!/home/na/.pyenv/shims/python

import os
import sys
import numpy as np

data = np.load("input.npz")

L = data.files

for i in L:
  s = data[i].sum()
  mx = data[i].max()
  max_index = np.isin(data[i], mx).nonzero()[0]
  mn = data[i].min()
  min_index = np.isin(data[i], mn).nonzero()[0]
  print(s, mn, mx)
  print(*min_index)
  print(*max_index)
