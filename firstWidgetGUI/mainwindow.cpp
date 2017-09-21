#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

   ui->statusLabel->setText("Button is Clicked!!");
   std::ifstream f("data1.txt");

std::string line;

    int counter = 0;
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






