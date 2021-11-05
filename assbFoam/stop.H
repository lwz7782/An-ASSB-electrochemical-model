label poswallID = mesh.boundaryMesh().findPatchID("wall-positive");
const polyPatch& poswall = mesh.boundaryMesh()[poswallID];
const surfaceScalarField& magSf = mesh.magSf();
scalar sumVoltage = 0;
scalar sumArea = 0;
scalar aveVoltage = 0;
forAll(poswall,faceI)
{ 
  scalar area = magSf.boundaryField()[poswallID][faceI];
  scalar voltage = phi_e.boundaryField()[poswallID][faceI];
  sumVoltage = sumVoltage + area*voltage;
  sumArea = sumArea + area;
}
aveVoltage = sumVoltage/sumArea;
if(aveVoltage < 3.0) break;
