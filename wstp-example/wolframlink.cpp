#include "wolframlink.h"
#include "wstp.h"
#include <iostream>


WolframLink::WolframLink()
{
    linkError = false;


    env = WSInitialize((WSEnvironmentParameter)0);
    if(env == (WSENV)0)
    {
        std::cout << "unable to initialize environment\n";
    }

    link = WSOpenString(env, "-linkmode launch -linkname '/Applications/Mathematica.app/Contents/MacOS/MathKernel -mathlink'", &error);

    if(link == (WSLINK) 0 || error != WSEOK)
    {
        std::cout << "unable to create link\n";
    }

    int stat = 0;   // status returned by mathlink function, 0 means error
    if(!linkError)
        stat = WSActivate(link);

    if(stat == 0)
        std::cout << "cannot activate link with MLActivate";
}

WolframLink::~WolframLink()
{
    WSClose(link);
    WSDeinitialize(env);
}

void WolframLink::putInteger(int x)
{
    if(linkError)
        return;

    if (!WSPutInteger(link, x)){
        std::cout << "Unable to put integer " << x << "\n";
    }
    else{
        std::cout << "Put integer " << x << "\n";
    }
    WSEndPacket(link);
}

int WolframLink::getInteger()
{
    if(linkError)
        return 0;

    int x;
    int packet;

    //while ((packet = WSNextPacket(link)) && packet != RETURNPKT)
      //      WSNewPacket(link);

    if (!WSGetInteger(link, &x)){
        std::cout << "Failed to get int\n";
    }
    else{
        std::cout << "Get integer " << x << "\n";
    }
    return x;
}

void WolframLink::addIntegers(int a, int b)
{
    std::cout << "Add integers " << a << " + " << b << "\n";
    WSPutFunction(link, "Plus", 2);
    WSPutInteger(link, a);
    WSPutInteger(link, b);
    //WSEndPacket(link);
}

void WolframLink::putIntegerList(int *l, int n) // array int* l with length int n
{
    if(linkError) return;
    if(!WSPutInteger32List(link, l, n)) {
        std::cout << "Unable to put integer list " << l << "\n";
    }
    else{
        std::cout << "Put integer list: ";
        for (int i = 0; i < n; i++)
        {
            std::cout << l[i] << " ";
            if (i == n - 1)
                std::cout << "\n";
        }
    }
    WSEndPacket(link);
}

void WolframLink::List(int **pl, int *pn) // store result in int** pl with length int* n
{
    // allocates memory for pl data, requires releaseInteger32List(....) to free memory
    if(linkError)
        return;

    //int *arr;
    int packet;

    //while ((packet = WSNextPacket(link)) && packet != RETURNPKT)
      //      WSNewPacket(link);

    if(! WSGetInteger32List(link, pl, pn)) {
        std::cout << "Failed to get integer list\n";
    }
    else{
        std::cout << "Get integer list: ";
        for (int i = 0; i < *pn; i++)
        {
            std::cout << (*pl)[i] << " ";
            if (i == (*pn) - 1)
                std::cout << "\n";
        }
        releaseIntegerList(*pl, *pn);
    }
}

void WolframLink::releaseIntegerList(int *l, int n)
{
    if(linkError) return;
    if(l != NULL && n > 0) WSReleaseInteger32List(link, l, n);
}

void WolframLink::putFunction(const char *s, int n)
{
    if(linkError) return;
    if(WSPutFunction(link, s, n) == 0) setFunctionError("WSPutFunction");
}


void WolframLink::putString(const char *s)
{
    if(linkError) return;
    if(!WSPutString(link, s)) {
        std::cout << "Unable to put string " << s << "\n";
    }
    else{
        std::cout << "Put string: " << s << "\n";
    }
    //WSEndPacket(link);
}

void WolframLink::getString(const char **ps)
{
    if(linkError) return;

    const char *s;
    // const char *packet;
    int packet;

    //while ((packet = WSNextPacket(link)) && packet != RETURNPKT)
      //      WSNewPacket(link);

    if(!WSGetString(link, &s)) {
        std::cout << "Failed to get string" << "\n";
    }
    else{
        std::cout << "Get string: ";

        for (size_t i = 0; i < strlen(s); i++)
        {
            std::cout << s[i];
            if (i == strlen(s) - 1)
                std::cout << "\n";
        }
        //WSReleaseString(link, s);
        releaseString(s);

        // Save the pointer
        ps = &s;
    }
}

void WolframLink::releaseString(const char *s)
{
    if(linkError) return;

    if(s == NULL) {
        std::cout << "Failed to release string" << "\n";
    }
    else{
        WSReleaseString(link, s);
    }
}


void WolframLink::putDouble(double x)
{
    if(linkError) return;
    if(!WSPutDouble(link, x)) {
        std::cout << "Unable to put double " << x << "\n";
    }
    else{
        std::cout << "Put double " << x << "\n";
    }
    //WSEndPacket(link);
}

double WolframLink::getDouble()
{
    if(linkError) return 0.0;
    double d;
    double packet;

    //while ((packet = WSNextPacket(link)) && packet != RETURNPKT)
      //      WSNewPacket(link);

    if(!WSGetDouble(link, &d)) {
        std::cout << "Failed to get int\n";
    }
    else{
        std::cout << "Get double " << d << "\n";
    }
    return d;
}

void WolframLink::putRealList(double *l, int n)
{
    if(linkError) return;
    if(!WSPutReal64List(link, l, n)) {
        std::cout << "Unable to put RealList " << l << "\n";
    }
    else{
        std::cout << "Put real list: ";
        for (int i = 0; i < n; i++)
        {
            std::cout << l[i] << " ";
            if (i == n - 1)
                std::cout << "\n";
        }
    }
    //WSEndPacket(link);
}

void WolframLink::getRealList(double **pl, int pn)
{
    // allocates memory for pl data, requires releaseRealList(....) to free memory
    if(linkError) return;

    double packet;

    //while ((packet = WSNextPacket(link)) && packet != RETURNPKT)
      //      WSNewPacket(link);

    if(!(WSGetReal64List(link, pl, &pn))){
        std::cout << "Failed to get int\n";
    }
    else{
        std::cout << "Get Real List: ";
        for (int i = 0; i < pn; i++)
        {
            //std::cout << "Loop " << i << std::endl;
            std::cout << (*pl)[i] << " ";
            if (i == (pn) - 1)
                std::cout << "\n";
        }
    }

    releaseRealList(*pl, pn);
}
/*
{
    // allocates memory for pl data, requires releaseInteger32List(....) to free memory
    if(linkError) return;

    //int *arr;
    int packet;

    while ((packet = WSNextPacket(link)) && packet != RETURNPKT)
            WSNewPacket(link);

    if(!WSGetInteger32List(link, pl, pn)) {
        std::cout << "Failed to get integer list\n";
    }
    else{
        std::cout << "Get integer list: ";
        for (int i = 0; i < *pn; i++)
        {
            std::cout << (*pl)[i] << " ";
            if (i == (*pn) - 1)
                std::cout << "\n";
        }
        releaseIntegerList(*pl, *pn);
    }
}
*/
void WolframLink::releaseRealList(double *l, int n)
{
    if(linkError) return;
    if(l != NULL && n > 0) WSReleaseReal64List(link, l, n);
}

void WolframLink::sentPacketWaitForReturnPacket()
{
    if(linkError)
        return;

    if(WSEndPacket(link) == 0)
    {
        setFunctionError("sentPacketWaitForReturnPacket WSEndPacket");
        return;
    }

    // flush before asking ready
    if(WSFlush(link) == 0) { setFunctionError("sentPacketWaitForReturnPacket WSFlush"); return;}

    // wait for data to appear on the link
    while(!linkError && WSReady(link) == 0)
    {
        //std::cout << "linkError = " << linkError << ", WSReady(link) = " << WSReady(link) << "\n";
        if(WSError(link) != WSEOK)
        {
            setFunctionError("sentPacketWaitForReturnPacket WSReady");
            return;
        }
    }

    // keep reading until return packet is found
    // ??? discard all packets until return packet is found ???
    // ??? check for MessagePacket ???
    int p = 0;
    while(!linkError && (p = WSNextPacket(link)) && p != RETURNPKT)
    {
        // setError instead of setFunctionError
        if(WSNewPacket(link) == 0) { setFunctionError("sentPacketWaitForReturnPacket WSNewPacket"); return;}
    }

    // final error check
    if(WSError(link) != WSEOK) setFunctionError("sentPacketWaitForReturnPacket final error check");
}

void WolframLink::setFunctionError(const char *sfunction)
{
    if(!linkError)
    {
        linkError = true;
        //NSLog("Error: function %s message %s", sfunction, WSErrorMessage(link));
    }

    // clear error and reactivate link, if possible
    if(WSClearError(link) == 0) setFunctionError("MLClearError cannot reactivate mathKernel link");
}

void WolframLink::putSymbol(const char *s)
{
    if(linkError) return;
    if(WSPutSymbol(link, s) == 0) setFunctionError("MLPutSymbol");
}

void WolframLink::getSymbol(const char **ps)
{
    if(linkError) return;
    if(WSGetSymbol(link, ps) == 0) setFunctionError("MLGetSymbol");
}

void WolframLink::releaseSymbol(const char *s)
{
    if(linkError) return;
    if(s != NULL) WSReleaseSymbol(link, s);
}

void WolframLink::loadPackage(const char *spackage)
{
    putFunction("EvaluatePacket",1);
    putFunction("Needs",1);
    putString(spackage);
    sentPacketWaitForReturnPacket();

    const char *s = NULL;
    getSymbol(&s);

    if(s == NULL)
    {
        std::cout << "loadPackage returned s = NULL\n";
    }
    else
    {
        if(strcmp(s, "Null") != 0)
            std::cout << "loadPackage returned s != 'Null'\n";
    }
    releaseSymbol(s);
}


void WolframLink::reverseIntList(int *l, int n) // array int* l with length int n
{
    std::cout << "Reverse integer list " << "\n";

    // Call the function and put in the list
    WSPutFunction(link, "EvaluatePacket", 1);
    WSPutFunction(link, "listOperation`switchLastAndFirstNumerator", 1);
    WSPutFunction(link, "List", n);
    // putIntegerList(l, n);
    for (int i = 0; i < n; i++)
    {
        WSPutInteger(link, l[i]);
        std::cout << "Put integer " << l[i] << "\n";
    }

    // Ending the packet by brute force
    //WSEndPacket(link);
    sentPacketWaitForReturnPacket();
        // Want to end with sentPacketWaitForReturnPacket()
        // However it's getting stuck on while-loop
        // while(!linkError && WSReady(link) == 0)
        // This needs further investigation
        // The goal is to replace WSEndPacket() with sentPacketWaitForReturnPacket()

    std::cout << "Reading the reversed int list\n";
    int* result;

    List(&result, &n);
    std::cout << "Done listing integers. Now sent packet wait for return\n";

}

