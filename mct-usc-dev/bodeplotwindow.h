#ifndef BODEPLOTWINDOW_H
#define BODEPLOTWINDOW_H

#include <QWidget>
#include "mathengine.h"

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
    void updateTfLabel(MathEngine* me);

private slots:
    void on_backButton_clicked();
    void on_plotButton_clicked();

private:
    MathEngine* me;
    Ui::BodePlotWindow *ui;
};

#endif // BODEPLOTWINDOW_H
