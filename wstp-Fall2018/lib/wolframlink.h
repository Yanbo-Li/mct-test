#ifndef WOLFRAMLINK_H
#define WOLFRAMLINK_H


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "wstp.h"

class WolframLink
{
public:
    WolframLink();
    ~WolframLink();

    // PUT FUNCTIONS
    bool putInteger(int x);
    bool putString(const char *s);
    bool putIntegerList(int *l, int n);
    bool putDouble(double x);
    bool putRealList(double *l, int n);
    bool putFunction(const char *s, int n);
    bool putSymbol(const char *s);

    // GET FUNCTIONS
    bool getInteger(int &input);
    bool getDouble(double &input);
    bool getString(std::string &input);
    bool getIntegerList(std::vector<int> &input);
    bool getRealList(std::vector<double> &input);
    bool getReal2DArray(std::vector<std::vector<double> > &input);
    bool getSymbol(std::string &input);

    // HELPER FUNCTIONS
    bool waitForReturnPacket();
    bool clearLinkError();
    bool loadPackage(const char *package);
    bool setupPackages(std::vector<const char*> packages);
    bool getGraph(const char* getFunction);
    bool reconnectLink();

    // TEST FUNCTIONS
    void testInteger();
    void testDouble();
    void testString();
    void testAddIntegers();

private:
    WSENV mEnv;
    WSLINK mLink;
    int mError;
    bool mLinkError;
};

#endif // WOLFRAMLINK_H
