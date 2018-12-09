#include "controlsystemwindow.h"
#include "ui_controlsystemwindow.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <QVector>

using namespace std;

ControlSystemWindow::ControlSystemWindow(MathEngine* me, WolframLink * link) :
    ui(new Ui::ControlSystemWindow)
{
    this->me = me;
    this->link = link;
    ui->setupUi(this);
    plotted = false;


    ui->phasePlot->xAxis->setLabel("Frequency(rad/s)");
    ui->phasePlot->yAxis->setLabel("Phase(deg)");
    ui->magnitudePlot->yAxis->setLabel("Magnitude(dB)");

    connect(ui->phasePlot, SIGNAL(selectionChangedByUser()),this,SLOT(getClickedPoint()));
    connect(ui->magnitudePlot, SIGNAL(selectionChangedByUser()),this,SLOT(getClickedPoint()));
    connect(ui->rootlocusPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(getClickedPoint(QMouseEvent*)));
}



void ControlSystemWindow::on_plotButton_clicked()
{
    //Plot the Phase of Bodeplot
    Plot P = link->getPhase();

    std::string line;

    QVector<double> colum1; //defined as ...static to avoid over-writing
    QVector<double> colum2;

    colum1 = QVector<double>::fromStdVector(P.x);
    colum2 = QVector<double>::fromStdVector(P.y);

    //Plot the Magnitude of Bodeplot
    Plot Q = link->getFreq();

    QVector<double> colum3; //defined as ...static to avoid over-writing
    QVector<double> colum4;

    colum3 = QVector<double>::fromStdVector(Q.x);
    colum4 = QVector<double>::fromStdVector(Q.y);

    //plot step response
    plotStepFile("step1.txt", ui->stepresponsePlot, 0);

    //plot root locus
    plotRootLocusFile("datarootlocus1.txt", ui->rootlocusPlot, 0);
    plotRootLocusFile("datarootlocus2.txt", ui->rootlocusPlot, 1);
    plotRootLocusFile("datarootlocus3.txt", ui->rootlocusPlot, 2);
    plotRootLocusFile("datarootlocus4.txt", ui->rootlocusPlot, 3);

    // add a graph for circle, do only once; this should be part of plotrootlocusfile
    ui->rootlocusPlot->addGraph();

    // call the function
    plotRootLocusPoint(0, 250);


    if (plotted == false)
    {
        ui->phasePlot->addGraph();
        ui->phasePlot->graph(0)->setData(colum1, colum2);

        //set subgrid visible
        //ui->phasePlot->xAxis->grid()->setSubGridVisible(true);
        //ui->phasePlot->yAxis->grid()->setSubGridVisible(true);
        //find the limits for x and y values, set axes ranges, so we see all data
        //set the maximum range of x to [0.01,100]


        ui->phasePlot->xAxis->setScaleType(QCPAxis::stLogarithmic);
        QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
        ui->phasePlot->xAxis->setTicker(logTicker);
        ui->phasePlot->xAxis->setNumberFormat("eb"); // e = exponential, b = beautiful decimal powers
        ui->phasePlot->xAxis->setNumberPrecision(0); // makes sure "1*10^4" is displayed only as "10^4"

        //QSharedPointer<QCPAxisTickerFixed> fixedTicker(new QCPAxisTickerFixed);
        //ui->phasePlot->yAxis->setTicker(fixedTicker);
        //fixedTicker->setTickStep(45);
        ui->phasePlot->yAxis->setSubTicks(false);

        ui->phasePlot->rescaleAxes(true); // plot visible points
        ui->phasePlot->xAxis->setRange(0.01, 100);
        ui->phasePlot->replot();

        //ui->phasePlot->yAxis->setRange(yMin, yMax);

        ui->magnitudePlot->addGraph();
        ui->magnitudePlot->graph(0)->setData(colum3, colum4);

        ui->magnitudePlot->xAxis->setScaleType(QCPAxis::stLogarithmic);
        //QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
        ui->magnitudePlot->xAxis->setTicker(logTicker);
        ui->magnitudePlot->xAxis->setNumberFormat("eb"); // e = exponential, b = beautiful decimal powers
        ui->magnitudePlot->xAxis->setNumberPrecision(0); // makes sure "1*10^4" is displayed only as "10^4"

        //QSharedPointer<QCPAxisTickerFixed> fixedTicker(new QCPAxisTickerFixed);
        //ui->magnitudePlot->yAxis->setTicker(fixedTicker);
        //fixedTicker->setTickStep(20);
        ui->magnitudePlot->yAxis->setSubTicks(false);

        ui->magnitudePlot->rescaleAxes(true); // plot visible points
        ui->magnitudePlot->xAxis->setRange(0.01, 100);

        ui->magnitudePlot->replot();


        plotted=true;
    }
    ui->phasePlot->setInteractions(QCP::iRangeZoom | QCP::iSelectAxes |
                                      QCP::iSelectPlottables);
    ui->phasePlot->graph(0)->setSelectable(QCP::stSingleData);

    ui->magnitudePlot->setInteractions(QCP::iRangeZoom | QCP::iSelectAxes |
                                      QCP::iSelectPlottables);
    ui->magnitudePlot->graph(0)->setSelectable(QCP::stSingleData);
}

ControlSystemWindow::~ControlSystemWindow()
{
    delete ui;
}

void ControlSystemWindow::on_backButton_clicked()
{
    ui->phasePlot->clearPlottables();
    ui->phasePlot->replot();
    ui->magnitudePlot->clearPlottables();
    ui->magnitudePlot->replot();
    ui->rootlocusPlot->clearPlottables();
    ui->rootlocusPlot->replot();
    ui->stepresponsePlot->clearPlottables();
    ui->stepresponsePlot->replot();

    this->hide();
    me->getStartWindowPtr()->show();
}

void ControlSystemWindow::plotStepFile(std::string filename, QCustomPlot* plot, int count)
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


void ControlSystemWindow::plotRootLocusFile(std::string filename, QCustomPlot* plot, int count)
{
    // Root Locus Plot
    std::ifstream f(filename);
    std::string line;

    int counter = 0;
    QVector<double> paramIndex;

    // Create QCPCurve on the axes xAxis, yAxis
    QCPCurve* rootlocus = new QCPCurve(ui->rootlocusPlot->xAxis, ui->rootlocusPlot->yAxis);

    QVector<double> paramData, xRootData, yRootData;

    while (std::getline(f, line))
    {

      std::istringstream iss(line);
      double n;
      double n2;

      while (iss >> n)
      {
        paramData.push_back((double)counter);

        counter++;
        xRootData.push_back(n);

        iss >> n2;
        yRootData.push_back(n2);

      }

    }
    f.close();


    rootlocus->setData(paramData, xRootData, yRootData, true);

    plot->rescaleAxes(true);
    plot->setInteractions( QCP::iRangeZoom | QCP::iSelectPlottables);
    plot->replot();

    xRootDataVec.push_back(xRootData);
    yRootDataVec.push_back(yRootData);

    // Create the QCPCurve* for the root locus points
    QCPCurve* rootlocusPoint = new QCPCurve(ui->rootlocusPlot->xAxis, ui->rootlocusPlot->yAxis);
    polePoints.push_back(rootlocusPoint);

}

void ControlSystemWindow::plotRootLocusPoint(int graphNum, int index)
{

    QCPCurve* rootlocusPoint = polePoints[graphNum];
    QVector<double> x, y, paramData;
    paramData.push_back(0); // 0th index
    xRootDataVec[graphNum][index] = xcord;
    yRootDataVec[graphNum][index] = ycord;
    x.push_back(xRootDataVec[graphNum][index]);
    y.push_back(yRootDataVec[graphNum][index]);
    rootlocusPoint->setData(paramData, x, y, true);

    //ui->rootLocusPlot->graph(graphNum)->setData(x,y);
    //rootLocusPoint->setScatterStyle(QCPScatterStyle::ssCircle);
    rootlocusPoint->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle,QPen(Qt::black, 0), QColor(139, 0, 0, 100), 8));
    ui->rootlocusPlot->replot();
    ui->rootlocusPlot->update();

}

void ControlSystemWindow::getClickedPoint(QMouseEvent* event)
{

    double x = ui->rootlocusPlot->xAxis->pixelToCoord(event->pos().x());
    double y = ui->rootlocusPlot->yAxis->pixelToCoord(event->pos().y());

     xcord = x;
     ycord = y;

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
          std::string xy = std::to_string(x) + ", " + std::to_string(y);
          ui->tfLabel->setText(QString::fromStdString(xy));
     }else{
          ui->tfLabel->setText(QString::fromStdString("no point selected"));
     }

     plotRootLocusPoint(0, 250);

}















