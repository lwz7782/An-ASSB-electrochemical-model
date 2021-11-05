Info<< "\nCalculating fields\n" << endl;

word electrolyteName = "electrolyte";
label electrolyteID = mesh.cellZones().findZoneID(electrolyteName);

labelList electrolyte = mesh.cellZones()[electrolyteID];
forAll(electrolyte, iCells)
{
    const label& celli = electrolyte[iCells];

    scalar CLiion = C_Li_ion[celli];

    if(CLiion < 0.0) CLiion = 0.0;
    if(CLiion > 60100.0) CLiion = 60100.0;

    D_Li_ion[celli] = 2.65e-16;
    S_ionize[celli] = 8.0e-7*(38464.0*38464.0-CLiion*CLiion);
}

word poselectrodeName = "electrode-pos";
label poselectrodeID = mesh.cellZones().findZoneID(poselectrodeName);

labelList poselectrode = mesh.cellZones()[poselectrodeID];
forAll(poselectrode, iCells)
{
    const label& celli = poselectrode[iCells];

    scalar CLi = C_Li[celli];

    if(CLi < 16100.0)  CLi = 16100.0;
    else if(CLi > 32200.0)  CLi = 32200.0;

    scalar x = C_Li[celli]/32200.0;
    if(x <= 0.7)
    {
        D_Li[celli] = 1.04e-13;
    }
    else if(x < 0.92)
    {
        D_Li[celli] = 1.04e-13 + (5.38e-15-1.04e-13)/(0.92-0.7)*(x-0.7);
    }
    else
    {
        D_Li[celli] = 5.38e-15;
    }
}

word fz2Name = "interior-2";
label fz2ID = mesh.faceZones().findZoneID(fz2Name);

const labelList fz2 = mesh.faceZones()[fz2ID];
forAll(fz2,facei)
{
   const label faceID = fz2[facei];
   const label cell1ID = mesh.faceOwner()[faceID];
   const label cell2ID = mesh.faceNeighbour()[faceID];
   D_Li_ion[cell1ID] = 1.0e-22;

   S_Li_ion[cell1ID] = S_ion[cell1ID]/96485.0*(1.0-0.233);
}

word fz3Name = "interior-3";
label fz3ID = mesh.faceZones().findZoneID(fz3Name);

const labelList fz3 = mesh.faceZones()[fz3ID];
forAll(fz3,facei)
{
   const label faceID = fz3[facei];
   const label cell1ID = mesh.faceOwner()[faceID];
   const label cell2ID = mesh.faceNeighbour()[faceID];
   D_Li[cell1ID] = 1.0e-22;
   D_Li_ion[cell2ID] = 1.0e-22;

   sur_CLi[faceID] = C_Li[cell1ID];

   S_Li_ion[cell2ID] = S_ion[cell2ID]/96485.0*(1.0-0.233);
   S_Li[cell1ID] = S_e[cell1ID]/96485.0;
}

word fz4Name = "interior-4";
label fz4ID = mesh.faceZones().findZoneID(fz4Name);

const labelList fz4 = mesh.faceZones()[fz4ID];
forAll(fz4,facei)
{
   const label faceID = fz4[facei];
   const label cell1ID = mesh.faceOwner()[faceID];
   const label cell2ID = mesh.faceNeighbour()[faceID];
   D_Li[cell2ID] = 1.0e-22;
}




