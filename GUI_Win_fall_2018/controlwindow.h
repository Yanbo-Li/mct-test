#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QWidget>
#include "qcustomplot.h"
#include "mathengine.h"

// Forward Declaration
namespace Ui {
class ControlWindow;
}

class MathEngine;

struct XandY{
public:
    double x;
    double y;
    bool operator <(const struct XandY& rhs) const{
        return this->x<rhs.x;
    }
};

class ControlWindow : public QWidget
{
    Q_OBJECT

public:
    ControlWindow(MathEngine* me);
    ~ControlWindow();
    void updateTfLabel(std::string numString, std::string denomString);
    void plotStepFile(std::string filename, QCustomPlot* plot, int count);
    void plotRootLocusFile(std::string filename, QCustomPlot* plot, int count);
    void plotRootLocusPoint(int graphNum, int index);
    std::map<struct XandY,double> store;

private slots:
    void on_backButton_clicked();
    void on_plotButton_clicked();

    void on_kpMinBox_valueChanged(double arg1);

    void on_kdMaxBox_valueChanged(double arg1);

    void on_kpMaxBox_valueChanged(double arg1);

    void on_kdMinBox_valueChanged(double arg1);

    void on_kiMinBox_valueChanged(double arg1);

    void on_kiMaxBox_valueChanged(double arg1);

    void on_kpSlider_valueChanged(int value);

    void on_kpValBox_valueChanged(double arg1);

    void on_kdSlider_valueChanged(int value);

    void on_kdValBox_valueChanged(double arg1);

    void on_kiSlider_valueChanged(int value);

    void on_kiValBox_valueChanged(double arg1);

    void getClickedPoint(QMouseEvent*);

private:
    Ui::ControlWindow* ui;
    MathEngine* me;
    bool plotted;
    double kp_integer;
    double kd_integer;
    double ki_integer;
    QVector<QVector<double>> xRootDataVec;
    QVector<QVector<double>> yRootDataVec;
    std::vector<QCPCurve*> polePoints;
    double xcord;
    double ycord;

    // Root Locus Plot
    // Step Plot
    // Kp slider, lineEdit, minEdit, maxEdit
    // Kd slider, lineEdit, minEdit, maxEdit
    // Ki slider, lineEdit, minEdit, maxEdit
};

#endif // CONTROLWINDOW_H
