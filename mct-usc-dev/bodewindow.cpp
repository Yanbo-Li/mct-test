#include "bodewindow.h"
#include <QtWidgets>
#include "sliders.h"

BodeWindow::BodeWindow()
{
    horizontalSliders = new Sliders(tr("Slider"));

    createControls(tr("Controls"));

    connect(horizontalSliders, SIGNAL(valueChanged(int)),
            valueSpinBox, SLOT(setValue(int)));
    connect(valueSpinBox, SIGNAL(valueChanged(int)),
            horizontalSliders, SLOT(setValue(int)));

    // the entire widget is QHBoxLayout
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(controlsGroup);
    layout->addWidget(horizontalSliders);
    setLayout(layout);

    minimumSpinBox->setValue(0);
    maximumSpinBox->setValue(20);
    valueSpinBox->setValue(10);

    setWindowTitle(tr("Bode Plot"));

// Imported from Ali's code, main.cpp
    /*
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
     */
}

void BodeWindow::createControls(const QString &title)
{
    controlsGroup = new QGroupBox(title);

    minimumLabel = new QLabel(tr("Minimum value:"));
    maximumLabel = new QLabel(tr("Maximum value:"));
    valueLabel = new QLabel(tr("Current value:"));

    minimumSpinBox = new QSpinBox;
    minimumSpinBox->setRange(-100, 100);
    minimumSpinBox->setSingleStep(1);

    maximumSpinBox = new QSpinBox;
    maximumSpinBox->setRange(-100, 100);
    maximumSpinBox->setSingleStep(1);

    valueSpinBox = new QSpinBox;
    valueSpinBox->setRange(-100, 100);
    valueSpinBox->setSingleStep(1);

    connect(minimumSpinBox, SIGNAL(valueChanged(int)),
            horizontalSliders, SLOT(setMinimum(int)));
    connect(maximumSpinBox, SIGNAL(valueChanged(int)),
            horizontalSliders, SLOT(setMaximum(int)));

// Will probably have to be adjusted once we put the graph in
    // Using a QGridLayout for sliders
    QGridLayout *controlsLayout = new QGridLayout;
    controlsLayout->addWidget(minimumLabel, 0, 0);
    controlsLayout->addWidget(maximumLabel, 1, 0);
    controlsLayout->addWidget(valueLabel, 2, 0);
    controlsLayout->addWidget(minimumSpinBox, 0, 1);
    controlsLayout->addWidget(maximumSpinBox, 1, 1);
    controlsLayout->addWidget(valueSpinBox, 2, 1);
    controlsGroup->setLayout(controlsLayout);
}
