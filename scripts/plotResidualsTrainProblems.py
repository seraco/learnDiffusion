#!/usr/bin/env python

import os
# from stat import S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IROTH

def plotResidualsTP(number):
    # path = os.path.abspath(os.path.join(os.path.dirname( __file__ ), os.pardir, 'train'))
    path = os.path.join(os.path.dirname( __file__ ), os.pardir, 'train')
    os.chdir(path)
    # os.system('ls')

    for i in range(number):
        os.chdir(path + '/tra' + str(i))
        # os.system('ls')
        # os.chmod('Allmesh', S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IROTH)
        # os.chmod('Allrun', S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IROTH)
        # os.chmod('Allclean', S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IROTH)
        # os.system('ls -lah Allmesh')
        # os.system('ls -lah Allrun')
        # os.system('ls -lah Allclean')
        # os.system('./Allclean')
        os.system('echo "set terminal png" >> residuals.gnuplot')
        os.system('echo "set title \\"Residuals\\"" >> residuals.gnuplot')
        os.system('echo "set ylabel \'Residual\'" >> residuals.gnuplot')
        os.system('echo "set xlabel \'Iteration\'" >> residuals.gnuplot')
        os.system('echo "set output \'residuals.png\'" >> residuals.gnuplot')
        os.system('echo "plot \\"< grep -A1 \'Solving for solid region mainSolid\' log.chtMultiRegionSimpleFoam|grep \'Solving for h\'|cut -d \',\' -f 3|cut -d \' \' -f 5\\" title \'Residual\'" >> residuals.gnuplot')
        os.system('gnuplot residuals.gnuplot')
        os.chdir(os.pardir)

if __name__ == "__main__":
    plotResidualsTP(1)
