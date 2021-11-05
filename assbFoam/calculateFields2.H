Info<< "\nCalculating fields\n" << endl;

current_e = sigma_e*fvc::grad(phi_e);
current_ion = sigma_ion*fvc::grad(phi_ion);

word negcurrentName = "current-neg";
label negcurrentID = mesh.cellZones().findZoneID(negcurrentName);

labelList negcurrent = mesh.cellZones()[negcurrentID];
forAll(negcurrent, iCells)
{
    const label& celli = negcurrent[iCells];
    sigma_e[celli] = 100.0;
}

word negelectrodeName = "electrode-neg";
label negelectrodeID = mesh.cellZones().findZoneID(negelectrodeName);

labelList negelectrode = mesh.cellZones()[negelectrodeID];
forAll(negelectrode, iCells)
{
    const label& celli = negelectrode[iCells];
    sigma_e[celli] = 100.0;
}

word electrolyteName = "electrolyte";
label electrolyteID = mesh.cellZones().findZoneID(electrolyteName);

labelList electrolyte = mesh.cellZones()[electrolyteID];
forAll(electrolyte, iCells)
{
    const label& celli = electrolyte[iCells];
    sigma_ion[celli] = 5.9e-4;
}

word poselectrodeName = "electrode-pos";
label poselectrodeID = mesh.cellZones().findZoneID(poselectrodeName);

labelList poselectrode = mesh.cellZones()[poselectrodeID];
forAll(poselectrode, iCells)
{
    const label& celli = poselectrode[iCells];

    sigma_e[celli] = 0.01;
}

word poscurrentName = "current-pos";
label poscurrentID = mesh.cellZones().findZoneID(poscurrentName);

labelList poscurrent = mesh.cellZones()[poscurrentID];
forAll(poscurrent, iCells)
{
    const label& celli = poscurrent[iCells];
    sigma_e[celli] = 100.0;
}


forAll(mesh.boundary(), patchi)
{
  forAll(mesh.boundary()[patchi], facei)
  {
    const label& bCell = mesh.boundaryMesh()[patchi].faceCells()[facei];

    sigma_e.boundaryFieldRef()[patchi][facei] = sigma_e[bCell];
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

    scalar CLiion = C_Li_ion[cell1ID];
    if(CLiion < 0.0) CLiion = 0.0;
    if(CLiion > 60100.0) CLiion = 60100.0;
   
    scalar i_ref = 1.0*96485.0*1.09e-9*Foam::pow(7.64e4,0.5)*Foam::pow(CLiion,0.5);
    scalar eta = phi_e[cell2ID]-phi_ion[cell1ID];
    scalar exponent_limit = 25.0;
    scalar exp_big = Foam::exp(exponent_limit);
    scalar exp_sml = 0.0;
    scalar eta_cut = 1.0e-10;

    scalar alpha_a = 0.5*96485.0/(8.3145*298.0);
    scalar alpha_c = -0.5*96485.0/(8.3145*298.0);

    scalar alpha_eta_a, alpha_eta_c, exp_a, exp_c;

    eta = eta - i_ref*0.001;
    if(eta < eta_cut)
    {
      eta = eta_cut;
    }
    else if(eta > 1.0)
    {
      eta = 1.0;
    }

    over_pen[faceID] = eta;

    alpha_eta_a = alpha_a*eta;
    if(exponent_limit < alpha_eta_a)
    {
      exp_a = exp_big;
    }
    else if(-exponent_limit > alpha_eta_a)
    {
      exp_a = exp_sml;
    }
    else
    {
      exp_a = Foam::exp(alpha_eta_a);
    }   

    alpha_eta_c = alpha_c*eta;
    if(exponent_limit < alpha_eta_c)
    {
      exp_c = exp_big;
    }
    else if(-exponent_limit > alpha_eta_c)
    {
      exp_c = exp_sml;
    }
    else
    {
      exp_c = Foam::exp(alpha_eta_c);
    }

    S_e[cell2ID] = -i_ref*(exp_a-exp_c)*mesh.magSf()[faceID]/mesh.V()[cell2ID];
    S_ion[cell1ID] = i_ref*(exp_a-exp_c)*mesh.magSf()[faceID]/mesh.V()[cell1ID];

    {
      scalar a_eta = alpha_a*eta;
      scalar c_eta = alpha_c*eta;
      if(a_eta > exponent_limit)
      {
        a_eta = exponent_limit;
      }
      else if(a_eta < -exponent_limit)
      {
        a_eta = -exponent_limit;
      }

      if (c_eta > exponent_limit)
      {
        c_eta = exponent_limit;
      }
      else if (c_eta < -exponent_limit)
      {
        c_eta = -exponent_limit;
      }
     
      dS_e[cell2ID] = -(alpha_a*Foam::exp(a_eta)-alpha_c*Foam::exp(c_eta))*i_ref*mesh.magSf()[faceID]/mesh.V()[cell2ID];
      dS_ion[cell1ID] = -(alpha_a*Foam::exp(a_eta)-alpha_c*Foam::exp(c_eta))*i_ref*mesh.magSf()[faceID]/mesh.V()[cell1ID];
    }
}

word fz3Name = "interior-3";
label fz3ID = mesh.faceZones().findZoneID(fz3Name);

const labelList fz3 = mesh.faceZones()[fz3ID];
forAll(fz3,facei)
{
    const label faceID = fz3[facei];
    const label cell1ID = mesh.faceOwner()[faceID];
    const label cell2ID = mesh.faceNeighbour()[faceID];

    scalar CLi = C_Li[cell1ID];
    scalar CLiion = C_Li_ion[cell2ID];

    if(CLiion < 0.0) CLiion = 0.0;
    if(CLiion > 60100.0) CLiion = 60100.0;
    
    if(CLi < 16100.0)  CLi = 16100.0;
    else if(CLi > 32200.0)  CLi = 32200.0;

    scalar y = CLi/32200.0;
    scalar E_eq = (-4.656+88.669*Foam::pow(y,2)-401.119*Foam::pow(y,4)+342.909*Foam::pow(y,6)-462.471*Foam::pow(y,8)+433.434*Foam::pow(y,10))/(-1+18.933*Foam::pow(y,2)-79.532*Foam::pow(y,4)+37.311*Foam::pow(y,6)-73.083*Foam::pow(y,8)+95.96*Foam::pow(y,10));

    scalar i_ref = 1.0*96485.0*1.53e-11*Foam::pow((32200.0-CLi),0.5)*Foam::pow(CLi,0.5)*Foam::pow(CLiion,0.5);

    scalar eta = phi_e[cell1ID]-phi_ion[cell2ID];
    scalar exponent_limit = 25.0;
    scalar exp_big = Foam::exp(exponent_limit);
    scalar exp_sml = 0.0;
    scalar eta_cut = 1.0e-10;

    scalar alpha_a = 0.5*96485.0/(8.3145*298.0);
    scalar alpha_c = -0.5*96485.0/(8.3145*298.0);

    scalar alpha_eta_a, alpha_eta_c, exp_a, exp_c;

    eta = eta - E_eq - i_ref*0.001;
    if(eta > -eta_cut)
    {
      eta = -eta_cut;
    }
    else if(eta < -1.0)
    {
      eta = -1.0;
    }

    over_pen[faceID] = eta;

    alpha_eta_a = alpha_a*eta;
    if(exponent_limit < alpha_eta_a)
    {
      exp_a = exp_big;
    }
    else if(-exponent_limit > alpha_eta_a)
    {
      exp_a = exp_sml;
    }
    else
    {
      exp_a = Foam::exp(alpha_eta_a);
    } 

    alpha_eta_c = alpha_c*eta;
    if(exponent_limit < alpha_eta_c)
    {
      exp_c = exp_big;
    }
    else if(-exponent_limit > alpha_eta_c)
    {
      exp_c = exp_sml;
    }
    else
    {
      exp_c = Foam::exp(alpha_eta_c);
    }

    S_e[cell1ID] = -i_ref*(exp_a-exp_c)*mesh.magSf()[faceID]/mesh.V()[cell1ID];
    S_ion[cell2ID] = i_ref*(exp_a-exp_c)*mesh.magSf()[faceID]/mesh.V()[cell2ID]; 

    {
      scalar a_eta = alpha_a*eta;
      scalar c_eta = alpha_c*eta;
      if(a_eta > exponent_limit)
      {
        a_eta = exponent_limit;
      }
      else if(a_eta < -exponent_limit)
      {
        a_eta = -exponent_limit;
      }

      if (c_eta > exponent_limit)
      {
        c_eta = exponent_limit;
      }
      else if (c_eta < -exponent_limit)
      {
        c_eta = -exponent_limit;
      }
     
      dS_e[cell1ID] = -(alpha_a*Foam::exp(a_eta)-alpha_c*Foam::exp(c_eta))*i_ref*mesh.magSf()[faceID]/mesh.V()[cell1ID];
      dS_ion[cell2ID] = -(alpha_a*Foam::exp(a_eta)-alpha_c*Foam::exp(c_eta))*i_ref*mesh.magSf()[faceID]/mesh.V()[cell2ID];
    }
}




