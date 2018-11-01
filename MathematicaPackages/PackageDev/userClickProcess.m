(* ::Package:: *)

(*Something*)
BeginPackage["userClickProcess`"]


(*This function builds a pole table for an input transfer function*)
(*Input: 
	1)Transfer Function which must contain "k"
	2)kmin,kmax and kstep(kstep is the step size of k*)
(*Output:
	1)A table of pole value in the following format
	{k_1,{pole1,pole2,pole3.......poleN},
	.....
	k_n,{pole1,pole2,pole3.......poleN}}*)
userClickProcess`poleTable[tfFunction_,kmin_,kmax_,kstep_]:=Module[{poleTable},
poleTable=Table[{i,TransferFunctionPoles[(tfFunction/.{k->i})][[1,1]]},{i,kmin,kmax,kstep}]]




(*This function calculates k and its location in pole table*)
(*Input: 
	1)a pole table built by userClickProcess`poleTable
	2)kmin,kmax and kstep(kstep is the step size of k*)
(*Output:
	1)a list:{position,k_value}
	*position is the the position of user click in the pole table 
	*)
userClickProcess`kcalculation[poletable_,userClick_,kmin_,kmax_,kstep_]:=
Module[{allPoles,click,k,position,result},
allPoles = Flatten[poletable];click=Nearest[allPoles,userClick];
position=Position[poletable,click[[1]]][[1,1]];
k=(position-1)*kstep+kmin;
result={position,k}
]


EndPackage[];
