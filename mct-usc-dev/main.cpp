#include <QApplication>
#include <QLabel>
#include <QWidget>

#include "mathengine.h"
#include "dialog.h"
#include "bodeplotwindow.h"
int main(int argc, char *argv[ ])
{

    QApplication mct_usc(argc, argv);

    MathEngine mathEngine;
    Dialog* d = new Dialog(&mathEngine);
    BodePlotWindow* bp = new BodePlotWindow(&mathEngine);
    // RootLocusWindow rl(&mathEngine);

    mathEngine.setWindowPtrs(d, bp);
    d->show();

    return mct_usc.exec();
}
