#include "controlwindow.h"
#include "ui_controlwindow.h"

ControlWindow::ControlWindow(MathEngine* me) :  ui(new Ui::ControlWindow)
{
    this->me = me;
    ui->setupUi(this);
}

ControlWindow::~ControlWindow()
{
    delete ui;
}
