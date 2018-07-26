#!/usr/bin/env python
# -*- coding: utf-8 -*-


import numpy as np


fid_both = open('../data/solution_both.txt')

both = np.array([])

for line in fid_both:
    both = np.append(both, float(line[:-1]))

# print both


fid_left = open('../data/solution_left.txt')

left = np.array([])

for line in fid_left:
    left = np.append(left, float(line[:-1]))

# print left


fid_center = open('../data/solution_center.txt')

center = np.array([])

for line in fid_center:
    center = np.append(center, float(line[:-1]))

# print center


summation = left + center
error = abs(summation - both)

if not np.any(error > 1e-4):
    print "Superposition holds!😋"
else:
    print "Superpostion does not hold😞"
