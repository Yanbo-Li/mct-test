/********************************************************************************
** Form generated from reading UI file 'controlsystemwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLSYSTEMWINDOW_H
#define UI_CONTROLSYSTEMWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_ControlSystemWindow
{
public:
    QTabWidget *BodePlot;
    QWidget *tab;
    QCustomPlot *magnitudePlot;
    QCustomPlot *phasePlot;
    QLabel *tfLabel;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *backButton;
    QPushButton *plotButton;
    QPushButton *saveButton;
    QTabWidget *RootLocus;
    QWidget *tab_3;
    QCustomPlot *rootlocusPlot;
    QTabWidget *StepResponse;
    QWidget *tab_5;
    QCustomPlot *stepresponsePlot;

    void setupUi(QWidget *ControlSystemWindow)
    {
        if (ControlSystemWindow->objectName().isEmpty())
            ControlSystemWindow->setObjectName(QStringLiteral("ControlSystemWindow"));
        ControlSystemWindow->resize(1000, 900);
        BodePlot = new QTabWidget(ControlSystemWindow);
        BodePlot->setObjectName(QStringLiteral("BodePlot"));
        BodePlot->setGeometry(QRect(9, 0, 460, 431));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        magnitudePlot = new QCustomPlot(tab);
        magnitudePlot->setObjectName(QStringLiteral("magnitudePlot"));
        magnitudePlot->setGeometry(QRect(0, 0, 451, 200));
        phasePlot = new QCustomPlot(tab);
        phasePlot->setObjectName(QStringLiteral("phasePlot"));
        phasePlot->setGeometry(QRect(0, 200, 451, 200));
        phasePlot->setContextMenuPolicy(Qt::DefaultContextMenu);
        BodePlot->addTab(tab, QString());
        tfLabel = new QLabel(ControlSystemWindow);
        tfLabel->setObjectName(QStringLiteral("tfLabel"));
        tfLabel->setGeometry(QRect(430, 650, 136, 16));
        tfLabel->setMaximumSize(QSize(1000, 20));
        tfLabel->setAlignment(Qt::AlignCenter);
        layoutWidget = new QWidget(ControlSystemWindow);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(160, 690, 651, 51));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        backButton = new QPushButton(layoutWidget);
        backButton->setObjectName(QStringLiteral("backButton"));

        horizontalLayout->addWidget(backButton);

        plotButton = new QPushButton(layoutWidget);
        plotButton->setObjectName(QStringLiteral("plotButton"));

        horizontalLayout->addWidget(plotButton);

        saveButton = new QPushButton(layoutWidget);
        saveButton->setObjectName(QStringLiteral("saveButton"));

        horizontalLayout->addWidget(saveButton);

        RootLocus = new QTabWidget(ControlSystemWindow);
        RootLocus->setObjectName(QStringLiteral("RootLocus"));
        RootLocus->setGeometry(QRect(530, 0, 451, 301));
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        rootlocusPlot = new QCustomPlot(tab_3);
        rootlocusPlot->setObjectName(QStringLiteral("rootlocusPlot"));
        rootlocusPlot->setGeometry(QRect(0, 0, 441, 271));
        RootLocus->addTab(tab_3, QString());
        StepResponse = new QTabWidget(ControlSystemWindow);
        StepResponse->setObjectName(QStringLiteral("StepResponse"));
        StepResponse->setGeometry(QRect(530, 300, 451, 301));
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        stepresponsePlot = new QCustomPlot(tab_5);
        stepresponsePlot->setObjectName(QStringLiteral("stepresponsePlot"));
        stepresponsePlot->setGeometry(QRect(0, 0, 441, 271));
        StepResponse->addTab(tab_5, QString());

        retranslateUi(ControlSystemWindow);

        BodePlot->setCurrentIndex(0);
        RootLocus->setCurrentIndex(0);
        StepResponse->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ControlSystemWindow);
    } // setupUi

    void retranslateUi(QWidget *ControlSystemWindow)
    {
        ControlSystemWindow->setWindowTitle(QApplication::translate("ControlSystemWindow", "ControlSystemDesinger", Q_NULLPTR));
        BodePlot->setTabText(BodePlot->indexOf(tab), QApplication::translate("ControlSystemWindow", "Bode Plot", Q_NULLPTR));
        tfLabel->setText(QApplication::translate("ControlSystemWindow", "Transfer Function", Q_NULLPTR));
        backButton->setText(QApplication::translate("ControlSystemWindow", "Go Back", Q_NULLPTR));
        plotButton->setText(QApplication::translate("ControlSystemWindow", "Plot", Q_NULLPTR));
        saveButton->setText(QApplication::translate("ControlSystemWindow", "Save Controller", Q_NULLPTR));
        RootLocus->setTabText(RootLocus->indexOf(tab_3), QApplication::translate("ControlSystemWindow", "Root Locus", Q_NULLPTR));
        StepResponse->setTabText(StepResponse->indexOf(tab_5), QApplication::translate("ControlSystemWindow", "Step Response", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ControlSystemWindow: public Ui_ControlSystemWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLSYSTEMWINDOW_H
