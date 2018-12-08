(* ::Package:: *)

(* ::Input::Initialization:: *)
(*
  Gerald Aguilar 
01-27-2018
MCT: Transfer Function Package
*)


(* ::Input::Initialization:: *)
(* Initialize the Package *) 
BeginPackage["PackageDev`TFRecord`",{"PackageDev`TFBode`","PackageDev`TFCheck`","PackageDev`TFRoot`","PackageDev`TFStep`"}];


(* ::Input::Initialization:: *)
(*  *) 
Begin["`Private`"];


(* ::Input::Initialization:: *)
(*Create bode freq record function*)
TFRecord`recordBode[recordNum_,recordDen_]:= Module[{dataRecord,transferFunctionList,transferFunctionFormat,transferFunctionData},transferFunctionList=TFCheck`tfBuild[recordNum,recordDen];transferFunctionFormat = TFBode`tfModel[TFCheck`tf[transferFunctionList]];transferFunctionData = TFBode`bodeData[transferFunctionFormat];Global`recordTotal=transferFunctionData ;Flatten[Global`recordTotal]]


(* ::Input::Initialization:: *)
TFRecord`getBode[]:=Global`recordTotal


(* ::Input::Initialization:: *)
TFRecord`getGain[]:=Global`recordTotal[[1]]


(* ::Input::Initialization:: *)
TFRecord`getPhase[]:=Global`recordTotal[[2]]


(* ::Input::Initialization:: *)
TFRecord`recordBodeTMP[recordNum_,recordDen_]:= Module[{dataRecord,transferFunctionList,transferFunctionFormat,transferFunctionData},transferFunctionList=TFCheck`tfBuild[recordNum,recordDen];transferFunctionFormat = TFBode`tfModel[TFCheck`tf[transferFunctionList]];transferFunctionData = TFBode`bodeData[transferFunctionFormat];Global`recordTotal=transferFunctionData ; Null]


(* ::Input::Initialization:: *)
(*Create a root locus function*)
TFRecord`recordRoot[recordRootNum_,recordRootDen_,rangeroot1_:0,rangeroot2_:1000]:= Module[{rootPlotHolder},Global`rootPlotHolder = TFRoot`tfRootBuild[recordRootNum,recordRootDen,rangeroot1,rangeroot2];Global`rootPlotHolder]


(* ::Input::Initialization:: *)
(*Create a root locus function with NULL return *)
TFRecord`recordRootTMP[recordRootNum_,recordRootDen_,rangeroot1_:0,rangeroot2_:1000]:= Module[{rootPlotHolder},Global`rootPlotHolder = TFRoot`tfRootBuild[recordRootNum,recordRootDen,rangeroot1,rangeroot2];Null]


(* ::Input::Initialization:: *)
TFRecord`getRoot[]:=Global`rootPlotHolder


(* ::Input::Initialization:: *)
TFRecord`getNumBranches[]:=Module[{root},root=TFRecord`getRoot[];Global`numBranches=Dimensions[root][[1]]
]


(* ::Input::Initialization:: *)
TFRecord`getBranch[num_Integer:1]:=Flatten[Global`rootPlotHolder[[num]],1]


(* ::Input::Initialization:: *)
(*Create a step function*)
TFRecord`recordStep[recordRootNum_,recordRootDen_,rangeroot1_:0,rangeroot2_:15]:= Module[{holder},Global`stepPlotHolder = TFStep`tfStepBuild[recordRootNum,recordRootDen,rangeroot1,rangeroot2];Global`stepPlotHolder]


(* ::Input::Initialization:: *)
(*Create a step function*)
TFRecord`recordStepTMP[recordRootNum_,recordRootDen_,rangeroot1_:0,rangeroot2_:15]:= Module[{holder},Global`stepPlotHolder = TFStep`tfStepBuild[recordRootNum,recordRootDen,rangeroot1,rangeroot2];Null]


(* ::Input::Initialization:: *)
TFRecord`getStep[]:=Flatten[Global`stepPlotHolder,1]


(* ::Input::Initialization:: *)
(*  *)
TFRecord`recordDataList[recordBodeData_,recordRootData_,recordStepData_]:= Module[{bodePhaseList,bodeFreqList,rootList,stepList},bodePhaseList = recordBodeData[[2]];bodeFreqList = recordBodeData[[1]];rootList = Flatten[recordRootData,2];stepList = Flatten[recordStepData,1];Flatten[{bodeFreqList,bodePhaseList,rootList,stepList},1]]


(* ::Input::Initialization:: *)
(*  *)
TFRecord`recordKeyBode[recordBodeData_]:= Module[{bodeKey,bodeFreqKey,bodePhaseKey},bodeFreqKey = Length[recordBodeData[[1]]];bodePhaseKey = Length[recordBodeData[[2]]];{bodeFreqKey,bodePhaseKey}]


(* ::Input::Initialization:: *)
(*  *)
TFRecord`recordKeyRoot[recordRootData_]:= Module[{rootKey},rootKey = Table[Length[recordRootData[[i]]],{i,1,Length[recordRootData]}];rootKey]


(* ::Input::Initialization:: *)
(*  *)
TFRecord`recordKeyStep[recordStepData_]:= Module[{stepKey},stepKey = Flatten[recordStepData,1];{Length[stepKey]}]


(* ::Input::Initialization:: *)
(*  *) 
End[];


(* ::Input::Initialization:: *)
(*end of package*)
EndPackage[];
