#!/usr/bin/env python

import sys
import numpy as np

A = np.loadtxt(sys.stdin, int)

s = A.shape
n, m = s[0], s[1]
flag = False
if n < m:
  n, m = m, n         # Будемо видаляти рядки
  A = np.transpose(A) # Детермінант матриці дорівнює детермінанту транспонованої матриці
  flag = True


rows_to_delete = [0, 1]
B_max = np.delete(A, rows_to_delete, axis=0)
max_det = np.linalg.det(B_max)

for i in range(n-1):
  for j in range(i + 1, n):
    rows_to_delete = [i, j]
    B = np.delete(A, rows_to_delete, axis=0)
    det = np.linalg.det(B)
    if det > max_det:
      max_det = det
      B_max = B

if flag:
  B_max = np.transpose(B_max)

s = B_max.shape
print(s[0])
for l in B_max:
  print(*l)
print(round(max_det))


'''
mean_values = np.mean(matrix, axis=0)

print("Середні значення по стовпцях:")
print(*mean_values)
mean_values = np.mean(matrix, axis=1)
print(*mean_values)
'''
