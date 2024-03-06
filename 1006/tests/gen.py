#!/home/na/.pyenv/shims/python

import os
import sys
import numpy as np
import pandas as pd

fname, n, m, mn, mx = map(str, input().split())
n = int(n)
m = int(m)
mn = int(mn)
mx = int(mx)

arr = np.random.randint(mn, mx, (n, m))
df = pd.DataFrame(arr)
df.columns = ['C' + str(i+1) for i in range(m)]

pd.DataFrame(df).to_csv(fname, sep=";", index=None)

