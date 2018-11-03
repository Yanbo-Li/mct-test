#include "lib/graphs.h"
#include <vector>

using namespace std;

Graphs::Graphs() {
    std::vector<const char*> packages ={
        "PackageDev`TFBode`",
        "PackageDev`TFCheck`",
        "PackageDev`TFRoot`"
        "PackageDev`TFStep`",
        "PackageDev`TFRecord`",
        "PackageDev`userClickProcess`",
        "PackageDev`controllerBuild`"
    };

    if(!mWolframLink.setupPackages(packages))
        cout << "packaged failed to load packages" << endl;
}

bool Graphs::compute(std::vector<double> num, std::vector<double> denom) {

    //***************Bode Plot***************
    if(!computePlot("TFRecord`recordBodeTMP", num, denom)) {
        cout << "Bode failed to create" << endl;
        return false;
    }

    if(!retrievePoints("TFRecord`getFreq", mFreq)) {
        cout << "retrieving Frequency failed" << endl;
        return false;
    }

    if(!retrievePoints("TFRecord`getPhase", mPhase)) {
        cout << "retrieving Phase failed" << endl;
        return false;
    }

    //***************Root Locus***************
    if(!computePlot("TFRecord`recordRootTMP", num, denom)) {
        cout << "Root Locus failed to create" << endl;
        return false;
    }

    //Retrieve Root Locus
    if(!retrievePoints("TFRecord`getRoot", mRootLocus)) {
        cout << "retrieving Root Locus failed" << endl;
        return false;
    }

    //***************Step Response***************
    if(!computePlot("TFRecord`recordStepTMP", num, denom)) {
        cout << "Step Response failed to create" << endl;
        return false;
    }

    //Retrieve Step Response
    if(!retrievePoints("TFRecord`getRoot", mStepResponse)) {
        cout << "retrieving Step Response failed" << endl;
        return false;
    }

    return true;
}

bool Graphs::sendClick() {
    return false;
}

const vector<vector<double>>& Graphs::getPhase() {
    return mPhase;
}

const vector<vector<double>>& Graphs::getFreq() {
    return mFreq;
}

const vector<vector<double>>& Graphs::getRootLocus() {
    return mRootLocus;
}

const vector<vector<double>>& Graphs::getStepResponse() {
    return mStepResponse;
}

void Graphs::print(vector<vector<double>> input) {
    for ( std::vector<std::vector<int>>::size_type i = 0; i < input.size(); i++ ) {
       for ( std::vector<int>::size_type j = 0; j < input[i].size(); j++ ) {
           std::cout << input[i][j] << ' ';
       }
       std::cout << std::endl;
    }
}

bool Graphs::computePlot(const char *function, std::vector<double> num, std::vector<double> denom) {
    mWolframLink.putFunction("EvaluatePacket", 1);
    mWolframLink.putFunction(function, 2);
    std::string s;

    if(!mWolframLink.putRealList(&num[0], static_cast<int>(num.size()))) {
        cout << "put num failed" << endl;
        return false;
    }

    if(!mWolframLink.putRealList(&denom[0], static_cast<int>(denom.size()))) {
        cout << "put num failed" << endl;
        return false;
    }

    if( !(mWolframLink.waitForReturnPacket() && mWolframLink.getSymbol(s))) {
        cout << "error when computing: " << function << endl;
        return false;
    }

    return true;
}

bool Graphs::retrievePoints(const char *function, std::vector<std::vector<double>>& populate) {
    mWolframLink.putFunction("EvaluatePacket", 1);
    mWolframLink.putFunction(function, 0);
    if(!mWolframLink.waitForReturnPacket()) {
        cout << "error when receiving symbol" << endl;
        return false;
    }
    if(!mWolframLink.getReal2DArray(populate)) {
        cout << "error when receiving array: " << function << endl;
        return false;
    }
    return true;
}
