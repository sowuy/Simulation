# Simulation
Objectif : C++ script for cosmic muon simulation through a small gRPC-based muon telescope

## 1) CorrectSim : 

To compile the project, simply do :

```
make
```

Setup : 4 layers of mini-gRPC (XY & XY) are placed horizontally one on top of another with or without space (parameters) between them and record muon hits.
The RPC is a gaseous detector used in CMS for muon detection and in muography for imaging purposes. Each layer contains 16 strips as readout. Muons are generated following a cos^2(theta) distribution where theta is the azimutal incidence angle of muons on Earth. The goal is to store the strip in which they pass and then the final distribution. In this version of the code, there is a free parameter that is left to vary: inclination angle of the telescope.

As it is now you simply need to launch the executable file to start the simulation for this given setup:

```
bin/Cosmics Hoffset_low Hoffset_high
```

