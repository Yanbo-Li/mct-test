#ifndef GRAPHS_H
#define GRAPHS_H

#include "wolframlink.h"
#include <vector>

class Graphs {
public:
    Graphs();
    bool compute(std::vector<double> num, std::vector<double> denom);
    bool sendClick();

    const std::vector<std::vector<double>>& getPhase();
    const std::vector<std::vector<double>>& getFreq();
    const std::vector<std::vector<double>>& getRootLocus();
    const std::vector<std::vector<double>>& getStepResponse();

    static void print(std::vector<std::vector<double>> input);

private:
    bool computePlot(const char *function, std::vector<double> num, std::vector<double> denom);
    bool retrievePoints(const char *function, std::vector<std::vector<double>>& populate);

    WolframLink mWolframLink;
    std::vector<std::vector<double>> mPhase;
    std::vector<std::vector<double>> mFreq;
    std::vector<std::vector<double>> mRootLocus;
    std::vector<std::vector<double>> mStepResponse;
    std::vector<double> originalNum;
    std::vector<double> originalDenom;
};

#endif // GRAPHS_H
