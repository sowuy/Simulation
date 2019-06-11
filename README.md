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

## 2) Misalignment :

The effect of misalignment on the distribution of residuals obtained from reconstructed angles through a simulation is demonstrated.

For that, CSV output file (x0; y1; x2; y3) from the previous simulation (**correctSim**) were re-used and *amplitudeCalculator.cpp* was adapted to take into account the displacement of the detectors.

## Help 
 
 Usage of *amplitudeCalculator.cpp* :
 
 ```
 g++ amplitudeCalculator.cpp -o amplitudeCalculator
 ./amplitudeCalculator -w w file 
 ```
 
where  w : Gap between detectors.

## 3) Acceptance : 

Same as **correctSim** at first sight.. Need to be investigated.
Focus on acceptance not on cosmic muon distributions.
Output = CSVFile with hit strip number for each layer : **x0 y1 x2 y3**

## 4) Induced charge :

The following simulation has been made in order to calculate the signal expected in one of the
chambers built according to the Shockley-Ramo theorem
