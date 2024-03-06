#!/home/na/.pyenv/shims/python

import os
import sys
import numpy as np

data = np.load("input.npz")

for test in data:
  s = data[test].sum()
  mx = data[test].max()
  max_index = np.isin(data[test], mx).nonzero()[0]
  mn = data[test].min()
  min_index = np.isin(data[test], mn).nonzero()[0]
  print(s, mn, mx)
  print(*min_index)
  print(*max_index)
