// solve ion potential

fvScalarMatrix phi_ion_Eqn
(
  fvm::laplacian(sigma_ion,phi_ion) + (S_ion - dS_ion*phi_ion) + fvm::Sp(dS_ion,phi_ion) //+ S_ion_mig
);

phi_ion_Eqn.relax();
fvOptions.constrain(phi_ion_Eqn);
phi_ion_Eqn.solve();
fvOptions.correct(phi_ion);

Info << "phi_ion min mean max = "
         << Foam::gMin(phi_ion) << " , "
         << phi_ion.weightedAverage(mesh.V()).value() << " , "
         << Foam::gMax(phi_ion)
         << nl <<endl;
