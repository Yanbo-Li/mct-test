#include "wstp.h"
#include "wolframlink.h"
#include <iostream>
#include <vector>
void testPackage(WolframLink &w);
void testArray(WolframLink &w);
void testGlobalVar(WolframLink &w);
//void testPoints(WolframLink &w);
void testPackages(WolframLink &w);

int main(int argc, char **argv)
{
	WolframLink w;

	//testGlobalVar(w);

	//testPackage(w);
	//testArray(w);

	//testPoints(w);
	testPackages(w);

	/*std::cout << "created link, testing integer" << std::endl;

	//Test integer list
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int* result = NULL;
	int size = sizeof(arr) / sizeof(int);

	// Test the custom package for reversing and int list
	const char* c = "researchPkg`listOperation`";
	w.loadPackage(c);
	std::cout << "loading researchPkg\n";
	w.reverseIntList(arr, size);

	//Test integer
	int x = 1;
	w.putInteger(x);
	w.sentPacketWaitForReturnPacket();
	w.getInteger();


	//Test Add
	std::cout << "Testing add" << std::endl;
	w.addIntegers(1, 2);
	w.sentPacketWaitForReturnPacket();
	w.getInteger();

	//Test double
	std::cout << "testing double" << std::endl;
	double d = 2.2;
	w.putDouble(d);
	w.sentPacketWaitForReturnPacket();
	w.getDouble();

	
	//Test string
	std::cout << "testing string" << std::endl;
	const char *y = "abcd";
	const char **z = NULL;
	w.putString(y);
	w.sentPacketWaitForReturnPacket();
	w.getString(z);
	
	//Test real list
	double* realArr = new double[5];
	realArr[0] = 0.2;
	realArr[1] = 1.2;
	realArr[2] = 2.3;
	realArr[3] = 3.2;
	realArr[4] = 4.2;
	double* realResult;
	int realSize = 5;

	w.putRealList(realArr, realSize);
	w.sentPacketWaitForReturnPacket();
	w.getRealList(&realResult, realSize);

	delete[] realArr;

	
	
	

	std::cout << "waiting" << std::endl;*/

	Sleep(1000000);
	return 0;
}

void testArray(WolframLink &w) {
	const char* c = "researchPkg`TFArray`";

	w.loadPackage(c);

	w.testArray();
}

void testPackage(WolframLink &w) {
	const char* c1 = "PackageDev`TFCheck`";
	const char* c2 = "PackageDev`TFBode`";
	const char* c3 = "PackageDev`TFRecord`";

	w.loadPackage(c3);
	w.loadPackage(c1);
	w.loadPackage(c2);

	w.testTFRecord();
}

void testGlobalVar(WolframLink &w) {
	const char* c = "PackageDev`TFwithGLOBAL`";
	w.loadPackage(c);

	w.testGlobal();
}

/*void testPoints(WolframLink &w) {
	w.setUpPlots();

	double numerator[] = {1, 2};
	std::vector<double> num(numerator, numerator + sizeof(numerator) / sizeof(numerator[0]));

	double denominator[] = {1, 2, 3};
	std::vector<double> den(denominator, denominator + sizeof(denominator) / sizeof(denominator[0]));
	
	Plots p = w.getPlots(num, den);

	std::cout << "number of points in freq graph: " << p.freq.size() << std::endl;
	std::cout << "number of points in phase graph: " << p.phase.size() << std::endl;
}*/

void testPackages(WolframLink &w) {
	w.setupPackages();

	double numerator[] = { 1, 1 };
	std::vector<double> num(numerator, numerator + sizeof(numerator) / sizeof(numerator[0]));

	double denominator[] = { 1, 3, 12, -16 };
	std::vector<double> den(denominator, denominator + sizeof(denominator) / sizeof(denominator[0]));
	
	w.createBode(num, den);

	std::cout << std::endl << std::endl <<  "getFreq" << std::endl;
	w.getFreq();

	std::cout << std::endl << std::endl << "getPhase" << std::endl;
	w.getPhase();

}
