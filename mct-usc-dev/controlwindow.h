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

class ControlWindow : public QWidget
{
    Q_OBJECT

public:
    ControlWindow(MathEngine* me);
    ~ControlWindow();
    void updateTfLabel(std::string numString, std::string denomString);

private slots:
    void on_backButton_clicked();

private:
    Ui::ControlWindow *ui;
    MathEngine* me;

    // Root Locus Plot
    // Step Plot
    // Kp slider, lineEdit, minEdit, maxEdit
    // Kd slider, lineEdit, minEdit, maxEdit
    // Ki slider, lineEdit, minEdit, maxEdit
};

#endif // CONTROLWINDOW_H
