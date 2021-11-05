
Info<< "Reading field C_Li_ion\n" << endl;
volScalarField C_Li_ion
(
    IOobject
    (
        "C_Li_ion",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading field D_Li_ion\n" << endl;
volScalarField D_Li_ion
(
    IOobject
    (
        "D_Li_ion",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("D_Li_ion", dimensionSet(0,0,0,0,0,0,0), 1.0e-22),
    zeroGradientFvPatchScalarField::typeName
);

Info<< "Reading field S_ionize\n" << endl;
volScalarField S_ionize
(
    IOobject
    (
        "S_ionize",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("S_ionize", dimensionSet(0,0,0,0,0,0,0), 0.0),
    zeroGradientFvPatchScalarField::typeName
);

Info<< "Reading field S_Li_ion\n" << endl;
volScalarField S_Li_ion
(
    IOobject
    (
        "S_Li_ion",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("S_Li_ion", dimensionSet(0,0,0,0,0,0,0), 0.0),
    zeroGradientFvPatchScalarField::typeName
);

Info<< "Reading field C_Li\n" << endl;
volScalarField C_Li
(
    IOobject
    (
        "C_Li",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading field D_Li\n" << endl;
volScalarField D_Li
(
    IOobject
    (
        "D_Li",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("D_Li", dimensionSet(0,0,0,0,0,0,0), 1.0e-22),
    zeroGradientFvPatchScalarField::typeName
);

Info<< "Reading field S_Li\n" << endl;
volScalarField S_Li
(
    IOobject
    (
        "S_Li",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("S_Li", dimensionSet(0,0,0,0,0,0,0), 0.0),
    zeroGradientFvPatchScalarField::typeName
);

Info<< "Reading field phi_e\n" << endl;
volScalarField phi_e
(
    IOobject
    (
        "phi_e",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading field sigma_e\n" << endl;
volScalarField sigma_e
(
    IOobject
    (
        "sigma_e",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("sigma_e", dimensionSet(0,0,0,0,0,0,0), 1.0e-22),
    zeroGradientFvPatchScalarField::typeName
);

Info<< "Reading field phi_ion\n" << endl;
volScalarField phi_ion
(
    IOobject
    (
        "phi_ion",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading field sigma_ion\n" << endl;
volScalarField sigma_ion
(
    IOobject
    (
        "sigma_ion",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("sigma_ion", dimensionSet(0,0,0,0,0,0,0), 1.0e-22),
    zeroGradientFvPatchScalarField::typeName
);

Info<< "Reading field S_e\n" << endl;
volScalarField S_e
(
    IOobject
    (
        "S_e",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("S_e", dimensionSet(0,0,0,0,0,0,0), 0.0),
    zeroGradientFvPatchScalarField::typeName
);

Info<< "Reading field dS_e\n" << endl;
volScalarField dS_e
(
    IOobject
    (
        "dS_e",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    mesh,
    dimensionedScalar("dS_e", dimensionSet(0,0,0,0,0,0,0), 0.0),
    zeroGradientFvPatchScalarField::typeName
);

Info<< "Reading field S_ion\n" << endl;
volScalarField S_ion
(
    IOobject
    (
        "S_ion",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("S_ion", dimensionSet(0,0,0,0,0,0,0), 0.0),
    zeroGradientFvPatchScalarField::typeName
);


Info<< "Reading field dS_ion\n" << endl;
volScalarField dS_ion
(
    IOobject
    (
        "dS_ion",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    mesh,
    dimensionedScalar("dS_ion", dimensionSet(0,0,0,0,0,0,0), 0.0),
    zeroGradientFvPatchScalarField::typeName
);

volVectorField current_e
(
    IOobject
    (
        "current_e",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedVector("current_e", dimensionSet(0,0,0,0,0,0,0), vector(0.0,0.0,0.0))
);

volVectorField current_ion
(
    IOobject
    (
        "current_ion",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedVector("current_ion", dimensionSet(0,0,0,0,0,0,0), vector(0.0,0.0,0.0))
);

surfaceScalarField over_pen
(
    IOobject
    (
        "over_pen",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("over_pen", dimensionSet(0,0,0,0,0,0,0), 0.0)
);

surfaceScalarField sur_CLi
(
    IOobject
    (
        "sur_CLi",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("sur_CLi", dimensionSet(0,0,0,0,0,0,0), 0.0)
);

#include "createFvOptions.H"
