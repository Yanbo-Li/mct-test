#ifndef MATHENGINE_H
#define MATHENGINE_H

#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

class MathEngine
{
public:
    MathEngine();
    void setTf(std::vector<float> num, std::vector<float> denom);
    std::vector<float> getNum();
    std::vector<float> getDenom();

    std::string getNumString();
    std::string getDenomString();
    std::string to_string_with_precision(float a_value, int n);

private:
    std::string numString;
    std::string denomString;
    std::vector<float> numVector;
    std::vector<float> denomVector;
    // Function to set precision of TF

};

#endif // MCT_ENGINE_H
