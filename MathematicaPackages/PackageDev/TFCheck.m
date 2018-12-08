(* ::Package:: *)

(* ::Input::Initialization:: *)
(*
  Gerald Aguilar 
01-27-2018
MCT: Transfer Function Package
*)


(* ::Input::Initialization:: *)
(* Initialize the Package *) 
BeginPackage["PackageDev`TFCheck`"];


(* ::Input::Initialization:: *)
(* Usage Messages *)
TFCheck`numerator::usage = "Forms numerator with given a list of numbers";


(* ::Input::Initialization:: *)
(* ASK PROF: CK's package had private functions, however functions like 'Numerator' are functions the user interacts with directly. So was it 'wrong' to have a `Private` context? *)


(* ::Input::Initialization:: *)
(* Building sub-functions to be used in the final function *)


(* ::Input::Initialization:: *)
(*Numerator Function*)
TFCheck`numerator[userNumList_List]:= Module[{length,laplaceVars,numTerms,numEquation,sTFCheck},sTFCheck = Symbol["s"];length = Length[userNumList];laplaceVars=Reverse[Table[sTFCheck^i,{i,0,length-1,1}]];numTerms=userNumList*laplaceVars; numEquation=Total[numTerms]];


(* ::Input::Initialization:: *)
(* Denomninator Function *)
TFCheck`denominator[userDenList_List] := Module[{length,laplaceVars,denTerms,denEquation,sTFCheck},sTFCheck = Symbol["s"];length=Length[userDenList];
laplaceVars=Reverse[Table[sTFCheck^i,{i,0,length-1,1}]];denTerms=userDenList*laplaceVars;denEquation=Total[denTerms]];


(* ::Input::Initialization:: *)
(* Formation of the transfer function...might not need it *)
(*Question: Does it matter that the polynomials get ordered from least to greatest?...could use TraditionalForm but that may cause issues*)
TFCheck`tf[{userNumList_,userDenList_}] :=Module[{numEquation,denEquation,tFun}, numEquation= TFCheck`numerator[userNumList];
denEquation=TFCheck`denominator[userDenList];
tFun=numEquation/denEquation;tFun];


(* ::Input::Initialization:: *)
(* Long div. function *)
TFCheck`longDiv[numTF_List,denTF_List]:=Module[{newPoly,newDen,newNum,sTFCheck},sTFCheck = Symbol["s"];newPoly=PolynomialQuotientRemainder[TFCheck`numerator[numTF],TFCheck`numerator[denTF],sTFCheck];
newNum=Reverse[CoefficientList[newPoly[[1]],sTFCheck]];
newDen=Reverse[CoefficientList[newPoly[[2]],sTFCheck]];{newNum,newDen}];


(* ::Input::Initialization:: *)
(* Get the info from the user and store it in to the context available variable 'user' *)
TFCheck`tfBuild[firstList_List,secondList_List] :=Module[{userInput,numPower,denPower},userInput = {firstList,secondList};numPower = Length[userInput[[1]]];denPower = Length[userInput[[2]]];Which[(denPower>numPower),{userInput[[1]],userInput[[2]]},(denPower < numPower),Append[TFCheck`longDiv[userInput[[1]],userInput[[2]]],userInput[[2]]],(denPower == numPower),Append[TFCheck`longDiv[userInput[[1]],userInput[[2]]],userInput[[2]]]]];


(* ::Input::Initialization:: *)
EndPackage[];
