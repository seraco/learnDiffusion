#!/usr/bin/env python

import random
from math import sqrt

def generateFvSolution(file_path):
    with open(file_path, 'w') as fd:
        fd.write(
            """
            /*--------------------------------*- C++ -*----------------------------------*\\
            | =========                 |                                                 |
            | \\\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox           |
            |  \\\    /   O peration     | Version:  plus                                  |
            |   \\\  /    A nd           | Web:      www.OpenFOAM.com                      |
            |    \\\/     M anipulation  |                                                 |
            \*---------------------------------------------------------------------------*/
            FoamFile
            {
                version     2.0;
                format      ascii;
                class       dictionary;
                object      fvSolution;
            }
            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

            // ************************************************************************* //
            """
        )

def generateFvSchemes(file_path):
    with open(file_path, 'w') as fd:
        fd.write(
            """
            /*--------------------------------*- C++ -*----------------------------------*\\
            | =========                 |                                                 |
            | \\\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox           |
            |  \\\    /   O peration     | Version:  plus                                  |
            |   \\\  /    A nd           | Web:      www.OpenFOAM.com                      |
            |    \\\/     M anipulation  |                                                 |
            \*---------------------------------------------------------------------------*/
            FoamFile
            {
                version     2.0;
                format      ascii;
                class       dictionary;
                object      fvSchemes;
            }
            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

            ddtSchemes
            {
            }

            gradSchemes
            {
            }

            divSchemes
            {
            }

            laplacianSchemes
            {
            }

            interpolationSchemes
            {
            }

            snGradSchemes
            {
            }


            // ************************************************************************* //
            """
        )

def generateControlDict(file_path):
    with open(file_path, 'w') as fd:
        fd.write(
            """
            /*--------------------------------*- C++ -*----------------------------------*\\
            | =========                 |                                                 |
            | \\\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox           |
            |  \\\    /   O peration     | Version:  plus                                  |
            |   \\\  /    A nd           | Web:      www.OpenFOAM.com                      |
            |    \\\/     M anipulation  |                                                 |
            \*---------------------------------------------------------------------------*/
            FoamFile
            {
                version     2.0;
                format      ascii;
                class       dictionary;
                location    "system";
                object      controlDict;
            }
            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

            application     chtMultiRegionSimpleFoam;

            startFrom       startTime;

            startTime       0;

            stopAt          endTime;

            endTime         300;

            deltaT          1;

            writeControl    timeStep;

            writeInterval   10;

            purgeWrite      10;

            writeFormat     ascii;

            writePrecision  7;

            writeCompression uncompressed;

            timeFormat      general;

            timePrecision   6;

            runTimeModifiable true;

            functions
            {
                #includeFunc  residuals
            }

            // maxCo           0.6;

            // Maximum diffusion number
            // maxDi           10.0;

            // adjustTimeStep  yes;

            // ************************************************************************* //
            """
        )

def generateBlockMeshDict(file_path):
    with open(file_path, 'w') as fd:
        fd.write(
            """
            /*--------------------------------*- C++ -*----------------------------------*\\
            | =========                 |                                                 |
            | \\\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox           |
            |  \\\    /   O peration     | Version:  plus                                  |
            |   \\\  /    A nd           | Web:      www.OpenFOAM.com                      |
            |    \\\/     M anipulation  |                                                 |
            \*---------------------------------------------------------------------------*/
            FoamFile
            {
                version     2.0;
                format      ascii;
                class       dictionary;
                object      blockMeshDict;
            }
            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

            scale   1;

            vertices
            (
                (-0.1 -0.1  -0.01)
                ( 0.1 -0.1  -0.01)
                ( 0.1  0.1  -0.01)
                (-0.1  0.1  -0.01)
                (-0.1 -0.1   0.01)
                ( 0.1 -0.1   0.01)
                ( 0.1  0.1   0.01)
                (-0.1  0.1   0.01)
            );

            blocks
            (
                hex (0 1 2 3 4 5 6 7) (256 256 1) simpleGrading (1 1 1)
            );

            edges
            (
            );

            boundary
            (
                maxY
                {
                    type wall;
                    faces
                    (
                        (3 7 6 2)
                    );
                }
                minX
                {
                    type wall;
                    faces
                    (
                        (0 4 7 3)
                    );
                }
                maxX
                {
                    type wall;
                    faces
                    (
                        (2 6 5 1)
                    );
                }
                minY
                {
                    type wall;
                    faces
                    (
                        (1 5 4 0)
                    );
                }
                minZ
                {
                    type wall;
                    faces
                    (
                        (0 3 2 1)
                    );
                }
                maxZ
                {
                    type wall;
                    faces
                    (
                        (4 5 6 7)
                    );
                }
            );

            mergePatchPairs
            (
            );

            // ************************************************************************* //
            """
        )

def generateHeaterChangeDict(file_path):
    with open(file_path, 'w') as fd:
        fd.write(
            """
            /*--------------------------------*- C++ -*----------------------------------*\\
            | =========                 |                                                 |
            | \\\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox           |
            |  \\\    /   O peration     | Version:  plus                                  |
            |   \\\  /    A nd           | Web:      www.OpenFOAM.com                      |
            |    \\\/     M anipulation  |                                                 |
            \*---------------------------------------------------------------------------*/
            FoamFile
            {
                version     2.0;
                format      ascii;
                class       dictionary;
                object      changeDictionaryDict;
            }
            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

            boundary
            {
                // minY
                // {
                //     type            patch;
                // }
                // minZ
                // {
                //     type            patch;
                // }
                // maxZ
                // {
                //     type            patch;
                // }
            }

            T
            {
                internalField   uniform 500;

                boundaryField
                {
                    ".*"
                    {
                        type            fixedValue;
                        value           uniform 500;
                    }
                    "heater_to_mainSolid"
                    {
                        type            compressible::turbulentTemperatureCoupledBaffleMixed;
                        Tnbr            T;
                        kappaMethod     solidThermo;
                        value           uniform 300;
                    }

                    // heater_to_leftSolid
                    // {
                    //     type            compressible::turbulentTemperatureCoupledBaffleMixed;
                    //     Tnbr            T;
                    //     kappaMethod     solidThermo;
                    //     thicknessLayers (1e-3);
                    //     kappaLayers     (5e-4);
                    //     value           uniform 300;
                    // }
                    //
                    // minY
                    // {
                    //     type            fixedValue;
                    //     value           uniform 500;
                    // }
                }
            }

            // ************************************************************************* //
            """
        )

def generateHeaterFvSchemes(file_path):
    with open(file_path, 'w') as fd:
        fd.write(
            """
            /*--------------------------------*- C++ -*----------------------------------*\\
            | =========                 |                                                 |
            | \\\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox           |
            |  \\\    /   O peration     | Version:  plus                                  |
            |   \\\  /    A nd           | Web:      www.OpenFOAM.com                      |
            |    \\\/     M anipulation  |                                                 |
            \*---------------------------------------------------------------------------*/
            FoamFile
            {
                version     2.0;
                format      ascii;
                class       dictionary;
                object      fvSchemes;
            }
            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

            ddtSchemes
            {
                default steadyState;
            }

            gradSchemes
            {
                default         Gauss linear;
            }

            divSchemes
            {
                default         none;
            }

            laplacianSchemes
            {
                default             none;
                laplacian(alpha,h)  Gauss linear uncorrected;
            }

            interpolationSchemes
            {
                default         linear;
            }

            snGradSchemes
            {
                default         uncorrected;
            }


            // ************************************************************************* //
            """
        )

def generateHeaterFvSolution(file_path):
    with open(file_path, 'w') as fd:
        fd.write(
            """
            /*--------------------------------*- C++ -*----------------------------------*\\
            | =========                 |                                                 |
            | \\\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox           |
            |  \\\    /   O peration     | Version:  plus                                  |
            |   \\\  /    A nd           | Web:      www.OpenFOAM.com                      |
            |    \\\/     M anipulation  |                                                 |
            \*---------------------------------------------------------------------------*/
            FoamFile
            {
                version     2.0;
                format      ascii;
                class       dictionary;
                object      fvSolution;
            }
            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

            solvers
            {
                h
                {
                    solver           PCG;
                    preconditioner   DIC;
                    tolerance        1e-06;
                    relTol           0.1;
                }
            }

            SIMPLE
            {
                nNonOrthogonalCorrectors 0;
            }

            relaxationFactors
            {
                equations
                {
                    h               0.7;
                }
            }

            // ************************************************************************* //
            """
        )

def generateMainSolidChangeDict(file_path):
    with open(file_path, 'w') as fd:
        fd.write(
            """
            /*--------------------------------*- C++ -*----------------------------------*\\
            | =========                 |                                                 |
            | \\\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox           |
            |  \\\    /   O peration     | Version:  plus                                  |
            |   \\\  /    A nd           | Web:      www.OpenFOAM.com                      |
            |    \\\/     M anipulation  |                                                 |
            \*---------------------------------------------------------------------------*/
            FoamFile
            {
                version     2.0;
                format      ascii;
                class       dictionary;
                object      changeDictionaryDict;
            }
            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

            boundary
            {
                minX
                {
                    type            wall;
                }
                maxX
                {
                    type            wall;
                }
                minY
                {
                    type            wall;
                }
                maxY
                {
                    type            wall;
                }
                minZ
                {
                    type            wall;
                }
                maxZ
                {
                    type            wall;
                }
            }

            T
            {
                internalField   uniform 300;

                boundaryField
                {
                    ".*"
                    {
                        type            zeroGradient;
                        value           uniform 300;
                    }
                    "mainSolid_to_heater"
                    {
                        type            compressible::turbulentTemperatureCoupledBaffleMixed;
                        Tnbr            T;
                        kappaMethod     solidThermo;
                        value           uniform 500;
                    }

                    // heater_to_leftSolid
                    // {
                    //     type            compressible::turbulentTemperatureCoupledBaffleMixed;
                    //     Tnbr            T;
                    //     kappaMethod     solidThermo;
                    //     thicknessLayers (1e-3);
                    //     kappaLayers     (5e-4);
                    //     value           uniform 300;
                    // }

                    // minY
                    // {
                    //     type            fixedValue;
                    //     value           uniform 500;
                    // }
                }
            }

            // ************************************************************************* //
            """
        )

def generateMainSolidFvSchemes(file_path):
    with open(file_path, 'w') as fd:
        fd.write(
            """
            /*--------------------------------*- C++ -*----------------------------------*\\
            | =========                 |                                                 |
            | \\\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox           |
            |  \\\    /   O peration     | Version:  plus                                  |
            |   \\\  /    A nd           | Web:      www.OpenFOAM.com                      |
            |    \\\/     M anipulation  |                                                 |
            \*---------------------------------------------------------------------------*/
            FoamFile
            {
                version     2.0;
                format      ascii;
                class       dictionary;
                object      fvSchemes;
            }
            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

            ddtSchemes
            {
                default steadyState;
            }

            gradSchemes
            {
                default         Gauss linear;
            }

            divSchemes
            {
                default         none;
            }

            laplacianSchemes
            {
                default             none;
                laplacian(alpha,h)  Gauss linear uncorrected;
            }

            interpolationSchemes
            {
                default         linear;
            }

            snGradSchemes
            {
                default         uncorrected;
            }


            // ************************************************************************* //
            """
        )

def generateMainSolidFvSolution(file_path):
    with open(file_path, 'w') as fd:
        fd.write(
            """
            /*--------------------------------*- C++ -*----------------------------------*\\
            | =========                 |                                                 |
            | \\\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox           |
            |  \\\    /   O peration     | Version:  plus                                  |
            |   \\\  /    A nd           | Web:      www.OpenFOAM.com                      |
            |    \\\/     M anipulation  |                                                 |
            \*---------------------------------------------------------------------------*/
            FoamFile
            {
                version     2.0;
                format      ascii;
                class       dictionary;
                object      fvSolution;
            }
            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

            solvers
            {
                h
                {
                    solver           PCG;
                    preconditioner   DIC;
                    tolerance        1e-06;
                    relTol           0.1;
                }
            }

            SIMPLE
            {
                nNonOrthogonalCorrectors 0;
            }

            relaxationFactors
            {
                equations
                {
                    h               0.7;
                }
            }

            // ************************************************************************* //
            """
        )

def generateTopoSetDict(file_path):
    shape = 'cyl' # 'box'/'cyl'

    Nx = 30
    Ny = 10

    minX = -0.09
    maxX =  0.09
    minY = -0.09
    maxY =  0.09
    minZ = -0.01
    maxZ =  0.01

    deltaX = (maxX - minX) / Nx
    deltaY = (maxY - minY) / Ny

    aRanX = random.uniform(minX, maxX)
    bRanX = random.uniform(minX, maxX)
    aRanY = random.uniform(minY, maxY)
    bRanY = random.uniform(minY, maxY)

    while abs(aRanX - bRanX) < 1.1*deltaX:
        bRanX += random.uniform(minX, maxX)
    while abs(aRanY - bRanY) < 1.1*deltaY:
        bRanY += random.uniform(minY, maxY)

    if aRanX < bRanX:
        x1 = aRanX
        x2 = bRanX
    else:
        x1 = bRanX
        x2 = aRanX
    if aRanY < bRanY:
        y1 = aRanY
        y2 = bRanY
    else:
        y1 = bRanY
        y2 = aRanY

    z1 = minZ
    z2 = maxZ

    if shape is 'box':
        srcTp = 'boxToCell'
        srcInStr = 'box ({} {} {}) ({} {} {});'.format(x1, y1, z1, x2, y2, z2)
    else:
        rds = abs(x2 - x1) / 2
        srcTp = 'cylinderToCell'
        srcInStr = 'p1 ({} {} {}); p2 ({} {} {}); radius {};'.format(x1, y1, z1, x1, y1, z2, rds)

    data = {
        'srcType': srcTp,
        'srcInfoString': srcInStr,
    }

    with open(file_path, 'w') as fd:
        fd.write(
            """
            /*--------------------------------*- C++ -*----------------------------------*\\
            | =========                 |                                                 |
            | \\\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox           |
            |  \\\    /   O peration     | Version:  plus                                  |
            |   \\\  /    A nd           | Web:      www.OpenFOAM.com                      |
            |    \\\/     M anipulation  |                                                 |
            \*---------------------------------------------------------------------------*/
            FoamFile
            {{
                version     2.0;
                format      ascii;
                class       dictionary;
                object      topoSetDict;
            }}

            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

            actions
            (
                // heater
                {{
                    name    heaterCellSet;
                    type    cellSet;
                    action  new;
                    source  {srcType};
                    sourceInfo
                    {{
                        {srcInfoString}
                    }}
                }}
                {{
                    name    heater;
                    type    cellZoneSet;
                    action  new;
                    source  setToCellZone;
                    sourceInfo
                    {{
                        set heaterCellSet;
                    }}
                }}

                // mainSolid is all the other cells
                {{
                    name    mainSolidCellSet;
                    type    cellSet;
                    action  new;
                    source  cellToCell;
                    sourceInfo
                    {{
                        set heaterCellSet;
                    }}
                }}
                {{
                    name    mainSolidCellSet;
                    type    cellSet;
                    action  invert;
                }}
                {{
                    name    mainSolid;
                    type    cellZoneSet;
                    action  new;
                    source  setToCellZone;
                    sourceInfo
                    {{
                        set mainSolidCellSet;
                    }}
                }}
            );


            // ************************************************************************* //
            """.format(**data)
        )

def generateResiduals(file_path):
    with open(file_path, 'w') as fd:
        fd.write(
            """
            /*--------------------------------*- C++ -*----------------------------------*\\
            | =========                 |                                                 |
            | \\\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox           |
            |  \\\    /   O peration     | Version:  plus                                  |
            |   \\\  /    A nd           | Web:      www.OpenFOAM.com                      |
            |    \\\/     M anipulation  |                                                 |
            \*---------------------------------------------------------------------------*/
            #includeEtc "caseDicts/postProcessing/numerical/residuals.cfg"

            fields (T);

            // ************************************************************************* //
            """
        )
