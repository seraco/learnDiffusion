#!/usr/bin/env python

def generateAllmesh(file_path):
    with open(file_path, 'w') as fd:
        fd.write(
            """
            #!/bin/sh
            cd ${0%/*} || exit 1                        # Run from this directory
            . $WM_PROJECT_DIR/bin/tools/RunFunctions    # Tutorial run functions

            echo $(foamListRegions)

            runApplication blockMesh
            runApplication topoSet

            # Restore initial fields
            restore0Dir

            runApplication splitMeshRegions -cellZones -overwrite

            # Remove fluid fields from solid regions (important for post-processing)
            for region in $(foamListRegions solid)
            do
                rm -f 0/$region/{nut,alphat,epsilon,k,U,p_rgh}
                rm -f processor*/0/$region/{nut,alphat,epsilon,k,U,p_rgh}
            done

            for region in $(foamListRegions)
            do
                runApplication -s $region changeDictionary -region $region
            done

            echo
            echo "Use paraFoam -touch-all to create files for paraview post-processing"
            echo
            echo "End"

            #------------------------------------------------------------------------------
            """
        )

def generateAllrun(file_path):
    with open(file_path, 'w') as fd:
        fd.write(
            """
            #!/bin/sh
            cd ${0%/*} || exit 1                        # Run from this directory
            . $WM_PROJECT_DIR/bin/tools/RunFunctions    # Tutorial run functions

            runApplication ./Allmesh

            #-- Run on single processor
            runApplication $(getApplication)

            # Decompose
            # runApplication decomposePar -allRegions

            # Run
            # runParallel $(getApplication)

            # Reconstruct
            # runApplication reconstructPar -allRegions

            #------------------------------------------------------------------------------
            """
        )

def generateAllclean(file_path):
    with open(file_path, 'w') as fd:
        fd.write(
            """
            #!/bin/sh
            cd ${0%/*} || exit 1                        # Run from this directory
            . $WM_PROJECT_DIR/bin/tools/CleanFunctions  # Tutorial clean functions

            cleanCase0

            rm -rf VTK
            rm -rf constant/cellToRegion
            rm -rf constant/*/polyMesh  # region meshes

            #------------------------------------------------------------------------------
            """
        )
