#ifndef BODEWINDOW_H
#define BODEWINDOW_H

#include <QMainWindow>

namespace Ui {
class BodeWindow;
}

class BodeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BodeWindow(QWidget *parent = 0);
    ~BodeWindow();

private:
    Ui::BodeWindow *ui;
};

#endif // BODEWINDOW_H
