#!/usr/bin/env python
# -*- coding: utf-8 -*-


import numpy as np
import matplotlib.pyplot as plt
from math import log


fid_nor_anal = open('../sol/time_9.9e-3/nor_1e-8_9.9e-3.vtk')

anal_nor = np.array([])

for line in fid_nor_anal:
    anal_nor = np.append(anal_nor, float(line[:-1]))

# print anal_nor


fid_nor_1 = open('../sol/time_9.9e-3/nor_1e-4_9.9e-3.vtk')

sol_nor_1 = np.array([])

for line in fid_nor_1:
    sol_nor_1 = np.append(sol_nor_1, float(line[:-1]))

# print sol_nor_1


fid_nor_2 = open('../sol/time_9.9e-3/nor_1e-5_9.91e-3.vtk')

sol_nor_2 = np.array([])

for line in fid_nor_2:
    sol_nor_2 = np.append(sol_nor_2, float(line[:-1]))

# print sol_nor_2


fid_nor_3 = open('../sol/time_9.9e-3/nor_1e-6_9.901e-3.vtk')

sol_nor_3 = np.array([])

for line in fid_nor_3:
    sol_nor_3 = np.append(sol_nor_3, float(line[:-1]))

# print sol_nor_3


fid_nor_4 = open('../sol/time_9.9e-3/nor_1e-7_9.9001e-3.vtk')

sol_nor_4 = np.array([])

for line in fid_nor_4:
    sol_nor_4 = np.append(sol_nor_4, float(line[:-1]))

# print sol_nor_4


avg_nor_1 = 0
i = 0
for el in anal_nor:
    avg_nor_1 += abs(el - sol_nor_1[i])
    i += 1
avg_nor_1 /= i

print avg_nor_1


avg_nor_2 = 0
i = 0
for el in anal_nor:
    avg_nor_2 += abs(el - sol_nor_2[i])
    i += 1
avg_nor_2 /= i

print avg_nor_2


avg_nor_3 = 0
i = 0
for el in anal_nor:
    avg_nor_3 += abs(el - sol_nor_3[i])
    i += 1
avg_nor_3 /= i

print avg_nor_3


avg_nor_4 = 0
i = 0
for el in anal_nor:
    avg_nor_4 += abs(el - sol_nor_4[i])
    i += 1
avg_nor_4 /= i

print avg_nor_4


fid_hop_anal = open('../sol/time_9.9e-3/hop_1e-8_9.9e-3.vtk')

anal_hop = np.array([])

for line in fid_hop_anal:
    anal_hop = np.append(anal_hop, float(line[:-1]))

# print anal_hop


fid_hop_1 = open('../sol/time_9.9e-3/hop_1e-4_9.9e-3.vtk')

sol_hop_1 = np.array([])

for line in fid_hop_1:
    sol_hop_1 = np.append(sol_hop_1, float(line[:-1]))

# print sol_hop_1


fid_hop_2 = open('../sol/time_9.9e-3/hop_1e-5_9.91e-3.vtk')

sol_hop_2 = np.array([])

for line in fid_hop_2:
    sol_hop_2 = np.append(sol_hop_2, float(line[:-1]))

# print sol_hop_2


fid_hop_3 = open('../sol/time_9.9e-3/hop_1e-6_9.901e-3.vtk')

sol_hop_3 = np.array([])

for line in fid_hop_3:
    sol_hop_3 = np.append(sol_hop_3, float(line[:-1]))

# print sol_hop_3


fid_hop_4 = open('../sol/time_9.9e-3/hop_1e-7_9.9001e-3.vtk')

sol_hop_4 = np.array([])

for line in fid_hop_4:
    sol_hop_4 = np.append(sol_hop_4, float(line[:-1]))

# print sol_hop_4


avg_hop_1 = 0
i = 0
for el in anal_hop:
    avg_hop_1 += abs(el - sol_hop_1[i])
    i += 1
avg_hop_1 /= i

print avg_hop_1


avg_hop_2 = 0
i = 0
for el in anal_hop:
    avg_hop_2 += abs(el - sol_hop_2[i])
    i += 1
avg_hop_2 /= i

print avg_hop_2


avg_hop_3 = 0
i = 0
for el in anal_hop:
    avg_hop_3 += abs(el - sol_hop_3[i])
    i += 1
avg_hop_3 /= i

print avg_hop_3


avg_hop_4 = 0
i = 0
for el in anal_hop:
    avg_hop_4 += abs(el - sol_hop_4[i])
    i += 1
avg_hop_4 /= i

print avg_hop_4

print (log(avg_hop_4) - log(avg_hop_3)) / (log(1e-07) - log(1e-06))

x = [1e-04, 1e-05, 1e-06, 1e-07]

plt.loglog(x, [avg_nor_1, avg_nor_2, avg_nor_3, avg_nor_4], label="Normal")
plt.loglog(x, [avg_hop_1, avg_hop_2, avg_hop_3, avg_hop_4], label="Hopscotch")
plt.legend()
plt.xlabel("Delta time [sec]")
plt.ylabel("Average error")
plt.show()
