#include <QtWidgets>
#include "sliders.h"

Sliders::Sliders(const QString &title, QWidget *parent): QGroupBox(title, parent)
{
    slider = new QSlider(Qt::Horizontal);
    slider->setFocusPolicy(Qt::StrongFocus);
    slider->setTickPosition(QSlider::TicksBothSides);
    slider->setTickInterval(10);
    slider->setSingleStep(1);

    dial = new QDial;
    dial->setFocusPolicy(Qt::StrongFocus);

    connect(slider, SIGNAL(valueChanged(int)), dial, SLOT(setValue(int)));
    connect(dial, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
    connect(slider, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));

    QBoxLayout::Direction direction;
    direction = QBoxLayout::LeftToRight;

    QBoxLayout *slidersLayout = new QBoxLayout(direction);
    slidersLayout->addWidget(slider);
    slidersLayout->addWidget(dial);
    setLayout(slidersLayout);
}

void Sliders::setValue(int value)
{
    slider->setValue(value);
}

void Sliders::setMinimum(int value)
{
    slider->setMinimum(value);
    dial->setMinimum(value);
}

void Sliders::setMaximum(int value)
{
    slider->setMaximum(value);
    dial->setMaximum(value);
}
