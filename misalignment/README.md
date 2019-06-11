# Misalignment study

The effect of misalignment on the distribution of residuals obtained from reconstructed angles through a simulation is demonstrated.

For that, CSV output file (x0; y1; x2; y3) from the previous simulation (**correctSim**) were re-used and *amplitudeCalculator.cpp* was adapted to take into account the displacement of the detectors.

## Help 
 
 Usage of *amplitudeCalculator.cpp* :
 
 ```
 g++ amplitudeCalculator.cpp -o amplitudeCalculator
 ./amplitudeCalculator -w w file 
 ```
 
where  w : Gap between detectors.

