#include <QApplication>
#include <QLabel>
#include <QWidget>
#include "dialog.h"
#include "mathengine.h"
int main(int argc, char *argv[ ])
{

    QApplication a(argc, argv);
    MathEngine mathEngine;

    Dialog d(&mathEngine);
    d.show();

    return a.exec();
}
