#!/usr/bin/env python

import random

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
                location    "system";
                object      fvSolution;
            }
            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

            solvers
            {
                T
                {
                    solver          PCG;
                    preconditioner  DIC;
                    tolerance       1e-06;
                    relTol          0;
                }
            }

            SIMPLE
            {
                nNonOrthogonalCorrectors 2;
            }


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
                location    "system";
                object      fvSchemes;
            }
            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

            ddtSchemes
            {
                default         Euler;
            }

            gradSchemes
            {
                default         Gauss linear;
                grad(T)         Gauss linear;
            }

            divSchemes
            {
                default         none;
            }

            laplacianSchemes
            {
                default         none;
                laplacian(DT,T) Gauss linear corrected;
            }

            interpolationSchemes
            {
                default         linear;
            }

            snGradSchemes
            {
                default         corrected;
            }


            // ************************************************************************* //
            """
        )

def generateDecomposeParDict(file_path):
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
                object      decomposeParDict;
            }
            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

            numberOfSubdomains 2;

            method          simple;

            simpleCoeffs
            {
                n               (1 2 1);
                delta           0.001;
            }

            hierarchicalCoeffs
            {
                n               (1 1 1);
                delta           0.001;
                order           xyz;
            }

            manualCoeffs
            {
                dataFile        "";
            }

            distributed     no;

            roots           ( );

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

            application     laplacianFoam;

            startFrom       latestTime;

            startTime       0;

            stopAt          endTime;

            endTime         1;

            deltaT          0.005;

            writeControl    runTime;

            writeInterval   0.1;

            purgeWrite      0;

            writeFormat     ascii;

            writePrecision  6;

            writeCompression off;

            timeFormat      general;

            timePrecision   6;

            runTimeModifiable true;


            // ************************************************************************* //
            """
        )

def generateMeshDictFile(file_path):
    L = 1.0
    N = 256
    dx = L / N
    dy = L / N

    aRan = random.randint(1, N - 1)
    bRan = random.randint(1, N - 1)
    cRan = random.randint(1, N - 1)
    dRan = random.randint(1, N - 1)

    if aRan == bRan:
        bRan += 1
    if cRan == dRan:
        dRan += 1

    if aRan < bRan:
        h1 = aRan
        h2 = bRan
    else:
        h1 = bRan
        h2 = aRan
    if cRan < dRan:
        v1 = cRan
        v2 = dRan
    else:
        v1 = dRan
        v2 = cRan

    NleftX = h1
    NcenterX = (h2 - h1)
    NbottomY = v1
    NcenterY = (v2 - v1)
    NtopY = (N - v2)
    NrightX = (N - h2)

    x1 = 0.0
    x2 = h1 * dx
    x3 = h2 * dx
    x4 = N * dx
    y1 = 0.0
    y2 = v1 * dy
    y3 = v2 * dy
    y4 = N * dy
    z1 = 0.0
    z2 = 0.1

    # print NleftX
    # print NcenterX
    # print NbottomY
    # print NcenterY
    # print NtopY
    # print NrightX

    data = {
        'NleftX': NleftX,
        'NcenterX': NcenterX,
        'NrightX': NrightX,
        'NbottomY': NbottomY,
        'NtopY': NtopY,
        'NcenterY': NcenterY,
        'xCoor1': x1,
        'xCoor2': x2,
        'xCoor3': x3,
        'xCoor4': x4,
        'yCoor1': y1,
        'yCoor2': y2,
        'yCoor3': y3,
        'yCoor4': y4,
        'zCoor1': z1,
        'zCoor2': z2,
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
                object      blockMeshDict;
            }}
            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

            scale   0.1;

            vertices
            (
                // block 0
                ({xCoor1} {yCoor1} {zCoor1})     		// vertex 0
                ({xCoor2} {yCoor1} {zCoor1})     		// vertex 1
                ({xCoor2} {yCoor2} {zCoor1})     		// vertex 2
                ({xCoor1} {yCoor2} {zCoor1})     		// vertex 3
                ({xCoor1} {yCoor1} {zCoor2})     		// vertex 4
                ({xCoor2} {yCoor1} {zCoor2})     		// vertex 5
                ({xCoor2} {yCoor2} {zCoor2})     		// vertex 6
                ({xCoor1} {yCoor2} {zCoor2})     		// vertex 7

                // block 1
                ({xCoor3} {yCoor1} {zCoor1})     		// vertex 8
                ({xCoor3} {yCoor2} {zCoor1})     		// vertex 9
                ({xCoor3} {yCoor1} {zCoor2})     		// vertex 10
                ({xCoor3} {yCoor2} {zCoor2})     		// vertex 11

                // block 2
                ({xCoor4} {yCoor1} {zCoor1})     	  // vertex 12
                ({xCoor4} {yCoor2} {zCoor1})     	  // vertex 13
                ({xCoor4} {yCoor1} {zCoor2})     	  // vertex 14
                ({xCoor4} {yCoor2} {zCoor2})     	  // vertex 15

                // block 3
                ({xCoor4} {yCoor3} {zCoor1})     		// vertex 16
                ({xCoor3} {yCoor3} {zCoor1})     		// vertex 17
                ({xCoor4} {yCoor3} {zCoor2})     		// vertex 18
                ({xCoor3} {yCoor3} {zCoor2})     		// vertex 19

                // block 4
                ({xCoor4} {yCoor4} {zCoor1})     		// vertex 20
                ({xCoor3} {yCoor4} {zCoor1})     		// vertex 21
                ({xCoor4} {yCoor4} {zCoor2})     		// vertex 22
                ({xCoor3} {yCoor4} {zCoor2})     		// vertex 23

                // block 5
                ({xCoor2} {yCoor4} {zCoor1})     		// vertex 24
                ({xCoor2} {yCoor3} {zCoor1})     		// vertex 25
                ({xCoor2} {yCoor4} {zCoor2})     		// vertex 26
                ({xCoor2} {yCoor3} {zCoor2})     		// vertex 27

                // block 6
                ({xCoor1} {yCoor4} {zCoor1})     		// vertex 28
                ({xCoor1} {yCoor3} {zCoor1})     		// vertex 29
                ({xCoor1} {yCoor4} {zCoor2})     		// vertex 30
                ({xCoor1} {yCoor3} {zCoor2})     		// vertex 31

                // block 7
            );

            blocks
            (
                hex (0 1 2 3 4 5 6 7) ({NleftX} {NbottomY} 1) simpleGrading (1 1 1)             // block 0
                hex (1 8 9 2 5 10 11 6) ({NcenterX} {NbottomY} 1) simpleGrading (1 1 1)         // block 1
                hex (8 12 13 9 10 14 15 11) ({NrightX} {NbottomY} 1) simpleGrading (1 1 1)      // block 2
                hex (13 16 17 9 15 18 19 11) ({NcenterY} {NrightX} 1) simpleGrading (1 1 1)     // block 3
                hex (16 20 21 17 18 22 23 19) ({NtopY} {NrightX} 1) simpleGrading (1 1 1)       // block 4
                hex (21 24 25 17 23 26 27 19) ({NcenterX} {NtopY} 1) simpleGrading (1 1 1)      // block 5
                hex (24 28 29 25 26 30 31 27) ({NleftX} {NtopY} 1) simpleGrading (1 1 1)        // block 6
                hex (29 3 2 25 31 7 6 27) ({NcenterY} {NleftX} 1) simpleGrading (1 1 1)         // block 7
            );

            edges
            (
            );

            boundary
            (
                leftWall
                {{
                    type wall;
                    faces
                    (
                        (0 4 7 3)
                        (3 7 31 29)
                        (29 31 30 28)
                    );
                }}
                topWall
                {{
                    type wall;
                    faces
                    (
                        (26 24 28 30)
                        (23 21 24 26)
                        (22 20 21 23)
                    );
                }}
                rightWall
                {{
                    type wall;
                    faces
                    (
                        (18 16 20 22)
                        (15 13 16 18)
                        (14 12 13 15)
                    );
                }}
                bottomWall
                {{
                    type wall;
                    faces
                    (
                        (10 8 12 14)
                        (5 1 8 10)
                        (4 0 1 5)
                    );
                }}
                frontAndBack
                {{
                    type empty;
                    faces
                    (
                        (0 3 2 1)
                        (1 2 9 8)
                        (8 9 13 12)
                        (9 17 16 13)
                        (17 21 20 16)
                        (25 24 21 17)
                        (29 28 24 25)
                        (3 29 25 2)

                        (5 6 7 4)
                        (10 11 6 5)
                        (14 15 11 10)
                        (15 18 19 11)
                        (18 22 23 19)
                        (19 23 26 27)
                        (27 26 30 31)
                        (6 27 31 7)
                    );
                }}
                leftSmallWall
                {{
                    type wall;
                    faces
                    (
                        (2 25 27 6)
                    );
                }}
                topSmallWall
                {{
                    type wall;
                    faces
                    (
                        (19 27 25 17)
                    );
                }}
                rightSmallWall
                {{
                    type wall;
                    faces
                    (
                        (11 19 17 9)
                    );
                }}
                bottomSmallWall
                {{
                    type wall;
                    faces
                    (
                        (11 9 2 6)
                    );
                }}
            );

            mergePatchPairs
            (
            );

            // ************************************************************************* //
            """.format(**data)
        )
