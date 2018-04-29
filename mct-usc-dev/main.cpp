#include <QApplication>
#include <QLabel>
#include <QWidget>

#include "mathengine.h"
#include "startwindow.h"
#include "bodeplotwindow.h"
#include "controlwindow.h"
#include "wolframlink.h"





int main(int argc, char *argv[ ])
{

    QApplication mct_usc(argc, argv);

    WolframLink * link = new WolframLink(); // create WSTP Link

    link->setupPackages(); // load all

    MathEngine mathEngine;
    StartWindow* sw = new StartWindow(&mathEngine, link);
    BodePlotWindow* bp = new BodePlotWindow(&mathEngine, link);
    ControlWindow* cw = new ControlWindow(&mathEngine);

    mathEngine.setWindowPtrs(sw, bp, cw);
    sw->show();

    //WSENV ep;
    //WSLINK lp;



    return mct_usc.exec();
}
