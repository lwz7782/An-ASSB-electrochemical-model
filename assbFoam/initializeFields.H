Info<< "\nInitializing fields\n" << endl;

word electrolyteName = "electrolyte";
label electrolyteID = mesh.cellZones().findZoneID(electrolyteName);

labelList electrolyte = mesh.cellZones()[electrolyteID];
forAll(electrolyte, iCells)
{
    const label& celli = electrolyte[iCells];
    C_Li_ion[celli] = 38464.0;
}

word poselectrodeName = "electrode-pos";
label poselectrodeID = mesh.cellZones().findZoneID(poselectrodeName);

labelList poselectrode = mesh.cellZones()[poselectrodeID];
forAll(poselectrode, iCells)
{
    const label& celli = poselectrode[iCells];

    C_Li[celli] = 16100.0;

    phi_e[celli] = 4.1936;
}

word poscurrentName = "current-pos";
label poscurrentID = mesh.cellZones().findZoneID(poscurrentName);

labelList poscurrent = mesh.cellZones()[poscurrentID];
forAll(poscurrent, iCells)
{
    const label& celli = poscurrent[iCells];
    phi_e[celli] = 4.1936;
}



