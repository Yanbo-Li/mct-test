#include "controlwindow.h"
#include "ui_controlwindow.h"
#include "chart.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "chart.h"

using namespace std;

ControlWindow::ControlWindow(MathEngine* me, Graphs *graph) :
    ui(new Ui::ControlWindow)
{
    this->me = me;
    this->graphs = graph;
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
    ui->stepPlot->clearPlottables();
    ui->stepPlot->replot();
    this->hide();
    me->getBpwPtr()->show();
}

void ControlWindow::on_plotButton_clicked()
{
    std::cout << "plot clicked" << std::endl;
    plotRootLocusPoint();
    // connect(ui->rootLocusPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(getClickedPoint(QMouseEvent*)));
}

void ControlWindow::plotRootLocusPoint()
{

    for(size_t i = 0; i < graphs->getRootLocus().size(); i++) {
        std::cout << "i = " << i << std::endl;
        ui->rootLocusPlot->addSeries(graphs->getRootLocus()[i], i);
    }
        ui->rootLocusPlot->chart()->axisX()->setRange(-5, 5);
        ui->rootLocusPlot->chart()->axisY()->setRange(-5, 5);
}


void ControlWindow::plotStepFile(std::string filename, QCustomPlot* plot, int count)
{

    // Step Plot
    std::ifstream f(filename);

    std::string line;

    static QVector<double> colum1; //defined as ...static to avoid over-writing
    static QVector<double> colum2;

    while (std::getline(f, line))
    {

      std::istringstream iss(line);
      double n;
      double n2;

      struct XandY key;
      while (iss >> n)
      {
         key.x = n;
        colum1.push_back(n);
        iss >> n2;
        key.y = n2;
        colum2.push_back(n2);
      }
      store[key] = n2;
     // std::cout<<"key:"<<key.x<<"\t"<<key.y<<"\t"<<"value: "<<n2;

    }
    f.close();

    // create graph and assign data to it:
    //if (plotted == false)
    //{
        plot->addGraph();
        plot->graph(count)->setData(colum1, colum2);
        // give the axes some labels:
        plot->xAxis->setLabel("x");
        plot->yAxis->setLabel("y");
        // set axes ranges, so we see all data:
        //plot->xAxis->setRange(-10, 10);
        //plot->yAxis->setRange(-10, 10);
        plot->rescaleAxes(true);
        plot->replot();
        //plotted = true;
    //}
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

void ControlWindow::getClickedPoint(QMouseEvent* event)
{

//    double x = ui->rootLocusPlot->xAxis->pixelToCoord(event->pos().x());
//    double y = ui->rootLocusPlot->yAxis->pixelToCoord(event->pos().y());
/*
    QCPDataSelection selection;
    selection = ui->rootLocusPlot->graph(0)->selection();
    //QCPDataSelection selection2 = ui->customPlot->graph(0)->selection();
    cout << "DEBUG: isEmpty Function is "<< selection.isEmpty() << endl;
    cout << "DEBUG: Number of selection points "<< selection.dataPointCount() << endl;

    double x = ui->rootLocusPlot->graph()->data()->at(selection.dataRange().begin())->key;
    double y = ui->rootLocusPlot->graph()->data()->at(selection.dataRange().begin())->value;
    std::cout << "DEBUG: x is: "<< x <<"y is:"<< y << endl;

*/



//     xcord = x;
//     ycord = y;

     vector<double> x1 = {0,2.45453654,6.54657567,9.546746548};
     vector<double> y1 = {0,3.3243245435,4.354354356,8.3243245};


     bool isXpresent = false;
     bool isYpresent = false;

    int roundNum = 1000000;
     for(int i=0;i<x1.size();i++) {
         if( ((roundf(x1[i]*roundNum))/roundNum) == (roundf(xcord)*roundNum)/roundNum ) {
             isXpresent = true;
         }
     }

     for(int i=0;i<y1.size();i++) {
         if( ((roundf(y1[i]*roundNum))/roundNum) == (roundf(ycord)*roundNum)/roundNum ) {
             isYpresent = true;
         }
     }

     if(isXpresent && isYpresent) {
          // std::string xy = std::to_string(x) + ", " + std::to_string(y);
          //mui->tfLabel->setText(QString::fromStdString(xy));
     }else{
          ui->tfLabel->setText(QString::fromStdString("no point selected"));
     }

    /*
    QCPDataSelection selection = curve->selection();

    if (!selection.isEmpty())
    {
        double x = curve->data()->at(selection.dataRange().begin())->key;
        double y = curve->data()->at(selection.dataRange().begin())->value;
        // Take the selected point and put into double array
        // Display selected point on console
        //std::cout << pointSelecX[0] << " " << pointSelecY[0] << std::endl;


        std::string xy = std::to_string(x) + ", " + std::to_string(y);
        // std::cout << x << " " << y << std::endl;
        ui->tfLabel->setText(QString::fromStdString(xy));
    }
    else
    {
        ui->tfLabel->setText(QString::fromStdString("no point selected"));
    }
*/
}



