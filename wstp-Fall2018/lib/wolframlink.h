#ifndef WOLFRAMLINK_H
#define WOLFRAMLINK_H


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "wstp.h"

/* The WolframLink provides the connection to Mathematic using wstp.
 * The code is divided into 4 sections:
 * Put functions send data to Mathematica
 * Get functions receive data from Mathematica
 * Helper functions are used throughout other code
 * Test functions were preliminary functions to test the link
 *
 * TODO:
 * Make clearLinkError() and reconnectLink() work
 * These functions would be used in graphs.cpp to restablish a working link.
 */

class WolframLink
{
public:
    WolframLink();
    ~WolframLink();

    //***************PUT FUNCTIONS***************
    bool putInteger(int x);
    bool putString(const char *s);
    bool putIntegerList(int *l, int n);
    bool putDouble(double x);
    bool putRealList(double *l, int n);
    bool putFunction(const char *s, int n);
    bool putSymbol(const char *s);

    //***************GET FUNCTIONS***************
    bool getInteger(int &input);
    bool getDouble(double &input);
    bool getString(std::string &input);
    bool getIntegerList(std::vector<int> &input);
    bool getRealList(std::vector<double> &input);
    bool getReal2DArray(std::vector<std::pair<double,double>> &input);
    bool getSymbol(std::string &input);

    //***************HELPER FUNCTIONS***************
    bool waitForReturnPacket();
    bool clearLinkError(); //TODO
    bool loadPackage(const char *package);
    bool setupPackages(std::vector<const char*> packages);
    bool getGraph(const char* getFunction);
    bool reconnectLink(); //TODO

    //***************TEST FUNCTIONS***************
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
