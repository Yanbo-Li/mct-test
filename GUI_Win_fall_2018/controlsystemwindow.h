#ifndef CONTROLSYSTEMWINDOW_H
#define CONTROLSYSTEMWINDOW_H

#include <QWidget>
#include "mathengine.h"
#include "qcustomplot.h"
#include "wolframlink.h"

namespace Ui {
class ControlSystemWindow;
}

class MathEngine;

class ControlSystemWindow : public QWidget
{
    Q_OBJECT

public:
    ControlSystemWindow(MathEngine* me, WolframLink * link);
    ~ControlSystemWindow();
    void updateTfLabel(std::string numString, std::string denomString);
    void plotStepFile(std::string filename, QCustomPlot* plot, int count);
    void plotRootLocusFile(std::string filename, QCustomPlot* plot, int count);
    void plotRootLocusPoint(int graphNum, int index);
    std::map<struct XandY,double> store;
    void plot();

private slots:
    void on_plotButton_clicked();



    void on_backButton_clicked();
    void getClickedPoint(QMouseEvent*);

private:
    MathEngine* me;
    Ui::ControlSystemWindow *ui;
    double omega_integer;
    double zeta_integer;

    // The selected point
    QVector<double> pointSelecX, pointSelecY;

    QCPDataSelection selection;
    bool plotted;


    QVector<QVector<double>> xRootDataVec;
    QVector<QVector<double>> yRootDataVec;
    std::vector<QCPCurve*> polePoints;
    double xcord;
    double ycord;

    WolframLink * link;
};

#endif // CONTROLSYSTEMWINDOW_H
