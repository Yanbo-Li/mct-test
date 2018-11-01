(* ::Package:: *)

 BeginPackage["controllerBuild`"];
 
 controllerBuild::usage = "controllerBuild function takes an ordered list of inputs: numRealPole_Integer,
  numComplexPole_Integer,numIntegrator_Integer, numRealZero_Integer, 
  the function will verify if the inputs are all nonnegative integers. 
  The default values for every input is zero. The default value for the output is 1. 
  The final output of the function will consist a transfer function with number of input components.";
 

controllerBuild`newController[numRealPole_Integer: 0, numComplexPole_Integer: 0, numIntegrator_Integer: 0, 
numRealZero_Integer: 0, numComplexZero_Integer: 0, numDifferentiator_Integer: 0] /; NonNegative[numRealPole] && 
NonNegative[numComplexPole] && NonNegative[numIntegrator] && NonNegative[numRealZero] &&
NonNegative[numComplexZero] && NonNegative[numDifferentiator] :=
 Module[{finalController = 1, nrp = numRealPole, ncp = numComplexPole, ni = numIntegrator, 
         nrz = numRealZero, ncz = numComplexZero, nd = numDifferentiator},
    finalController =finalController*1/(s+1)^nrp*2/(s^2+2s+2)^ncp*1/s^ni*(1 + s)^nrz/1*(s^2+2s+2)^ncz/1*s^nd/1;
    finalController];
EndPackage[];
