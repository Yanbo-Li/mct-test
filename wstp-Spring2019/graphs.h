#ifndef GRAPHS_H
#define GRAPHS_H

#include "wolframlink.h"
#include <vector>
#include <iostream>

/* The Graphs class is a wrapper for a Wolfram Link.
 * We use the Link to iterface with Mathematica, providing the correct
 * function names from the packages and data structures to capture data.
 *
 * TODO:
 * We still need to do error handling. As in, what happens if the
 * link encounters an error where it cannot retrieve data, or
 * if the link dies or becomes corrupted.
 *
 * We also have not implemented sendClick()
 */

class Graphs {
public:
    Graphs();
    bool compute(std::vector<double> num, std::vector<double> denom);
    bool sendClick(); //TODO

    //***************Get FUNCTIONS***************
    const std::vector<std::pair<double, double>>& getGain(){return mGain;}
    const std::vector<std::pair<double, double>>& getPhase(){return mPhase;}
    const std::vector<std::vector<std::pair<double, double>>>& getRootLocus(){return mRootLocus;}
    const std::vector<std::pair<double, double>>& getStepResponse(){return mStepResponse;}

    //***************Get FUNCTIONS***************
    WolframLink* getLink();
    static void print(std::vector<std::pair<double, double>> input);

private:
    bool computePlot(const char *function, std::vector<double> num, std::vector<double> denom);
    bool retrievePoints(const char *function, std::vector<std::pair<double, double>>& populate, int branchNum = -1);
    bool retrieveDouble(const char *function, double& populate);

    WolframLink *mWolframLink;
    std::vector<std::pair<double, double>> mGain;
    std::vector<std::pair<double, double>> mPhase;
    std::vector<std::vector<std::pair<double, double>>> mRootLocus;
    std::vector<std::pair<double, double>> mStepResponse;
    std::vector<double> originalNum;
    std::vector<double> originalDenom;
};

#endif // GRAPHS_H
