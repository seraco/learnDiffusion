#!/usr/bin/env python

def generatePressure(file_path):
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
                class       volScalarField;
                object      p;
            }
            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

            dimensions      [1 -1 -2 0 0 0 0];

            internalField   uniform 1e5;

            boundaryField
            {
                ".*"
                {
                    type            calculated;
                    value           uniform 1e5;
                }
            }

            // ************************************************************************* //
            """
        )

def generateTemperature(file_path):
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
                class       volScalarField;
                object      T;
            }
            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

            dimensions      [0 0 0 1 0 0 0];

            internalField   uniform 300;

            boundaryField
            {
                ".*"
                {
                    type            calculated;
                    value           uniform 300;
                }
            }

            // ************************************************************************* //
            """
        )
