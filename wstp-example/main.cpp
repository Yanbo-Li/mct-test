#include "wstp.h"
#include "wolframlink.h"
#include <iostream>


int main(int argc, char **argv)
{

    WolframLink w;

    //Test integer
    int x = 1;
    w.putInteger(x);
    w.getInteger();

    //Test integer list
    int arr[] = {0, 1, 2, 3} ;
    int* result;
    int size = sizeof(arr)/sizeof(int);
    w.putIntegerList(arr, size);
    w.List(&result, &size);

    //Test double
    double d = 2.2;
    w.putDouble(d);
    w.getDouble();

    //Test string
    const char *y = "abcd";
    const char **z;
    w.putString(y);
    w.getString(z);

    //Test real list
    // Unclear why initializing the double array causes program to crash
//    double realArr[] = {0.2, 1.3, 2.5, 3.7, 4.2};
//    double* realResult;
//    int realSize = sizeof(realArr)/sizeof(double);
//    w.putRealList(realArr, realSize);
//    w.getRealList(&realResult, &realSize);

    //Add integers
    w.addIntegers(1,2);
    w.getInteger();


    return 0;
}

/*
static void init_and_openlink( int argc, char* argv[]);
static void error( WSLINK link);


WSENV env = (WSENV)0;
WSLINK link = (WSLINK)0;


int main(int argc, char* argv[])
{
    int pkt, n, prime, expt;
    int len, lenp, k;

    init_and_openlink( argc, argv);

    printf( "Integer to factor: ");

#if defined(_MSC_VER) && (_MSC_VER >= 1400)
    scanf_s( "%d", &n);
#else
    scanf( "%d", &n);
#endif

    WSPutFunction( link, "Evaluatenvacket", 1L);
        WSPutFunction( link, "FactorInteger", 1L);
            WSPutInteger( link, n);
    WSEndPacket( link);

    while( (pkt = WSNextPacket( link), pkt) && pkt != RETURNPKT) {
        WSNewPacket( link);
        if (WSError( link)) error( link);
    }

    if ( ! WSTestHead( link, "List", &len)) error(link);
    for (k = 1; k <= len; k++) {
        if (WSTestHead( link, "List", &lenp)
        &&  lenp == 2
        &&  WSGetInteger( link, &prime)
        &&  WSGetInteger( link, &expt)
        ){
            printf( "%d ^ %d\n", prime, expt);
        }else{
            error( link);
        }
    }

    WSPutFunction( link, "Exit", 0);

    return 0;
}


static void error( WSLINK link)
{
    if( WSError( link)){
        fprintf( stderr, "Error detected by WSTP: %s.\n",
            WSErrorMessage(link));
    }else{
        fprintf( stderr, "Error detected by this program.\n");
    }
    exit(3);
}


static void deinit( void)
{
    if( env) WSDeinitialize( env);
}


static void closelink( void)
{
    if( link) WSClose( link);
}


static void init_and_openlink( int argc, char* argv[])
{
    int err;

    env =  WSInitialize( (WSParametersPointer)0);
    if( env == (WSENV)0) exit(1);
    atexit( deinit);

    link = WSOpenArgv( env, argv, argv + argc, &err);
    if(link == (WSLINK)0) exit(2);
    atexit( closelink);
}
*/
