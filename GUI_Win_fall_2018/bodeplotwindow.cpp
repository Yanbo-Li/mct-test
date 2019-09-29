#include "ui_bodeplotwindow.h"
#include "bodeplotwindow.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <QVector>
#include "wstp.h"

//#include "wolframlink.h"

using namespace std;

BodePlotWindow::BodePlotWindow(MathEngine* me, WolframLink * link) : ui(new Ui::BodePlotWindow)
{
    this->me = me;
    this->link = link;

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
    connect(ui->customPlot, SIGNAL(selectionChangedByUser()), this, SLOT(getClickedPoint()));
    //connect(ui->customPlot, SIGNAL(mouseRelease(QMouseEvent*)), this, SLOT(updateClickedPoint()));
    //connect(ui->customPlot, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*,int)));
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
    ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);
    ui->customPlot->replot();
    ui->customPlot->update();
}

void BodePlotWindow::on_plotButton_clicked()
{
    Plot P = link->getPhase();

    std::ifstream f("bode1.txt");

    std::string line;

    QVector<double> colum1; //defined as ... static to avoid over-writing
    QVector<double> colum2;

    colum1 = QVector<double>::fromStdVector(P.x);
    colum2 = QVector<double>::fromStdVector(P.y);

    // create graph and assign data to it:
    if (plotted == false)
    {
        ui->customPlot->addGraph();
        ui->customPlot->graph(0)->setData(colum1, colum2);
        // give the axes some labels:
        ui->customPlot->xAxis->setLabel("Frequency(rad/sec)");
        ui->customPlot->yAxis->setLabel("Phase(deg)");
        // set subgrid visible
        ui->customPlot->xAxis->grid()->setSubGridVisible(true);
        ui->customPlot->yAxis->grid()->setSubGridVisible(true);

        // find the limits for x and y values, set axes ranges, so we see all data
        int i, n;
        n = sizeof(colum1)/sizeof(colum1[0]);
        double xMax = 0, yMin = 0, yMax = 0;
        for(i = 0;i < n; ++i)
            {
               if(xMax < colum1[i])
                   xMax = colum1[i];
               if(yMax < colum2[i])
                   yMax = colum2[i];
               if(yMin > colum2[i])
                   yMin = colum2[i];
            }
        ui->customPlot->xAxis->setRange(0, xMax);
        ui->customPlot->yAxis->setRange(yMin, yMax);
        ui->customPlot->xAxis->setScaleType(QCPAxis::stLogarithmic);
        QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
        ui->customPlot->xAxis->setTicker(logTicker);
        ui->customPlot->xAxis->setNumberFormat("eb"); // e = exponential, b = beautiful decimal powers
        ui->customPlot->xAxis->setNumberPrecision(0); // makes sure "1*10^4" is displayed only as "10^4"
        ui->customPlot->rescaleAxes(true);
        ui->customPlot->replot();
        plotted = true;
    }
    ui->customPlot->setInteractions(QCP::iRangeZoom | QCP::iSelectAxes |
                                      QCP::iSelectPlottables);
    ui->customPlot->graph(0)->setSelectable(QCP::stSingleData);

    //updateClickedPoint();
}


void BodePlotWindow::on_backButton_clicked()
{
    ui->customPlot->clearGraphs();
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
    //QCPDataSelection selection2 = ui->customPlot->graph(0)->selection();
    cout << "DEBUG: isEmpty Function is "<< selection.isEmpty() << endl;
    cout << "DEBUG: Number of selection points "<< selection.dataPointCount() << endl;

    updateClickedPoint();
}

void BodePlotWindow::updateClickedPoint()
{
    //QCPDataSelection selection = ui->customPlot->graph(0)->selection();

    if (!selection.isEmpty())
    {
        double x = ui->customPlot->graph(0)->data()->at(selection.dataRange().begin())->key;
        double y = ui->customPlot->graph(0)->data()->at(selection.dataRange().begin())->value;
        cout << "DEBUG: x is: "<< x <<"y is:"<< y << endl;

        // Take the selected point and put into double array
        pointSelecX.append(x);
        pointSelecY.append(y);
        // Display selected point on console
        //std::cout << pointSelecX[0] << " " << pointSelecY[0] << std::endl;


        std::string xy = std::to_string(x) + ", " + std::to_string(y);
        // std::cout << x << " " << y << std::endl;
        ui->xyLabel->setText(QString::fromStdString(xy));

        xcord = x;
        ycord = y;


    }
    else
    {
        ui->xyLabel->setText(QString::fromStdString("no point selected"));
    }
}

void BodePlotWindow::paintEvent(QPaintEvent *event){



}

void BodePlotWindow::graphClicked(QCPAbstractPlottable *plottable, int dataIndex)
{
    std::cout<<"-----!!----"<<std::endl;
}

