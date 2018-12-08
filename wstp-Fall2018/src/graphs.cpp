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

    bool success = true;

    //***************Bode Plot***************
    if(!computePlot("TFRecord`recordBodeTMP", num, denom)) {
        cout << "Bode Plot failed to create" << endl;
        success = false;
    } else {
        if(!retrievePoints("TFRecord`getGain", mGain)) {
            cout << "Bode Plot failed to get Gain" << endl;
            success = false;
        }

        if(!retrievePoints("TFRecord`getPhase", mPhase)) {
            cout << "Bode Plot failed to get Phase" << endl;
            success = false;
        }
    }

    //***************Root Locus***************
    if(!computePlot("TFRecord`recordRootTMP", num, denom)) {
        cout << "Root Locus failed to create" << endl;
        success = false;
    } else {
        //Retrieve Number of Root Locus Branches
        double numBranches;
        if(!retrieveDouble("TFRecord`getNumBranches", numBranches)) {
            cout << "Root Locus failed to get numBranches" << endl;
            success = false;
        } else {
            //Populate Root Locus Branches
            mRootLocus.resize(static_cast<size_t>(numBranches));
            for(size_t i = 0; i < numBranches; i++) {
                if(!retrievePoints("TFRecord`getBranch", mRootLocus[i], static_cast<int>(i+1))) {
                    cout << "Root Locus failed to get branch " << i << endl;
                    success = false;
                }
            }
        }
    }

    //***************Step Response***************
    if(!computePlot("TFRecord`recordStepTMP", num, denom)) {
        cout << "Step Response failed to create" << endl;
        success = false;
    } else {
        //Retrieve Step Response
        if(!retrievePoints("TFRecord`getStep", mStepResponse)) {
            cout << "retrieving Step Response failed" << endl;
            success = false;
        }
    }

    return success;
}

bool Graphs::sendClick() {
    return false;
}

void Graphs::print(vector<pair<double, double>> input) {
    for (auto i : input) {
       cout << i.first << ' ' << i.second << endl;
    }
}

bool Graphs::computePlot(const char *function, std::vector<double> num, std::vector<double> denom) {
    mWolframLink.putFunction("EvaluatePacket", 1);
    mWolframLink.putFunction(function, 2);
    string s;

    if(!mWolframLink.putRealList(&num[0], static_cast<int>(num.size()))) {
        cout << "put numerator failed" << endl;
        return false;
    }

    if(!mWolframLink.putRealList(&denom[0], static_cast<int>(denom.size()))) {
        cout << "put denominator failed" << endl;
        return false;
    }

    if( !(mWolframLink.waitForReturnPacket() && mWolframLink.getSymbol(s))) {
        cout << "error when computing: " << function << endl;
        return false;
    }

    return true;
}

bool Graphs::retrievePoints(const char *function, std::vector<std::pair<double, double>>& populate, int branchNum) {
    mWolframLink.putFunction("EvaluatePacket", 1);

    if(branchNum == -1)
        mWolframLink.putFunction(function, 0);
    else{
        mWolframLink.putFunction(function, 1);
        mWolframLink.putInteger(branchNum);
    }

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

bool Graphs::retrieveDouble(const char* function, double &populate) {
    mWolframLink.putFunction("EvaluatePacket", 1);
    mWolframLink.putFunction(function, 0);
    if(!mWolframLink.waitForReturnPacket()) {
        cout << "error when receiving symbol" << endl;
        return false;
    }
    if(!mWolframLink.getDouble(populate)) {
        cout << "error when receiving double: " << function << endl;
        return false;
    }
    return true;
}
