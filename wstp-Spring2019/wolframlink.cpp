#include "wolframlink.h"
#include "wstp.h"
#include <iostream>
#include <vector>

using namespace std;

WolframLink::WolframLink()
{
    mLinkError = false;

    mEnv = WSInitialize(nullptr);
    if(mEnv == static_cast<WSENV>(nullptr)) cerr << "unable to initialize environment" << endl;

    mLink = WSOpenString(mEnv, "-linkmode launch -linkname '/Applications/Mathematica.app/Contents/MacOS/MathKernel -mathlink'", &mError);

    if(mLink == static_cast<WSLINK>(nullptr) || mError != WSEOK) cerr << "unable to create mLink\n";

    int stat = 0;   // status returned by mathlink function, 0 means mError
    if(!mLinkError) stat = WSActivate(mLink);

    if(stat == 0) cerr << "cannot activate mLink with MLActivate" << endl;
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

bool WolframLink::getString(string &input) {
    const char *string;
    if(mLinkError) return false;
    if(WSGetString(mLink, &string) == 0) return false;
    input = std::string(string);
    WSReleaseString(mLink, string);
    return true;
}

bool WolframLink::getIntegerList(vector<int> &input) {
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

bool WolframLink::getRealList(vector<double> &input) {
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

bool WolframLink::getReal2DArray(vector<pair<double, double>> &input) {
    char **heads;
    double *data;
    int *dims;
    int depth;
    if (mLinkError) return false;
    if (WSGetReal64Array(mLink, &data, &dims, &heads, &depth) == 0) {
        cout << "did not retrieve array from mathematica" << endl;
        return false;
    }
    if(depth == 2 && dims[1] == 2) {
        input.resize(static_cast<size_t>(dims[0]));
        int curr = 0;
        for(size_t i = 0; i < static_cast<size_t>(dims[0]); i++) {
            input[i].first = data[curr];
            input[i].second = data[curr + 1];
            curr += 2;
        }
        WSReleaseReal64Array(mLink, data, dims, heads, depth);
        return true;
    }
    WSReleaseReal64Array(mLink, data, dims, heads, depth);
    cout << "retrieved array not depth not 2 or of pairs of 2" << endl;
    return false;
}

bool WolframLink::getSymbol(string &input) {
    const char *symbol;
    if(mLinkError) return false;
    if(WSGetSymbol(mLink, &symbol) == 0) return false;
    input = string(symbol);
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
    string s;
    if(putFunction("EvaluatePacket", 1) && putFunction("Needs", 1) && putString(pkg) && waitForReturnPacket() && getSymbol(s))
        return true;
    return false;
}

bool WolframLink::setupPackages(vector<const char*> packages) {
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

void WolframLink::createBode(std::vector<double> numerator, std::vector<double> denominator) {

    WSPutFunction(mLink, "EvaluatePacket", 1);
    WSPutFunction(mLink, "TFRecord`recordBodeTMP", 2);
    std::cout << "TFRecord`recordBode" << std::endl;

    double* l1 = &numerator[0];
    double* l2 = &denominator[0];

    std::cout << "size of numerator: " << numerator.size() << std::endl;
    std::cout << "size of denominator: " << denominator.size() << std::endl;

    putRealList(l1, (int)numerator.size());
    putRealList(l2, (int)denominator.size());

    sentPacketWaitForReturnPacket();
    std::cout << "received return packet" << std::endl;

    const char *s = nullptr;
    string ss(s);
    getSymbol(ss);
    s = ss.c_str();

    if (s == nullptr)
    {
        std::cout << "loadPackage returned s = NULL\n";
    }
    else
    {
        if (strcmp(s, "Null") != 0)
            std::cout << "loadPackage returned s != 'Null'\n";
    }
    releaseSymbol(s);
}

void WolframLink::releaseSymbol(const char *s)
{
    if(mLinkError) return;
    if(s != nullptr) WSReleaseSymbol(mLink, s);
}

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

void WolframLink::sentPacketWaitForReturnPacket()
{
    if(mLinkError)
        return;

    if(WSEndPacket(mLink) == 0)
    {
        setFunctionError("sentPacketWaitForReturnPacket WSEndPacket");
        return;
    }

    // flush before asking ready
    if(WSFlush(mLink) == 0) { setFunctionError("sentPacketWaitForReturnPacket WSFlush"); return;}

    // wait for data to appear on the link
    while(!mLinkError && WSReady(mLink) == 0)
    {
        //std::cout << "mLinkError = " << mLinkError << ", WSReady(link) = " << WSReady(link) << "\n";
        if(WSError(mLink) != WSEOK)
        {
            setFunctionError("sentPacketWaitForReturnPacket WSReady");
            return;
        }
    }

    // keep reading until return packet is found
    // ??? discard all packets until return packet is found ???
    // ??? check for MessagePacket ???
    int p = 0;
    while(!mLinkError && (p = WSNextPacket(mLink)) && p != RETURNPKT)
    {
        // setError instead of setFunctionError
        if(WSNewPacket(mLink) == 0) { setFunctionError("sentPacketWaitForReturnPacket WSNewPacket"); return;}
    }

    // final error check
    if(WSError(mLink) != WSEOK) setFunctionError("sentPacketWaitForReturnPacket final error check");
}

void WolframLink::getRealArray(double*& data, int*& dims, int& depth) {
    char **heads;
    /* stores the rank of the array */
    if (mLinkError) return;

    if (!WSGetReal64Array(mLink, &data, &dims, &heads, &depth)) {
        std::cout << "Failed to get array" << std::endl;
        std::cout << "WSError: " << WSErrorMessage(mLink) << std::endl;
    }
    else {

    }

    if (mLinkError) return;
    if (data != nullptr && dims != nullptr && heads != nullptr && depth > 0) WSReleaseReal64Array(mLink, data, dims, heads, depth);
}

Plot WolframLink::getFreq() {
    WSPutFunction(mLink, "EvaluatePacket", 1);
    WSPutFunction(mLink, "TFRecord`getFreq", 0);

    sentPacketWaitForReturnPacket();
    std::cout << std::endl << "received return packet" << std::endl;

    double* data = nullptr;
    int* dims = nullptr;
    int depth = 0;

    getRealArray(data, dims, depth);

    int total = 1;
    for (int i = 0; i < depth; i++) {
        total *= dims[i];
    }
    std::cout << "total: " << total << std::endl;
    std::cout << data[0] << std::endl;

    for (int i = 0; i < total; i++) {
        std::cout << data[i] << " ";
    }

    Plot returnPlot;

    for (int i = 0; i < total; i += 2) {
        returnPlot.x.push_back(data[i]);
        returnPlot.y.push_back(data[i + 1]);
    }

    return returnPlot;
}

Plot WolframLink::getPhase() {
    WSPutFunction(mLink, "EvaluatePacket", 1);
    WSPutFunction(mLink, "TFRecord`getPhase", 0);

    sentPacketWaitForReturnPacket();
    std::cout << std::endl << "received return packet" << std::endl;

    double* data = nullptr;
    int* dims = nullptr;
    int depth = 0;

    getRealArray(data, dims, depth);

    int total = 1;
    for (int i = 0; i < depth; i++) {
        total *= dims[i];
    }
    std::cout << "total: " << total << std::endl;
    std::cout << data[0] << std::endl;

    for (int i = 0; i < total; i++) {
        std::cout << data[i] << " ";
    }

    Plot returnPlot;

    for (int i = 0; i < total; i += 2) {
        returnPlot.x.push_back(data[i]);
        returnPlot.y.push_back(data[i + 1]);
    }

    return returnPlot;
}



//***************END OF HELPER FUNCTIONS***************

//***************TEST FUNCTIONS***************
void WolframLink::testInteger() {
    cout << "Testing Put and Get Integer" << endl;
    int x = 10;
    int y = -1;
    if(putInteger(x) && waitForReturnPacket() && getInteger(y))
        cout << "Sent: " << x << endl << "Received: " << y << endl;
    else
        cout << "Communication Failed" << endl;
    cout << endl;
}

void WolframLink::testDouble() {
    cout << "Testing Put and Get Double" << endl;
    double x = 2.2;
    double y = -1;
    if(putDouble(x) && waitForReturnPacket() && getDouble(y))
        cout << "Sent: " << x << endl << "Received: " << y << endl;
    else
        cout << "Communication Failed" << endl;
    cout << endl;
}

void WolframLink::testString() {
    cout << "Testing Put and Get String" << endl;
    const char *x = "abcd";
    string y;
    if(putString(x) && waitForReturnPacket() && getString(y))
        cout << "Sent: " << x << endl << "Received: " << y << endl;
    else
        cout << "Communication Failed" << endl;
    cout << endl;
}

void WolframLink::testAddIntegers() {
    cout << "Testing Adding Two Integers" << endl;
    int a = 2;
    int b = 3;
    int c = -1;
    if(putFunction("Plus", 2) && putInteger(a) && putInteger(b) && waitForReturnPacket() && getInteger(c))
        cout << "a: " << a << endl << "b: " << b << endl << "result: " << c << endl;
    else
        cout << "Communication Failed" << endl;
    cout << endl;
}

void WolframLink::setFunctionError(const char *sfunction)
{
    if(!mLinkError)
    {
        mLinkError = true;
        //NSLog("Error: function %s message %s", sfunction, WSErrorMessage(link));
    }

    // clear error and reactivate link, if possible
    if(WSClearError(mLink) == 0) setFunctionError("MLClearError cannot reactivate mathKernel link");
}

