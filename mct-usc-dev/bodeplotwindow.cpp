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
        ui->customPlot->replot();
        plotted = true;
    }


    // Ali TODO: update xyLabel
    // ui->xyLabel->setText();
        // If no data point selected, then setText("")
        // else, setText(xy);

    /*
    QCPDataSelection selection = graph->selection();
    double sum = 0;
    foreach (QCPDataRange dataRange, selection.dataRanges())
    {
      QCPGraphDataContainer::const_iterator begin = graph->data()->at(dataRange.begin()); // get range begin iterator from index
      QCPGraphDataContainer::const_iterator end = graph->data()->at(dataRange.end()); // get range end iterator from index
      for (QCPGraphDataContainer::const_iterator it=begin; it!=end; ++it)
      {
        // iterator "it" will go through all selected data points, as an example, we calculate the value average
        sum += it->value;
      }
    } */

    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                      QCP::iSelectPlottables);
    ui->customPlot->graph(0)->setSelectable(QCP::stSingleData);

    if (!ui->customPlot->graph(0)->selection().isEmpty())
    {
        QCPDataSelection selection = ui->customPlot->graph(0)->selection();

        double x = ui->customPlot->graph(0)->data()->at(selection.dataRange().begin())->key;
        double y = ui->customPlot->graph(0)->data()->at(selection.dataRange().begin())->value;

        std::string xy = std::to_string(x) + ", " + std::to_string(y);
        ui->xyLabel->setText(QString::fromStdString(xy));
    }
    else
    {
        ui->xyLabel->setText(QString::fromStdString("no point selected"));
    }
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
