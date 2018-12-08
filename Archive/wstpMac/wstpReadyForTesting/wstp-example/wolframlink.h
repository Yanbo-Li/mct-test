#ifndef WOLFRAMLINK_H
#define WOLFRAMLINK_H


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "wstp.h"

class Plot {
public:
	std::vector<double> x, y;
};

class WolframLink
{
public:
    WolframLink();
    ~WolframLink();
void putInteger(int x);
	int getInteger();
	void addIntegers(int a, int b);

	void putString(const char *s);
	void getString(const char **ps);
	void releaseString(const char *s);

	void putIntegerList(int *l, int n);
	//void getIntegerList(int **pl, int *pn);
	void releaseIntegerList(int *l, int n);

	void   putDouble(double x);
	double getDouble();

	void   putRealList(double *l, int n);
	void   getRealList(double **pl, int pn);
	void   releaseRealList(double *l, int n);
	void getRealArray(double*& data, int*& dims, int& depth);

	void List(int **pl, int *pn);
	void putFunction(const char *s, int n);

	void sentPacketWaitForReturnPacket();
	void setFunctionError(const char *sfunction);

	void loadPackage(const char *spackage);

	void putSymbol(const char *s);
	void getSymbol(const char **ps);
	void releaseSymbol(const char *s);

	void reverseIntList(int *l, int n);
	//void tfTest(int *l, int n);
	void testTFRecord();
	//void testArray();
	//void testGlobal();

	//void setUpPlots();
	//Plots getPlots(std::vector<double> numerator, std::vector<double> denominator);

	void setupPackages();
	void createBode(std::vector<double> numerator, std::vector<double> denominator);


	Plot getFreq();
	Plot getPhase();


private:
    WSENV env;
    WSLINK link;
    int error;
    bool linkError;
};

#endif // WOLFRAMLINK_H
