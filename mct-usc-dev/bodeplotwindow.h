#ifndef BODEPLOTWINDOW_H
#define BODEPLOTWINDOW_H

#include <QWidget>
#include "mathengine.h"
#include "qcustomplot.h"

namespace Ui {
class BodePlotWindow;
}

class MathEngine;

class BodePlotWindow : public QWidget
{
    Q_OBJECT

public:
    BodePlotWindow();
    BodePlotWindow(MathEngine* me);
    ~BodePlotWindow();
    void updateTfLabel(std::string numString, std::string denomString);
    // Function to move selected point
    void movePoint(double x, double y);
    void plot();

private slots:
    void on_backButton_clicked();
    void on_plotButton_clicked();

    void on_confirmButton_clicked();
    void on_omegaSlider_valueChanged(int value);

    void on_omegaValSpinBox_valueChanged(double arg1);

    void on_omegaMinSpinBox_valueChanged(double arg1);

    void on_omegaMaxSpinBox_valueChanged(double arg1);

    void on_zetaMinSpinBox_valueChanged(double arg1);

    void on_zetaMaxSpinBox_valueChanged(double arg1);

    void on_zetaSlider_valueChanged(int value);

    void on_zetaValSpinBox_valueChanged(double arg1);

    void on_upButton_clicked();

    void getClickedPoint();
    void updateClickedPoint();
    void graphClicked(QCPAbstractPlottable *plottable, int dataIndex);

    virtual void paintEvent(QPaintEvent *);




private:
    MathEngine* me;
    Ui::BodePlotWindow *ui;

    double omega_integer;
    double zeta_integer;
    // The selected point
    QVector<double> pointSelecX, pointSelecY;

    QCPDataSelection selection;
    bool plotted;

    double xcord;
    double ycord;
};

#endif // BODEPLOTWINDOW_H
