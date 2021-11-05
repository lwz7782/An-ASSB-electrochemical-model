// solve electric potential

fvScalarMatrix C_Li_Eqn
(
  fvm::ddt(C_Li) == fvm::laplacian(D_Li,C_Li) + S_Li
);

C_Li_Eqn.relax();
fvOptions.constrain(C_Li_Eqn);
C_Li_Eqn.solve();
fvOptions.correct(C_Li);

Info << "C_Li min mean max = "
         << Foam::gMin(C_Li) << " , "
         << C_Li.weightedAverage(mesh.V()).value() << " , "
         << Foam::gMax(C_Li)
         << nl <<endl;
