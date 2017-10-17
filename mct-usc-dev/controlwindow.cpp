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
