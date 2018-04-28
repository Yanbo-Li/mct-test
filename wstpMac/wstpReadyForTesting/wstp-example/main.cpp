#include "wstp.h"
#include "wolframlink.h"
#include <iostream>

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

int main(int argc, char **argv)
{
    WolframLink w;

	testPackages(w);
	
    return 0;
}
