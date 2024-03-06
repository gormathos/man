#!/usr/bin/env python

import numpy as np

n = int(input())

matrix = np.ones((n, n), int)
matrix[1:-1, 1:-1] = 0
np.fill_diagonal(matrix, 1)
np.fill_diagonal(np.fliplr(matrix), 1)

for l in matrix:
  print(*l)

