#include "controlwindow.h"
#include "ui_controlwindow.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

ControlWindow::ControlWindow(MathEngine* me) :  ui(new Ui::ControlWindow)
{
    this->me = me;
    ui->setupUi(this);
    plotted = false;
    // Set initial values for spin boxes
    ui->kpMinBox->setValue(0);
    ui->kpMaxBox->setValue(100);
    ui->kiMinBox->setValue(0);
    ui->kiMaxBox->setValue(100);
    ui->kdMinBox->setValue(0);
    ui->kdMaxBox->setValue(100);
    // Set up sliders
    ui->kpSlider->setTickPosition(QSlider::TicksBothSides);
    ui->kpSlider->setTickInterval(50);
    ui->kpSlider->setSingleStep(0.1);
    ui->kdSlider->setTickPosition(QSlider::TicksBothSides);
    ui->kdSlider->setTickInterval(50);
    ui->kdSlider->setSingleStep(0.1);
    ui->kiSlider->setTickPosition(QSlider::TicksBothSides);
    ui->kiSlider->setTickInterval(50);
    ui->kiSlider->setSingleStep(0.1);
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

void ControlWindow::on_plotButton_clicked()
{

    std::ifstream f("step1.txt");

    std::string line;

    static QVector<double> colum1; //defined as ...static to avoid over-writing
    static QVector<double> colum2;

    while (std::getline(f, line))
    {

      std::istringstream iss(line);
      double n;
      double n2;

      while (iss >> n)
      {
        colum1.push_back(n);
        iss >> n2;
        colum2.push_back(n2);
      }

    }
    f.close();

    // create graph and assign data to it:
    if (plotted == false)
    {
        ui->stepPlot->addGraph();
        ui->stepPlot->graph(0)->setData(colum1, colum2);
        // give the axes some labels:
        ui->stepPlot->xAxis->setLabel("x");
        ui->stepPlot->yAxis->setLabel("y");
        // set axes ranges, so we see all data:
        ui->stepPlot->xAxis->setRange(0, 10);
        ui->stepPlot->yAxis->setRange(0, 1);
        ui->stepPlot->replot();
        plotted = true;
    }
}

void ControlWindow::updateTfLabel(std::string numString, std::string denomString)
{
    ui->tfLabel->setText(QString::fromStdString(numString + " / " + denomString));
}

void ControlWindow::on_kpMinBox_valueChanged(double arg1)
{
    int val = (int)arg1;
    ui->kpSlider->setMinimum(val);
}

void ControlWindow::on_kpMaxBox_valueChanged(double arg1)
{
    int val = (int)arg1;
    ui->kpSlider->setMaximum(1000.0);
}

void ControlWindow::on_kdMinBox_valueChanged(double arg1)
{
    int val = (int)arg1;
    ui->kdSlider->setMinimum(val);
}

void ControlWindow::on_kdMaxBox_valueChanged(double arg1)
{
    int val = (int)arg1;
    ui->kdSlider->setMaximum(1000.0);
}

void ControlWindow::on_kiMinBox_valueChanged(double arg1)
{
    int val = (int)arg1;
    ui->kiSlider->setMinimum(val);
}

void ControlWindow::on_kiMaxBox_valueChanged(double arg1)
{
    int val = (int)arg1;
    ui->kiSlider->setMaximum(1000.0);
}

void ControlWindow::on_kpSlider_valueChanged(int value)
{
    double val = (double(value)/1000.0) + kp_integer; //need global variable for integer part of kp
    if(value<1000.0){ // prevents a bug where the slider keeps increasing the spin box when holding in rightmost position
    ui->kpValBox->setValue(val);
    }
    else{}
}

void ControlWindow::on_kpValBox_valueChanged(double arg1)
{
    //Takes the integer part of the number entered into kp spin box
    int kp_int = (int)arg1;
    //Pass kp_int to global double variable for integer part of kp
    kp_integer =double(kp_int);
    //Debugging:Makes sure the integer part is correct
    QString s = QString::number(kp_int);
    //ui->kpLineEdit->setText(s);
    //Subtracts integer part of arg1
    double arg1_cut = arg1 - kp_integer;
    //Multipies fractional part of arg1 by 100 because slider accepts only int
    double preval = 1000.0*arg1_cut;
    int val = (int)preval;
    ui->kpSlider->setValue(val);
}

void ControlWindow::on_kdSlider_valueChanged(int value)
{
    double val = (double(value)/1000.0) + kd_integer; //need global variable for integer part of kd
    if(value<1000.0){ // prevents a bug where the slider keeps increasing the spin box when holding in rightmost position
    ui->kdValBox->setValue(val);
    }
    else{}
}

void ControlWindow::on_kdValBox_valueChanged(double arg1)
{
    //Takes the integer part of the number entered into kd spin box
    int kd_int = (int)arg1;
    //Pass kd_int to global double variable for integer part of kd
    kd_integer =double(kd_int);
    //Debugging:Makes sure the integer part is correct
    QString s = QString::number(kd_int);
    //ui->kdLineEdit->setText(s);
    //Subtracts integer part of arg1
    double arg1_cut = arg1 - kd_integer;
    //Multipies fractional part of arg1 by 100 because slider accepts only int
    double preval = 1000.0*arg1_cut;
    int val = (int)preval;
    ui->kdSlider->setValue(val);
}

void ControlWindow::on_kiSlider_valueChanged(int value)
{
    double val = (double(value)/1000.0) + ki_integer; //need global variable for integer part of ki
    if(value<1000.0){ // prevents a bug where the slider keeps increasing the spin box when holding in rightmost position
    ui->kiValBox->setValue(val);
    }
    else{}
}

void ControlWindow::on_kiValBox_valueChanged(double arg1)
{
    //Takes the integer part of the number entered into ki spin box
    int ki_int = (int)arg1;
    //Pass ki_int to global double variable for integer part of ki
    ki_integer =double(ki_int);
    //Debugging:Makes sure the integer part is correct
    QString s = QString::number(ki_int);
    //ui->kiLineEdit->setText(s);
    //Subtracts integer part of arg1
    double arg1_cut = arg1 - ki_integer;
    //Multipies fractional part of arg1 by 100 because slider accepts only int
    double preval = 1000.0*arg1_cut;
    int val = (int)preval;
    ui->kiSlider->setValue(val);
}
