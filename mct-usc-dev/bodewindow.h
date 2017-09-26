#ifndef BODEWINDOW_H
#define BODEWINDOW_H

#include <QWidget> // added for widgets
// needed for sliders and text boxes
class QGroupBox;
class QLabel;
class QSpinBox;
class Sliders;

class BodeWindow;


class BodeWindow : public QWidget
{
    Q_OBJECT

public:
    BodeWindow();

private:

// makes the controls in bodewindow
    void createControls(const QString &title);
    void on_enterButton_clicked();
// These are for the sliders and text boxes
    Sliders *horizontalSliders;
    QGroupBox *controlsGroup;
    QLabel *minimumLabel;
    QLabel *maximumLabel;
    QLabel *valueLabel;
    QSpinBox *minimumSpinBox;
    QSpinBox *maximumSpinBox;
    QSpinBox *valueSpinBox;
};

#endif // BODEWINDOW_H
