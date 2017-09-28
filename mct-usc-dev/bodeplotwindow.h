#ifndef BODEPLOTWINDOW_H
#define BODEPLOTWINDOW_H

#include <QWidget>
#include "mathengine.h"
#include "dialog.h"

namespace Ui {
class BodePlotWindow;
}

class BodePlotWindow : public QWidget
{
    Q_OBJECT

public:
    BodePlotWindow();
    BodePlotWindow(MathEngine* me);
    ~BodePlotWindow();

private slots:
    void on_backButton_clicked();
    void on_plotButton_clicked();

private:
    MathEngine* me;
    Ui::BodePlotWindow *ui;
};

#endif // BODEPLOTWINDOW_H
