import numpy as np

def one(arr):
  n = arr.shape[0]
  mi = arr.min()
  ma = arr.max()
  print(arr.sum(), mi, ma)
  ind = np.array(list(range(n)))
  print(*ind[np.where(arr[ind] == mi)])
  print(*ind[np.where(arr[ind] == ma)])

data = np.load("input.npz")
for test in data:
  one(data[test])
data.close()
