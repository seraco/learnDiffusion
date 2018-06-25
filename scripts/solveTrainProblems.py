#!/usr/bin/env python

import os
from stat import S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IROTH

def solveTP(number):
    # path = os.path.abspath(os.path.join(os.path.dirname( __file__ ), os.pardir, 'train'))
    path = os.path.join(os.path.dirname( __file__ ), os.pardir, 'train')
    os.chdir(path)
    # os.system('ls')

    for i in range(number):
        os.chdir(path + '/tra' + str(i))
        # os.system('ls')
        os.chmod('Allmesh', S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IROTH)
        os.chmod('Allrun', S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IROTH)
        # os.chmod('Allclean', S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IROTH)
        # os.system('ls -lah Allmesh')
        # os.system('ls -lah Allrun')
        # os.system('ls -lah Allclean')
        # os.system('./Allmesh')
        # os.system('chtMultiRegionFoam')
        os.system('./Allrun')
        os.system('touch foam.foam')
        os.chdir(os.pardir)

if __name__ == "__main__":
    solveTP(1)
