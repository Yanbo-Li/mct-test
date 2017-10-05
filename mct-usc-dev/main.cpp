#include <QApplication>
#include <QLabel>
#include <QWidget>

#include "mathengine.h"
#include "startwindow.h"
#include "bodeplotwindow.h"
#include "controlwindow.h"
int main(int argc, char *argv[ ])
{

    QApplication mct_usc(argc, argv);

    MathEngine mathEngine;
    StartWindow* d = new StartWindow(&mathEngine);
    BodePlotWindow* bp = new BodePlotWindow(&mathEngine);
    ControlWindow* cw = new ControlWindow(&mathEngine);

    mathEngine.setWindowPtrs(d, bp, cw);
    d->show();

    return mct_usc.exec();
}
