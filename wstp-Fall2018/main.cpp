#include "lib/wstp.h"
#include "lib/wolframlink.h"
#include "lib/graphs.h"
#include <iostream>
#include <vector>

using namespace std;


int main()
{
    Graphs graph;

    std::vector<double> num = {1, 2};
    std::vector<double> denom = {1, 2, 3};

    if(!graph.compute(num, denom))
        cout << "error" << endl;

    Graphs::print(graph.getFreq());

    return 0;
}
