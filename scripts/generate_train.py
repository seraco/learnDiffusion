#!/usr/bin/env python

import os
from solve_diffusion import solve

def gen_train(number):

    dir_path = '../train'

    tra_case_path = dir_path + '/tra' + str(number)
    if not os.path.exists(tra_case_path):
        os.makedirs(tra_case_path)

    # path = os.path.abspath(os.path.join(os.path.dirname( __file__ ), os.pardir, 'train'))
    path = os.path.join(os.path.dirname( __file__ ), os.pardir, 'train')

    os.chdir(path + '/tra' + str(number))
    solve()
    os.chdir(os.pardir)
