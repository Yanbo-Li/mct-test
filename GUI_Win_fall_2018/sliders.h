#ifndef SLIDERS_H
#define SLIDERS_H

#include <QGroupBox>

class QDial;
class QSlider;

class Sliders : public QGroupBox
{
    Q_OBJECT

public:
    Sliders(const QString &title, QWidget *parent = 0);

signals:
    void valueChanged(int value);

public slots:
    void setValue(int value);
    void setMinimum(int value);
    void setMaximum(int value);

private:
    QSlider *slider;
    QDial *dial;
};

#endif // SLIDERS_H
