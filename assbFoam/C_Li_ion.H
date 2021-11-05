// solve electric potential

fvScalarMatrix C_Li_ion_Eqn
(
  fvm::ddt(C_Li_ion) == fvm::laplacian(D_Li_ion,C_Li_ion) + S_ionize + S_Li_ion
);

C_Li_ion_Eqn.relax();
fvOptions.constrain(C_Li_ion_Eqn);
C_Li_ion_Eqn.solve();
fvOptions.correct(C_Li_ion);

Info << "C_Li_ion min mean max = "
         << Foam::gMin(C_Li_ion) << " , "
         << C_Li_ion.weightedAverage(mesh.V()).value() << " , "
         << Foam::gMax(C_Li_ion)
         << nl <<endl;
