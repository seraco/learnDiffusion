#!/usr/bin/env python

import os
# from distutils.dir_util import copy_tree

from genSys import generateBlockMeshDict
from genSys import generateControlDict
from genSys import generateFvSchemes
from genSys import generateFvSolution
from genSys import generateHeaterChangeDict
from genSys import generateHeaterFvSchemes
from genSys import generateHeaterFvSolution
from genSys import generateMainSolidChangeDict
from genSys import generateMainSolidFvSchemes
from genSys import generateMainSolidFvSolution
from genSys import generateTopoSetDict
from genSys import generateResiduals
from genCons import generateRegionProperties
from genCons import generateRadiationProperties
from genCons import generateHeaterThermoProperties
from genCons import generateMainSolidThermoProperties
from genBnd import generatePressure
from genBnd import generateTemperature
from genExec import generateAllmesh
from genExec import generateAllrun
from genExec import generateAllclean


def setTP(number):
    dir_path = '../train'
    cons_path = 'constant'
    sys_path = 'system'
    bnd_path = '0.orig'

    for i in range(number):

        tra_case_path = dir_path + '/tra' + str(i)
        system_path = tra_case_path + '/' + sys_path
        properties_path = tra_case_path + '/' + cons_path
        boundary_path = tra_case_path + '/' + bnd_path

        # copy_tree(cons_path, tra_case_path + '/' + cons_path)
        # copy_tree(sys_path, system_path)
        # copy_tree(bnd_path, tra_case_path + '/' + bnd_path)

        if not os.path.exists(system_path):
            os.makedirs(system_path + '/heater')
            os.makedirs(system_path + '/mainSolid')
            generateBlockMeshDict(system_path + '/blockMeshDict')
            generateControlDict(system_path + '/controlDict')
            generateFvSchemes(system_path + '/fvSchemes')
            generateFvSolution(system_path + '/fvSolution')
            generateHeaterChangeDict(system_path + '/heater/changeDictionaryDict')
            generateHeaterFvSchemes(system_path + '/heater/fvSchemes')
            generateHeaterFvSolution(system_path + '/heater/fvSolution')
            generateMainSolidChangeDict(system_path + '/mainSolid/changeDictionaryDict')
            generateMainSolidFvSchemes(system_path + '/mainSolid/fvSchemes')
            generateMainSolidFvSolution(system_path + '/mainSolid/fvSolution')
            generateTopoSetDict(system_path + '/topoSetDict')
            generateResiduals(system_path + '/residuals')

        if not os.path.exists(properties_path):
            os.makedirs(properties_path + '/heater')
            os.makedirs(properties_path + '/mainSolid')
            generateRegionProperties(properties_path + '/regionProperties')
            generateRadiationProperties(properties_path + '/heater/radiationProperties')
            generateRadiationProperties(properties_path + '/mainSolid/radiationProperties')
            generateHeaterThermoProperties(properties_path + '/heater/thermophysicalProperties')
            generateMainSolidThermoProperties(properties_path + '/mainSolid/thermophysicalProperties')

        if not os.path.exists(boundary_path):
            os.makedirs(boundary_path)
            generatePressure(boundary_path + '/p')
            generateTemperature(boundary_path + '/T')

        generateAllmesh(tra_case_path + '/Allmesh')
        generateAllrun(tra_case_path + '/Allrun')
        generateAllclean(tra_case_path + '/Allclean')

if __name__ == "__main__":
    setTP(1)
