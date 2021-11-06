# An-ASSB-electrochemical-model
A 3D layer electrochemical model of all-solid-state battery made by Weizhuo Li, Qing Du, and Kui Jiao, Tianjin University, China

The model computational domain includes negative current collector, negative electrode, solid electrolyte, positive electrode, and positive current collector. 

The governing equations include intercalation lithium conservation, lithium-ion conservation, electronic charge, ionic charge, and interface electrochemical reactions.

This solver comprises a main file and nine inclusion files for clarity of model architecture. The functions of nine inclusion files are scalar or vector fields creation, physical field initialization, lithium-ion species fields calculation, intercalated lithium-ion conservation equation, lithium-ion conservation equation, potential fields calculation, electron conservation equation, ion conservation equation, and termination condition in sequence, respectively.
