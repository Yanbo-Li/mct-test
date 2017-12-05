#include "wstp.h"
#include "wolframlink.h"
#include <iostream>


int main(int argc, char **argv)
{
    WolframLink w;

    //Test integer
    int x = 1;
    w.putInteger(x);
    w.sentPacketWaitForReturnPacket();
    w.getInteger();

    //Test integer list
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9} ;
    int* result;
    int size = sizeof(arr)/sizeof(int);

    // Test the custom package for reversing and int list
    const char* c = "researchPkg`listOperation`";
    w.loadPackage(c);
    std::cout << "loading researchPkg\n";
    w.reverseIntList(arr, size);

    //Test double
    double d = 2.2;
    w.putDouble(d);
    w.sentPacketWaitForReturnPacket();
    w.getDouble();

    //Test string
    const char *y = "abcd";
    const char **z;
    w.putString(y);
    w.sentPacketWaitForReturnPacket();
    w.getString(z);

    //Add integers
    w.addIntegers(1,2);
    w.sentPacketWaitForReturnPacket();
    w.getInteger();

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



    delete [] realArr;

    return 0;
}
