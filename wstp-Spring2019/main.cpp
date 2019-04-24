#include <QApplication>
#include <QLabel>
#include <QWidget>
#include <iostream>
#include <vector>
#include "mathengine.h"
#include "startwindow.h"
#include "bodeplotwindow.h"
#include "controlwindow.h"
#include "wolframlink.h"
#include "wstp.h"
#include "graphs.h"
#include "chart.h"
#include "mainwindow.h"
#include "chartview.h"

using namespace std;


int main(int argc, char *argv[ ])
{
    // ****************** GUI code below **********************
    QApplication a(argc, argv);
    Graphs *graphs = new Graphs();

    MathEngine *mathEngine = new MathEngine();
    StartWindow* sw = new StartWindow(mathEngine, graphs);
    ControlWindow* cw = new ControlWindow(mathEngine, graphs);
    BodePlotWindow* bp = new BodePlotWindow(mathEngine, graphs);
    mathEngine->setWindowPtrs(sw, bp, cw);
    sw->show(); // show initial window
    return a.exec();
}
