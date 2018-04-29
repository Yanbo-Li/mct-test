(* ::Package:: *)

(* ::Input::Initialization:: *)
(*
  Gerald Aguilar 
04-01-2018
MCT: Transfer Function Package
*)


(* ::Input::Initialization:: *)
(* Initialize the Package *) 
BeginPackage["PackageDev`TFRoot`",{"PackageDev`TFCheck`"}];


(* ::Input::Initialization:: *)
(* Usage Messages *)


(* ::Input::Initialization:: *)
(*Create a function to format the RootLocus Data*)
TFRoot`rootDataExtract[rootPlotHandle_]:= Module[{rootAdjustmentRule,aA,xX,yY,bB,finalRootData,allPlotRootData,xTFRoot,t},xTFRoot=Symbol["x"];allPlotRootData =Cases[rootPlotHandle[[1,1,1]],Line[t__]->t,\[Infinity]];finalRootData =  Table[Partition[allPlotRootData[[i]],2],{i,1,Length[allPlotRootData]}];finalRootData]


(* ::Input::Initialization:: *)
(*Create a function to format the given transfer function in the Matlab standard convention*)
TFRoot`tfRootBuild[userRootNumerator_,userRootDenominator_,rootrange1_,rootrange2_]:= Module[{tfRoot,kK,matlabTF,tfRootModel,rootPlotHandle,rootAdjustedData,sTFRootBuild,finalDataRoot},sTFRootBuild = Symbol["s"];tfRoot = (kK*TFCheck`tf[TFCheck`tfBuild[userRootNumerator,userRootDenominator]]);matlabTF = (tfRoot)/(1 + ((kK - 1)*tfRoot));tfRootModel = TransferFunctionModel[matlabTF,sTFRootBuild];rootPlotHandle = RootLocusPlot[tfRootModel,{kK,rootrange1,rootrange2}];TFRoot`rootDataExtract[rootPlotHandle]]


(* ::Input::Initialization:: *)
(*end of package*)
EndPackage[];
