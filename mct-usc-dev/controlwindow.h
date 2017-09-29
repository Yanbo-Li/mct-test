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
