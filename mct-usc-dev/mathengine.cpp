#include "mathengine.h"
#include "wstp.h"
#define PRECISIONCONST 4

MathEngine::MathEngine()
{

}

MathEngine::~MathEngine()
{
    delete d;
    delete bw;
}

void MathEngine::setWindowPtrs(Dialog* d, BodePlotWindow* bw)
{
    this->d = d;
    this->bw = bw;
}

Dialog* MathEngine::getDialogPtr()
{
    return d;
}

BodePlotWindow* MathEngine::getBpwPtr()
{
    return bw;
}

void MathEngine::setTf(std::vector<float> num, std::vector<float> denom)
{
    numVector = num;
    denomVector = denom;

    numString.clear();
    denomString.clear();

    for (size_t i = 0; i < numVector.size(); i++)
    {
        int s = numVector.size() - 1 - i;

        // Formatting s
        if (s == 0)
        {
            numString += to_string_with_precision(numVector[i], PRECISIONCONST) + " + ";
        }
        else if (s == 1)
        {
            numString += to_string_with_precision(numVector[i], PRECISIONCONST) + "s" + " + ";
        }
        else
        {
            numString += to_string_with_precision(numVector[i], PRECISIONCONST) + "s^" + std::to_string(s) + " + ";
        }

        // Delete final +
        if (i == numVector.size() - 1)
        {
            numString.resize(numString.size() - 3);
        }
    }

    for (size_t i = 0; i < denomVector.size(); i++)
    {
        int s = denomVector.size() - 1 - i;
        // Formatting s
        if (s == 0)
        {
            denomString += to_string_with_precision(denomVector[i], PRECISIONCONST) + " + ";
        }
        else if (s == 1)
        {
            denomString += to_string_with_precision(denomVector[i], PRECISIONCONST) + "s" + " + ";
        }
        else
        {
            denomString += to_string_with_precision(denomVector[i], PRECISIONCONST) + "s^" + std::to_string(s) + " + ";
        }

        // Delete final +
        if (i == denomVector.size() - 1)
        {
            denomString.resize(denomString.size() - 3);
        }
    }

    if (numString.size() > 0 && denomString.size() > 0)
    {
    //std::cout << "/n" + numString + " / " + denomString;
        bw->updateTfLabel(numString, denomString);
    }

}

std::vector<float> MathEngine::getNum()
{
    return numVector;
}

std::vector<float> MathEngine::getDenom()
{
    return denomVector;
}

std::string MathEngine::getNumString()
{
    return numString;
}

std::string MathEngine::getDenomString()
{
    return denomString;
}

// Function to set precision of TF
std::string MathEngine::to_string_with_precision(float a_value, int n)
{
    std::ostringstream out;
    out << std::setprecision(n) << a_value;
    return out.str();
}
