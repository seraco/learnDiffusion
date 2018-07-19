#!/usr/bin/env python

import sys
import os
import random

sys.path.append(os.path.join(os.path.dirname( __file__ ), os.pardir, 'solver'))
import diffusion

def solve():

    init_temp = 0.0
    source_val = 10000.0

    n_x = 256
    n_y = 256

    a_ran_x = random.randint(0, n_x - 1)
    b_ran_x = random.randint(0, n_x - 1)
    a_ran_y = random.randint(0, n_y - 1)
    b_ran_y = random.randint(0, n_y - 1)

    while a_ran_x == b_ran_x:
        b_ran_x = random.randint(0, n_x - 1)
    while a_ran_y == b_ran_y:
        b_ran_y = random.randint(0, n_y - 1)

    if a_ran_x < b_ran_x:
        i_1 = a_ran_x
        i_2 = b_ran_x
    else:
        i_1 = b_ran_x
        i_2 = a_ran_x
    if a_ran_y < b_ran_y:
        j_1 = a_ran_y
        j_2 = b_ran_y
    else:
        j_1 = b_ran_y
        j_2 = a_ran_y

    i_m = (i_1 + i_2) / 2
    j_m = (j_1 + j_2) / 2

    # print "I1", i_1
    # print "IM", i_m
    # print "I2", i_2
    # print "J1", j_1
    # print "JM", j_m
    # print "J2", j_2

    diffusion.solve(init_temp, i_m, j_m, source_val, i_1, i_2, j_1, j_2)
