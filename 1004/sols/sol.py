#!/usr/bin/env python

import numpy as np

n = int(input())

arr = np.array(input().split(), float)

p = np.poly(arr)


k = int(input())
points = np.array(input().split(), float)

ans = []

#for i in range(k):
#  ans.append(np.polyval(p, points[0]))

d = np.polyder(p)

ans1 = list(np.polyval(p, x) for x in points)
ans2 = list(np.polyval(d, x) for x in points)

formatted_str = ' '.join(['{:0.5f}'.format(x) for x in p])
print(formatted_str)

formatted_str = ' '.join(['{:0.5f}'.format(x) for x in ans1])
print(formatted_str)

formatted_str = ' '.join(['{:0.5f}'.format(x) for x in ans2])
print(formatted_str)

