#!/usr/bin/env python

import sys
import os
import random

sys.path.append(os.path.join(os.path.dirname( __file__ ), os.pardir, 'solver'))
import diffusion

def solve():
    # shape = 'cyl' # 'box'/'cyl'

    init_temp = 273.0
    temp_bc = 500.0

    n_x = 256
    n_y = 256

    min_x = 0.0
    max_x = 1.0
    min_y = 0.0
    max_y = 1.0

    deltaX = (max_x - min_x) / n_x
    deltaY = (max_y - min_y) / n_y

    a_ran_x = random.uniform(min_x, max_x)
    b_ran_x = random.uniform(min_x, max_x)
    a_ran_y = random.uniform(min_y, max_y)
    b_ran_y = random.uniform(min_y, max_y)

    while abs(a_ran_x - b_ran_x) < 1.1*deltaX:
        b_ran_x += random.uniform(min_x, max_x)
    while abs(a_ran_y - b_ran_y) < 1.1*deltaY:
        b_ran_y += random.uniform(min_y, max_y)

    if a_ran_x < b_ran_x:
        x_1 = a_ran_x
        x_2 = b_ran_x
    else:
        x_1 = b_ran_x
        x_2 = a_ran_x
    if a_ran_y < b_ran_y:
        y_1 = a_ran_y
        y_2 = b_ran_y
    else:
        y_1 = b_ran_y
        y_2 = a_ran_y

    x_m = (x_1 + x_2) / 2.0
    y_m = (y_1 + y_2) / 2.0

    # print "X1", x_1
    # print "XM", x_m
    # print "X2", x_2
    # print "Y1", y_1
    # print "YM", y_m
    # print "Y2", y_2

    diffusion.solve(init_temp, x_m, y_m, temp_bc, x_1, x_2, y_1, y_2)
