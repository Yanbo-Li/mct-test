#ifndef BODEPLOTWINDOW_H
#define BODEPLOTWINDOW_H

#include <QDialog>

namespace Ui {
class BodePlotWindow;
}

class BodePlotWindow : public QDialog
{
    Q_OBJECT

public:
    explicit BodePlotWindow(QWidget *parent = 0);
    ~BodePlotWindow();

private slots:
    void on_backButton_clicked();
    void on_plotButton_clicked();

private:
    Ui::BodePlotWindow *ui;
};

#endif // BODEPLOTWINDOW_H
