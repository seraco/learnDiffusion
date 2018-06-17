#!/usr/bin/env python

import os
from stat import S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IROTH

# path = os.path.abspath(os.path.join(os.path.dirname( __file__ ), os.pardir, 'train'))
path = os.path.join(os.path.dirname( __file__ ), os.pardir, 'train')
os.chdir(path)
# os.system('ls')

for i in range(1):
    os.chdir(path + '/tra' + str(i))
    # os.system('ls')
    # os.chmod('Allmesh', S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IROTH)
    # os.chmod('Allrun', S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IROTH)
    os.chmod('Allclean', S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IROTH)
    # os.system('ls -lah Allmesh')
    # os.system('ls -lah Allrun')
    # os.system('ls -lah Allclean')
    os.system('./Allclean')
    os.chdir(os.pardir)
