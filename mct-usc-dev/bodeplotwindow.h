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
    void updateTfLabel(std::string numString, std::string denomString);

private slots:
    void on_backButton_clicked();
    void on_plotButton_clicked();

    void on_confirmButton_clicked();

private:
    MathEngine* me;
    Ui::BodePlotWindow *ui;

    bool plotted;
};

#endif // BODEPLOTWINDOW_H
