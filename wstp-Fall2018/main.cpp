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

    cout << "**********Gain Coordinates**********" << endl;
    Graphs::print(graph.getGain());

    cout << "**********Phase Coordinates**********" << endl;
    Graphs::print(graph.getPhase());

    cout << "**********Root Locus Coordinates**********" << endl;
    for(size_t i = 0; i < graph.getRootLocus().size(); i++) {
        Graphs::print(graph.getRootLocus()[i]);
    }

    cout << "**********Step Response Coordinates**********" << endl;
    Graphs::print(graph.getStepResponse());

    return 0;
}
