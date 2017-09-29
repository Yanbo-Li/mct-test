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
/*
    connect(ui->omegaSlider, SIGNAL(valueChanged(int)),
            valueSpinBox, SLOT(setValue(int)));
    connect(valueSpinBox, SIGNAL(valueChanged(int)),
            horizontalSliders, SLOT(setValue(int)));
            */
}


BodePlotWindow::~BodePlotWindow()
{
    delete ui;
}

void BodePlotWindow::updateTfLabel(std::string numString, std::string denomString)
{
    ui->tfLabel->setText(QString::fromStdString(numString + " / " + denomString));
}

void BodePlotWindow::on_plotButton_clicked()
{

    std::ifstream f("sample_data.txt");

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
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(colum1, colum2);
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(0, 120);
    ui->customPlot->yAxis->setRange(-5, 52);
    ui->customPlot->replot();



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
