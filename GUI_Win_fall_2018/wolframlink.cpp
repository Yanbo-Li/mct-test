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

    char arg0[] = "-linklaunch";
    char arg1[] = "-linkname";
    char arg2[] = "C:\\Program Files\\Wolfram Research\\Mathematica\\11.2\\MathKernel.exe";

    char *argv[3];
    argv[0] = arg0;
    argv[1] = arg1;
    argv[2] = arg2;

    int argc = 3;

    link = WSOpenArgcArgv(env, argc, argv, &error);

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

}

int WolframLink::getInteger()
{
    if(linkError)
        return 0;

    int x;

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
}

void WolframLink::List(int **pl, int *pn) // store result in int** pl with length int* n
{
    // allocates memory for pl data, requires releaseInteger32List(....) to free memory
    if(linkError)
        return;

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
}

void WolframLink::getString(const char **ps)
{
    if(linkError) return;

    const char *s;

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
}

double WolframLink::getDouble()
{
    if(linkError) return 0.0;
    double d;

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
}

void WolframLink::getRealList(double **pl, int pn)
{
    // allocates memory for pl data, requires releaseRealList(....) to free memory
    if(linkError) return;

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
    //WSPutFunction(link, "List", n);
    putIntegerList(l, n);
//    for (int i = 0; i < n; i++)
//    {
//        WSPutInteger(link, l[i]);
//        std::cout << "Put integer " << l[i] << "\n";
//    }

    sentPacketWaitForReturnPacket();

    std::cout << "Reading the reversed int list\n";
    int* result;

    List(&result, &n);
    std::cout << "Done listing integers. Now sent packet wait for return\n";
}

/*void WolframLink::testingMulti(int *l, int n) { // array int* l with length int n
    std::cout << "Testing Multi Pkgs " << "\n";

    // Call the function and put in the list
    WSPutFunction(link, "EvaluatePacket", 1);
    WSPutFunction(link, "testMultiPkgs`multiplyNums", 1);
    //WSPutFunction(link, "List", n);

    putIntegerList(l, n);
    //    for (int i = 0; i < n; i++)
    //    {
    //        WSPutInteger(link, l[i]);
    //        std::cout << "Put integer " << l[i] << "\n";
    //    }
    sentPacketWaitForReturnPacket();

    std::cout << "Reading the list with last component is the product of the first and the last of original list \n";
    int* result;

    List(&result, &n);
    std::cout << "Done listing integers. Now sent packet wait for return\n";
}*/

//void WolframLink::testingArrays(int *l, int n) { // array int* l with length int n
//    std::cout << "Testing TFArray" << "\n";

//    // Call the function and put in the list
//    WSPutFunction(link, "EvaluatePacket", 1);
//    WSPutFunction(link, "TFRecord`listFun", 1);

//    //WSPutFunction(link, "List", n);

//    putIntegerList(l, n);
////    for (int i = 0; i < n; i++) {
////        WSPutInteger(link, l[i]);
////        std::cout << "Put integer " << l[i] << "\n";
////    }
//    sentPacketWaitForReturnPacket();

//    std::cout << "TFArray test \n";
//    int* result;

//    getRealArray(&result, &n);
//    std::cout << "Done listing integers. Now sent packet wait for return\n";
//}

//void WolframLink::getRealArray(int **pl, int *pn) {
//    double *data;
//    int *dims;
//    char **heads;
//    int d; /* stores the rank of the array */
//    if (linkError) return;

//    if (!WSGetReal64Array(link, &data, &dims, &heads, &d)) {
//        std::cout << "Failed to get array" << std::endl;
//        std::cout << "WSError: " << WSErrorMessage(link) << std::endl;
//    }
//    else {
//        std::cout << "Received array with depth: " << d << std::endl;
//        int total = 1;
//        for (int i = 0; i < d; i++) {
//            std::cout << "dimention " << i << ": " << dims[i] << std::endl;
//            total *= dims[i];
//        }
//        std::cout << "total size is: " << total << std::endl;
//        for (int i = 0; i < total; i++) {
//            std::cout << data[i] << " ";
//        }
//        std::cout << std::endl;
//    }
//}

void WolframLink::getRealArray(double*& data, int*& dims, int& depth) {
	char **heads;
	/* stores the rank of the array */
	if (linkError) return;

	if (!WSGetReal64Array(link, &data, &dims, &heads, &depth)) {
		std::cout << "Failed to get array" << std::endl;
		std::cout << "WSError: " << WSErrorMessage(link) << std::endl;
	}
	else {
		
	}

	if (linkError) return;
	if (data != NULL && dims != NULL && heads != NULL && depth > 0) WSReleaseReal64Array(link, data, dims, heads, depth);
}

void WolframLink::testTFRecord() {
    WSPutFunction(link, "EvaluatePacket", 1);
    WSPutFunction(link, "TFRecord`globalListTest", 2);
    std::cout << "TFRecord`globalListTest" << std::endl;

    double* l1 = new double[1];
    l1[0] = 1;

    double* l2 = new double[2];
    l2[0] = 1;
    l2[1] = 2;

    std::cout << "Putting List of 1" << std::endl;
    putRealList(l1, 1);

    std::cout << "Putting List of 2" << std::endl;
    putRealList(l2, 2);

    std::cout << "Waiting for return packet" << std::endl;
    sentPacketWaitForReturnPacket();

    std::cout << "reading returned list" << std::endl;

    double* data = NULL;
    int* dims = NULL;
    int depth = 0;

    getRealArray(data, dims, depth);

    std::cout << "Received array with depth: " << depth << std::endl;
    int total = 1;
    for (int i = 0; i < depth; i++) {
        std::cout << "dimention " << i << ": " << dims[i] << std::endl;
        total *= dims[i];
    }
    std::cout << "total size is: " << total << std::endl;
    for (int i = 0; i < total; i++) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;

    // test second function
    WSPutFunction(link, "EvaluatePacket", 1);
    WSPutFunction(link, "TFRecord`recordPhaseBode", 2);
    std::cout << "TFRecord`recordPhaseBode" << std::endl;

    std::cout << "Putting List of 1" << std::endl;
    putRealList(l1, 1);

    std::cout << "Putting List of 2" << std::endl;
    putRealList(l2, 2);

    std::cout << "Waiting for return packet" << std::endl;
    sentPacketWaitForReturnPacket();

    std::cout << "reading returned list" << std::endl;

    getRealArray(data, dims, depth);

    std::cout << "Received array with depth: " << depth << std::endl;
    total = 1;
    for (int i = 0; i < depth; i++) {
        std::cout << "dimention " << i << ": " << dims[i] << std::endl;
        total *= dims[i];
    }
    std::cout << "total size is: " << total << std::endl;
    for (int i = 0; i < total; i++) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

void WolframLink::setupPackages() {
	/*putFunction("EvaluatePacket", 1);
	putFunction("Clear", 1); //trying Get instead of Needs
	putString("Global`.");
	sentPacketWaitForReturnPacket();

	const char *s = NULL;
	getSymbol(&s);

	if (s == NULL)
	{
		std::cout << "Clearing global returned s = NULL\n";
	}
	else
	{
		if (strcmp(s, "Null") != 0)
			std::cout << "Clearing global returned s != 'Null'\n";
	}
	releaseSymbol(s);*/

    const char* c1 = "TFCheck`";
	const char* c2 = "PackageDev`TFBode`";
	const char* c3 = "PackageDev`TFRoot`";
	const char* c4 = "PackageDev`TFRecord`";
	const char* c5 = "PackageDev`TFStep`";

	loadPackage(c1);
	loadPackage(c2);
	loadPackage(c3);
	loadPackage(c4);
	loadPackage(c5);
}

void WolframLink::createBode(std::vector<double> numerator, std::vector<double> denominator) {
	
	WSPutFunction(link, "EvaluatePacket", 1);
	WSPutFunction(link, "TFRecord`recordBodeTMP", 2);
	std::cout << "TFRecord`recordBode" << std::endl;

    double *l1 = &numerator[0];
    double *l2 = &denominator[0];

	std::cout << "size of numerator: " << numerator.size() << std::endl;
	std::cout << "size of denominator: " << denominator.size() << std::endl;

	putRealList(l1, (int)numerator.size());
	putRealList(l2, (int)denominator.size());

	sentPacketWaitForReturnPacket();
	std::cout << "received return packet" << std::endl;

	const char *s = NULL;
	getSymbol(&s);

	if (s == NULL)
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

Plot WolframLink::getFreq() {
    WSFlush(link);
	WSPutFunction(link, "EvaluatePacket", 1);
	WSPutFunction(link, "TFRecord`getFreq", 0);

	sentPacketWaitForReturnPacket();
	std::cout << std::endl << "received return packet" << std::endl;

	double* data = NULL;
	int* dims = NULL;
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

    WSFlush(link);
	WSPutFunction(link, "EvaluatePacket", 1);
	WSPutFunction(link, "TFRecord`getPhase", 0);

	sentPacketWaitForReturnPacket();
	std::cout << std::endl << "received return packet" << std::endl;

	double* data = NULL;
	int* dims = NULL;
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
