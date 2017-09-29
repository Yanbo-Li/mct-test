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

void ControlWindow::on_backButton_clicked()
{
    ui->rootLocusPlot->clearPlottables();
    ui->rootLocusPlot->replot();
    ui->stepPlot->clearPlottables();
    ui->stepPlot->replot();
    this->hide();
    me->getBpwPtr()->show();
}

void ControlWindow::updateTfLabel(std::string numString, std::string denomString)
{
    ui->tfLabel->setText(QString::fromStdString(numString + " / " + denomString));
}
