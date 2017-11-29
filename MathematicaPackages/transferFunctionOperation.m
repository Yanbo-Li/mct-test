(* ::Package:: *)

BeginPackage["researchPkg`transferFunctionOperation`"];

transferFunctionOperation`switchLastAndFirstNumerator::usage="[numerators_List]";

Begin["`Private`"];

transferFunctionOperation`switchLastAndFirstNumerator[numerator_List]:=Module[{numeratorList,editedNumeratorList},numeratorList=numerator[[5]];editedNumeratorList=numeratorList/.{a_,b___,c_}-> {c,b,a};
Global`record=numerator/.numerator[[5]]->editedNumeratorList;];

End[];

EndPackage[];


