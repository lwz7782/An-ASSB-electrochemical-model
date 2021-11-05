// solve electric potential

fvScalarMatrix phi_e_Eqn
(
  fvm::laplacian(sigma_e,phi_e) + (S_e - dS_e*phi_e) + fvm::Sp(dS_e,phi_e)
);

phi_e_Eqn.relax();
fvOptions.constrain(phi_e_Eqn);
phi_e_Eqn.solve();
fvOptions.correct(phi_e);

Info << "phi_e min mean max = "
         << Foam::gMin(phi_e) << " , "
         << phi_e.weightedAverage(mesh.V()).value() << " , "
         << Foam::gMax(phi_e)
         << nl <<endl;
