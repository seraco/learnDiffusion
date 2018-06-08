#!/usr/bin/env python

import os
# from distutils.dir_util import copy_tree

from genSys import generateMeshDictFile
from genSys import generateControlDict
from genSys import generateDecomposeParDict
from genSys import generateFvSchemes
from genSys import generateFvSolution
from genCons import generateTransportProperties
from genBnd import generateBoundary


dir_path = 'train'
cons_path = 'constant'
sys_path = 'system'
bnd_path = '0'


for i in range(500):

    tra_case_path = dir_path + '/tra' + str(i)
    blockMeshDict_path = tra_case_path + '/' + sys_path
    properties_path = tra_case_path + '/' + cons_path
    boundary_path = tra_case_path + '/' + bnd_path

    # copy_tree(cons_path, tra_case_path + '/' + cons_path)
    # copy_tree(sys_path, blockMeshDict_path)
    # copy_tree(bnd_path, tra_case_path + '/' + bnd_path)

    if not os.path.exists(blockMeshDict_path):
        os.makedirs(blockMeshDict_path)
        generateMeshDictFile(blockMeshDict_path + '/blockMeshDict')
        generateControlDict(blockMeshDict_path + '/controlDict')
        generateDecomposeParDict(blockMeshDict_path + '/decomposeParDict')
        generateFvSchemes(blockMeshDict_path + '/fvSchemes')
        generateFvSolution(blockMeshDict_path + '/fvSolution')

    if not os.path.exists(properties_path):
        os.makedirs(properties_path)
        generateTransportProperties(properties_path + '/transportProperties')

    if not os.path.exists(boundary_path):
        os.makedirs(boundary_path)
        generateBoundary(boundary_path + '/T')
