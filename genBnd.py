#!/usr/bin/env python

def generateBoundary(file_path):
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

            internalField uniform 273;

            boundaryField
            {

            	topWall {
                    	type zeroGradient; //adiabatic
            	}

            	rightWall {
                    	type zeroGradient; //adiabatic
            	}

            	bottomWall {
                    	type zeroGradient; //adiabatic
            	}

            	leftSmallWall {
                    	type fixedValue; // fixed Temperature b.c.
            		value uniform 373;
            	}

            	topSmallWall {
                    	type fixedValue; // fixed Temperature b.c.
            		value uniform 373;
            	}

            	rightSmallWall {
                    	type fixedValue; // fixed Temperature b.c.
            		value uniform 373;
            	}

            	bottomSmallWall {
                    	type fixedValue; // fixed Temperature b.c.
            		value uniform 373;
            	}

            	leftWall {
            		type fixedValue; // fixed Temperature b.c.
            		value uniform 473;
            	}
            }
            """
        )
