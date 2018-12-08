(* ::Package:: *)

(* ::Input::Initialization:: *)
(*
  Gerald Aguilar 
01-27-2018
MCT: Bode Plot Package
*)


(* ::Input::Initialization:: *)
(* Initialize the Package *)
BeginPackage["PackageDev`TFBode`"];


(* ::Input::Initialization:: *)
(*Note that  is taking the num and den only... so if theres a remainder its gonna break/not be included*)
TFBode`tfModel[input_]:=Module[{plant,closedPlant,controller,systemTf,sTFBode},sTFBode=Symbol["s"];plant = TransferFunctionModel[input,sTFBode];plant];


(* ::Input::Initialization:: *)
(*Create the bode plot and extract the data set *)
(* HARD CODED THE DATA RANGE *)
(*might have issue with: Line[x__]\[Rule]x because of localization*)


(* ::Input::Initialization:: *)
TFBode`bodeData[input_]:=Module[{bodeplothandle1,freqplotdata,phaseplotdata,x,xadjustmentrule,a,y,b,freqdata,phasedata,freqAndPhaseData},bodeplothandle1 = BodePlot[input];freqplotdata =Flatten[Cases[bodeplothandle1[[1,1,1]],Line[x__]->x,\[Infinity]],1];phaseplotdata =Flatten[Cases[bodeplothandle1[[1,2,1]],Line[x__]->x,\[Infinity]],1];xadjustmentrule={a___,{x_,y_},b___}-> {a,10^x,y,b};freqdata = Partition[freqplotdata //.xadjustmentrule,2];phasedata = Partition[phaseplotdata //.xadjustmentrule,2];freqAndPhaseData = {freqdata,phasedata};freqAndPhaseData]


(* ::Input::Initialization:: *)
EndPackage[]
