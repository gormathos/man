#!/home/na/.pyenv/shims/python

#import os
import sys
import pandas as pd

#import numpy as np
#import cv2
#import matplotlib.pyplot as plt

data = pd.read_csv(sys.stdin, sep=';')

s = 0
maxi=0
mini=1000000000
for i in data.head():
  s += data[i].sum()
  mx = max(data[i])
  mn = data[i].min()
  maxi = max(maxi, mx)
  mini = min(mini, mn)
print(int(s))
print(int(maxi))
print(int(mini))
