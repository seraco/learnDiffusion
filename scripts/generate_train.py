#!/usr/bin/env python

import os
from solve_diffusion import solve

number = 5

dir_path = '../train'

for i in range(number):
    tra_case_path = dir_path + '/tra' + str(i)
    if not os.path.exists(tra_case_path):
        os.makedirs(tra_case_path)

# path = os.path.abspath(os.path.join(os.path.dirname( __file__ ), os.pardir, 'train'))
path = os.path.join(os.path.dirname( __file__ ), os.pardir, 'train')
os.chdir(path)
# os.system('ls')

for i in range(number):
    os.chdir(path + '/tra' + str(i))
    solve()
    os.chdir(os.pardir)
