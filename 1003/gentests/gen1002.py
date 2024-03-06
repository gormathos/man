#!/usr/bin/env python

import os
import sys
import numpy as np
import pandas as pd
import random
from npy_append_array import NpyAppendArray

fname, k, n, mn, mx = map(str, input().split())
k = int(k) # k массивов
n = int(n) # максимальное количество элементов
mn = int(mn) # минимальное значение
mx = int(mx) # максимальное значение

ALL = []
names = []
for i in range(k):
  n1 = random.randint(n, n + n // 2)
  mn1 = random.randint(2 * mn, mn)
  mx1 = random.randint(mx, 2 * mx)
  print(n1, mn1, mx1)
  arr = np.random.randint(mn1, mx1, n1)
  ALL.append(arr)

#print(names)
print(ALL)
np.savez_compressed(fname, *[ALL[x] for x in range(len(ALL))])
