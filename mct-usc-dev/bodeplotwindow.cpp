#include "ui_bodeplotwindow.h"
#include "bodeplotwindow.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

BodePlotWindow::BodePlotWindow(MathEngine* me) : ui(new Ui::BodePlotWindow)
{
    this->me = me;
    ui->setupUi(this);
    plotted = false;
// Set initial values for spin boxes
    ui->zetaMinSpinBox->setValue(0);
    ui->zetaMaxSpinBox->setValue(100);
    ui->omegaMinSpinBox->setValue(0);
    ui->omegaMaxSpinBox->setValue(100);
    // Set up sliders
    ui->omegaSlider->setTickPosition(QSlider::TicksBothSides);
    ui->omegaSlider->setTickInterval(10);
    ui->omegaSlider->setSingleStep(0.1);
    ui->zetaSlider->setTickPosition(QSlider::TicksBothSides);
    ui->zetaSlider->setTickInterval(50);
    ui->zetaSlider->setSingleStep(0.1);

    // Hide the upButton, it's broken currently
    ui->upButton->hide();

    // Set up click slot
    //connect(ui->customPlot, &QCustomPlot::mousePress, this, SLOT(updateClickedPoint()));
    connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(getClickedPoint()));
    connect(ui->customPlot, SIGNAL(mouseRelease(QMouseEvent*)), this, SLOT(updateClickedPoint()));
}


BodePlotWindow::~BodePlotWindow()
{
    delete ui;
}

void BodePlotWindow::updateTfLabel(std::string numString, std::string denomString)
{
    ui->tfLabel->setText(QString::fromStdString(numString + " / " + denomString));
}

void BodePlotWindow::movePoint(double x, double y)
{
    pointSelecX.append(x);
    pointSelecY.append(y);
}

void BodePlotWindow::plot()
{
    ui->customPlot->graph(0)->setData(pointSelecX,pointSelecY);
    ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->customPlot->replot();
    ui->customPlot->update();
}

void BodePlotWindow::on_plotButton_clicked()
{

    std::ifstream f("bode1.txt");

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

    // create graph and assign data to it:
    if (plotted == false)
    {
        ui->customPlot->addGraph();
        ui->customPlot->graph(0)->setData(colum1, colum2);
        // give the axes some labels:
        ui->customPlot->xAxis->setLabel("x");
        ui->customPlot->yAxis->setLabel("y");
        // set axes ranges, so we see all data:
        ui->customPlot->xAxis->setRange(0, 120);
        ui->customPlot->yAxis->setRange(-5, 52);
        ui->customPlot->rescaleAxes(true);
        ui->customPlot->replot();
        plotted = true;
    }
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                      QCP::iSelectPlottables);
    ui->customPlot->graph(0)->setSelectable(QCP::stSingleData);


    //updateClickedPoint();
}


void BodePlotWindow::on_backButton_clicked()
{
    ui->customPlot->clearPlottables();
    ui->customPlot->replot();
    this->hide();
    me->getStartWindowPtr()->show();
}


void BodePlotWindow::on_confirmButton_clicked()
{
    this->hide();
    me->getCwPtr()->show();
}
void BodePlotWindow::on_omegaSlider_valueChanged(int value)
{
    double val = (value/100.0) + omega_integer; //need global variable for integer part of omega
    if(value<100){ // prevents a bug where the slider keeps increasing the spin box when holding in rightmost position
    ui->omegaValSpinBox->setValue(val);}
    else{}
}

void BodePlotWindow::on_omegaValSpinBox_valueChanged(double arg1)
{
    //Takes the integer part of the number entered into omega spin box
    int omega_int = (int)arg1;
    //Pass omega_int to global double variable for integer part of omega
    omega_integer =double(omega_int);
    //Debugging:Makes sure the integer part is correct
    QString s = QString::number(omega_int);
    //ui->omegaLineEdit->setText(s);
    //Subtracts integer part of arg1
    double arg1_cut = arg1 - omega_integer;
    //Multipies fractional part of arg1 by 100 because slider accepts only int
    double preval = 100.0*arg1_cut;
    int val = (int)preval;
    ui->omegaSlider->setValue(val);
}
// Minimum and Maximum spin boxes should stay constant (from 0 to 100)
void BodePlotWindow::on_omegaMinSpinBox_valueChanged(double arg1)
{
    int val = (int)arg1;
    ui->omegaSlider->setMinimum(val);
}

void BodePlotWindow::on_omegaMaxSpinBox_valueChanged(double arg1)
{
    int val = (int)arg1;
    ui->omegaSlider->setMaximum(100.0);
}

void BodePlotWindow::on_zetaMinSpinBox_valueChanged(double arg1)
{
    int val = (int)arg1;
    ui->zetaSlider->setMinimum(val);
}

void BodePlotWindow::on_zetaMaxSpinBox_valueChanged(double arg1)
{
    int val = (int)arg1;
    ui->zetaSlider->setMaximum(1000.0);
}

void BodePlotWindow::on_zetaSlider_valueChanged(int value)
{
    double val = (double(value)/1000.0) + zeta_integer; //need global variable for integer part of zeta
    if(value<1000.0){ // prevents a bug where the slider keeps increasing the spin box when holding in rightmost position
    ui->zetaValSpinBox->setValue(val);
    }
    else{}
}

void BodePlotWindow::on_zetaValSpinBox_valueChanged(double arg1)
{
    //Takes the integer part of the number entered into zeta spin box
    int zeta_int = (int)arg1;
    //Pass omega_int to global double variable for integer part of omega
    zeta_integer =double(zeta_int);
    //Debugging:Makes sure the integer part is correct
    QString s = QString::number(zeta_int);
    //ui->zetaLineEdit->setText(s);
    //Subtracts integer part of arg1
    double arg1_cut = arg1 - zeta_integer;
    //Multipies fractional part of arg1 by 100 because slider accepts only int
    double preval = 1000.0*arg1_cut;
    int val = (int)preval;
    ui->zetaSlider->setValue(val);
}

void BodePlotWindow::on_upButton_clicked()
{
    movePoint(pointSelecX[0], pointSelecY[0] + 4.0);
    plot();
}

void BodePlotWindow::getClickedPoint()
{
    selection = ui->customPlot->graph(0)->selection();
}

void BodePlotWindow::updateClickedPoint()
{
    //QCPDataSelection selection = ui->customPlot->graph(0)->selection();

    if (!selection.isEmpty())
    {
        double x = ui->customPlot->graph(0)->data()->at(selection.dataRange().begin())->key;
        double y = ui->customPlot->graph(0)->data()->at(selection.dataRange().begin())->value;
        // Take the selected point and put into double array
        pointSelecX.append(x);
        pointSelecY.append(y);
        // Display selected point on console
        //std::cout << pointSelecX[0] << " " << pointSelecY[0] << std::endl;


        std::string xy = std::to_string(x) + ", " + std::to_string(y);
        // std::cout << x << " " << y << std::endl;
        ui->xyLabel->setText(QString::fromStdString(xy));
    }
    else
    {
        ui->xyLabel->setText(QString::fromStdString("no point selected"));
    }
}
