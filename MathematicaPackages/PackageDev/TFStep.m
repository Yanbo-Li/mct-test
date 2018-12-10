(* ::Package:: *)

(* ::Input::Initialization:: *)
(*
  Gerald Aguilar 
04-01-2018
MCT: Transfer Function Package
*)


(* ::Input::Initialization:: *)
(* Initialize the Package *) 
BeginPackage["PackageDev`TFStep`",{"PackageDev`TFCheck`","PackageDev`TFRoot`"}];


(* ::Input::Initialization:: *)
(* Usage Messages *)


(* ::Input::Initialization:: *)
(*Create a function to format the given transfer function in the Matlab standard convention*)
TFStep`tfStepBuild[userStepNumerator_,userStepDenominator_,steprange1_,steprange2_]:= Module[{tfStep,tfStepModel,stepPlotHandle,rootAdjustedData,sTFStepBuild,tTFStepBuild,stepOutputResponse},sTFStepBuild = Symbol["s"];tTFStepBuild = Symbol["t"];tfStep = TransferFunctionModel[(TFCheck`tf[TFCheck`tfBuild[userStepNumerator,userStepDenominator]]),sTFStepBuild];stepOutputResponse = OutputResponse[tfStep,UnitStep[tTFStepBuild],tTFStepBuild];stepPlotHandle = Plot[stepOutputResponse,{tT,steprange1,steprange2}//.tT-> tTFStepBuild,PlotRange->All];Flatten[TFRoot`rootDataExtract[stepPlotHandle],1]]


(* ::Input::Initialization:: *)
(*end of package*)
EndPackage[];
