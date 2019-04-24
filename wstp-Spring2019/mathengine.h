#ifndef MATHENGINE_H
#define MATHENGINE_H
#include "startwindow.h"
#include "bodeplotwindow.h"
#include "controlwindow.h"
#include <QDialog>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

class StartWindow;
class BodePlotWindow;
class ControlWindow;

class MathEngine
{
public:
    MathEngine();
    ~MathEngine();

    void setTf(std::vector<double> num, std::vector<double> denom);

    std::vector<double> getNum();
    std::vector<double> getDenom();
    std::string getNumString();
    std::string getDenomString();
    std::string to_string_with_precision(float a_value, int n);

    void setWindowPtrs(StartWindow* d, BodePlotWindow* bw, ControlWindow* cw);
    StartWindow* getStartWindowPtr();
    BodePlotWindow* getBpwPtr();
    ControlWindow* getCwPtr();

private:
    std::string numString;
    std::string denomString;
    std::vector<double> numVector;
    std::vector<double> denomVector;
    StartWindow* d;
    BodePlotWindow* bw;
    ControlWindow* cw;

};

#endif // MCT_ENGINE_H
