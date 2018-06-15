#!/usr/bin/env python

def generateRegionProperties(file_path):
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
                location    "constant";
                object      regionProperties;
            }
            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

            regions
            (
                fluid       ()
                solid       (heater mainSolid)
            );

            // ************************************************************************* //
            """
        )

def generateRadiationProperties(file_path):
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
                location    "constant";
                object      radiationProperties;
            }
            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

            radiation off;

            radiationModel  none;

            // ************************************************************************* //
            """
        )

def generateHeaterThermoProperties(file_path):
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
                object      thermophysicalProperties;
            }
            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

            thermoType
            {
                type            heSolidThermo;
                mixture         pureMixture;
                transport       constIso;
                thermo          hConst;
                equationOfState rhoConst;
                specie          specie;
                energy          sensibleEnthalpy;
            }

            mixture
            {
                // specie
                // {
                //     molWeight   27;
                // }
                //
                // transport
                // {
                //     kappa   143;
                // }
                //
                // thermodynamics
                // {
                //     Hf      0;
                //     Cp      795;
                // }
                //
                // equationOfState
                // {
                //     rho     2800;
                // }
                specie
                {
                    molWeight   27;
                }

                transport
                {
                    kappa   0;
                }

                thermodynamics
                {
                    Hf      0;
                    Cp      795;
                }

                equationOfState
                {
                    rho     2800;
                }
            }

            // ************************************************************************* //
            """
        )

def generateMainSolidThermoProperties(file_path):
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
                object      thermophysicalProperties;
            }
            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

            thermoType
            {
                type            heSolidThermo;
                mixture         pureMixture;
                transport       constIso;
                thermo          hConst;
                equationOfState rhoConst;
                specie          specie;
                energy          sensibleEnthalpy;
            }

            mixture
            {
                specie
                {
                    molWeight   50;
                }

                transport
                {
                    kappa   80;
                }

                thermodynamics
                {
                    Hf      0;
                    Cp      450;
                }

                equationOfState
                {
                    rho     8000;
                }
            }

            // ************************************************************************* //
            """
        )
