#include "lib/wolframlink.h"
#include "lib/wstp.h"
#include <iostream>
#include <vector>

WolframLink::WolframLink()
{
    mLinkError = false;

    mEnv = WSInitialize(nullptr);
    if(mEnv == static_cast<WSENV>(0)) std::cerr << "unable to initialize environment" << std::endl;

    mLink = WSOpenString(mEnv, "-linkmode launch -linkname '/Applications/Mathematica.app/Contents/MacOS/MathKernel -mathlink'", &mError);

    if(mLink == static_cast<WSLINK>(0) || mError != WSEOK) std::cerr << "unable to create mLink\n";

    int stat = 0;   // status returned by mathlink function, 0 means mError
    if(!mLinkError) stat = WSActivate(mLink);

    if(stat == 0) std::cerr << "cannot activate mLink with MLActivate" << std::endl;
}

WolframLink::~WolframLink() {
    WSClose(mLink);
    WSDeinitialize(mEnv);
}

//***************PUT FUNCTIONS***************

bool WolframLink::putInteger(int x) {
    if(mLinkError) return false;
    if (WSPutInteger(mLink, x) == 0) return false;
    return true;
}

bool WolframLink::putIntegerList(int *l, int n) {
    if(mLinkError) return false;
    if(WSPutInteger32List(mLink, l, n) == 0) return false;
    return true;
}

bool WolframLink::putFunction(const char *s, int n) {
    if(mLinkError) return false;
    if(WSPutFunction(mLink, s, n) == 0) return false;
    return true;
}

bool WolframLink::putString(const char *s) {
    if(mLinkError) return false;
    if(WSPutString(mLink, s) == 0) return false;
    return true;
}

bool WolframLink::putDouble(double x) {
    if(mLinkError) return false;
    if(WSPutDouble(mLink, x) == 0) return false;
    return true;
}

bool WolframLink::putRealList(double *l, int n) {
    if(mLinkError) return false;
    if(WSPutReal64List(mLink, l, n) == 0) return false;
    return true;
}

bool WolframLink::putSymbol(const char *s) {
    if(mLinkError) return false;
    if(WSPutSymbol(mLink, s) == 0) return false;
    return true;
}

//***************END OF PUT FUNCTIONS***************

//***************GET FUNCTIONS***************

bool WolframLink::getInteger(int &outputInt) {
    if(mLinkError) return false;
    if (WSGetInteger(mLink, &outputInt) == 0) return false;
    return true;
}

bool WolframLink::getDouble(double &outputDouble) {
    if(mLinkError) return false;
    if(WSGetDouble(mLink, &outputDouble) ==  0) return false;
    return true;
}

bool WolframLink::getString(std::string &input) {
    const char *string;
    if(mLinkError) return false;
    if(WSGetString(mLink, &string) == 0) return false;
    input = std::string(string);
    WSReleaseString(mLink, string);
    return true;
}

bool WolframLink::getIntegerList(std::vector<int> &input) {
    int *outputArray;
    int numElements;
    if(mLinkError) return false;
    if(WSGetInteger32List(mLink, &outputArray, &numElements) == 0) return false;
    input.resize(static_cast<size_t>(numElements));
    for(size_t i = 0; i < static_cast<size_t>(numElements); i++)
        input[i] = outputArray[i];
    WSReleaseInteger32List(mLink, outputArray, numElements);
    return true;
}

bool WolframLink::getRealList(std::vector<double> &input) {
    double *outputArray;
    int numElements;
    if(mLinkError) return false;
    if(WSGetReal64List(mLink, &outputArray, &numElements) == 0) return false;
    input.resize(static_cast<size_t>(numElements));
    for(size_t i = 0; i < static_cast<size_t>(numElements); i++)
        input[i] = outputArray[i];
    WSReleaseReal64List(mLink, outputArray, numElements);
    return true;
}

bool WolframLink::getReal2DArray(std::vector<std::vector<double> > &input) {
    char **heads;
    double *data;
    int *dims;
    int depth;
    if (mLinkError) return false;
    if (WSGetReal64Array(mLink, &data, &dims, &heads, &depth) == 0) return false;
    if(depth == 2) {
        input.resize(static_cast<size_t>(dims[0]));
        for (size_t i = 0; i < static_cast<size_t>(dims[0]); i++)
            input[i].resize(static_cast<size_t>(dims[1]));
        int curr = 0;
        for(size_t i = 0; i < static_cast<size_t>(dims[0]); i++)
            for(size_t j = 0; j < static_cast<size_t>(dims[1]); j++) {
                input[i][j] = data[curr];
                curr++;
            }
        WSReleaseReal64Array(mLink, data, dims, heads, depth);
        return true;
    }
    WSReleaseReal64Array(mLink, data, dims, heads, depth);
    return false;
}

bool WolframLink::getSymbol(std::string &input) {
    const char *symbol;
    if(mLinkError) return false;
    if(WSGetSymbol(mLink, &symbol) == 0) return false;
    input = std::string(symbol);
    WSReleaseSymbol(mLink, symbol);
    return true;
}

//***************END OF GET FUNCTIONS***************

//***************HELPER FUNCTIONS***************

bool WolframLink::waitForReturnPacket() {
    if(mLinkError) return false;
    if(WSEndPacket(mLink) == 0) return false;
    if(WSFlush(mLink) == 0) return false;
    while(!mLinkError && WSReady(mLink) == 0)
        if(WSError(mLink) != WSEOK) return false;
    int p = 0;
    while(!mLinkError && (p = WSNextPacket(mLink)) && p != RETURNPKT)
        if(WSNewPacket(mLink) == 0) return false;
    if(WSError(mLink) != WSEOK) return false;
    return true;
}

bool WolframLink::loadPackage(const char *pkg) {
    std::string s;
    if(putFunction("EvaluatePacket", 1) && putFunction("Needs", 1) && putString(pkg) && waitForReturnPacket() && getSymbol(s))
        return true;
    return false;
}

bool WolframLink::setupPackages(std::vector<const char*> packages) {
    for(const char* pkg: packages)
        if(!loadPackage(pkg)) return false;
    return true;
}

bool WolframLink::clearLinkError() {
    if(!mLinkError) mLinkError = true;
    if(WSClearError(mLink) == 0) return false;
    return true;
}

/*
WSClearError does the following:
1. Actiavtes a previously unactivated link
2. Returns 0 for certain catastrophic errors like WSDEAD. Indicates link closed unexpectedly
3. Returns nonzero value for successful completion

Things to consider:
1. What should happen if a non catastrophic error occurs? (errors like running out of memory 
or failure to accept the socket connection)
2. Returning false in put functions means link error occured.
*/

bool WolframLink::reconnectLink() {
    /* There actually was an mError */
    if (mLinkError) {
        int errorCode = WSClearError(mLink);
        if (errorCode != 0)
        {
            // Successful completion of WSClearError
        } else {
            // Catastrophic error like WSDEAD.
            // Indicates link has closed unexpectedly
        }
    }
    return false;
}

//***************END OF HELPER FUNCTIONS***************

//***************TEST FUNCTIONS***************
void WolframLink::testInteger() {
    std::cout << "Testing Put and Get Integer" << std::endl;
    int x = 10;
    int y = -1;
    if(putInteger(x) && waitForReturnPacket() && getInteger(y))
        std::cout << "Sent: " << x << std::endl << "Received: " << y << std::endl;
    else
        std::cout << "Communication Failed" << std::endl;
    std::cout << std::endl;
}

void WolframLink::testDouble() {
    std::cout << "Testing Put and Get Double" << std::endl;
    double x = 2.2;
    double y = -1;
    if(putDouble(x) && waitForReturnPacket() && getDouble(y))
        std::cout << "Sent: " << x << std::endl << "Received: " << y << std::endl;
    else
        std::cout << "Communication Failed" << std::endl;
    std::cout << std::endl;
}

void WolframLink::testString() {
    std::cout << "Testing Put and Get String" << std::endl;
    const char *x = "abcd";
    std::string y;
    if(putString(x) && waitForReturnPacket() && getString(y))
        std::cout << "Sent: " << x << std::endl << "Received: " << y << std::endl;
    else
        std::cout << "Communication Failed" << std::endl;
    std::cout << std::endl;
}

void WolframLink::testAddIntegers() {
    std::cout << "Testing Adding Two Integers" << std::endl;
    int a = 2;
    int b = 3;
    int c = -1;
    if(putFunction("Plus", 2) && putInteger(a) && putInteger(b) && waitForReturnPacket() && getInteger(c))
        std::cout << "a: " << a << std::endl << "b: " << b << std::endl << "result: " << c << std::endl;
    else
        std::cout << "Communication Failed" << std::endl;
    std::cout << std::endl;
}
