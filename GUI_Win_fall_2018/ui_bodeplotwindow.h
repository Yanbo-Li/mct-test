/********************************************************************************
** Form generated from reading UI file 'bodeplotwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BODEPLOTWINDOW_H
#define UI_BODEPLOTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_BodePlotWindow
{
public:
    QWidget *centralWidget;
    QCustomPlot *customPlot;
    QWidget *layoutWidget;
    QVBoxLayout *outerVLayout;
    QLabel *xyLabel;
    QVBoxLayout *topHLayout;
    QLabel *tfLabel;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *zetaLabel;
    QLabel *omegaLabel;
    QVBoxLayout *verticalLayout_2;
    QDoubleSpinBox *zetaValSpinBox;
    QDoubleSpinBox *omegaValSpinBox;
    QVBoxLayout *verticalLayout_3;
    QDoubleSpinBox *zetaMinSpinBox;
    QDoubleSpinBox *omegaMinSpinBox;
    QVBoxLayout *verticalLayout_4;
    QSlider *zetaSlider;
    QSlider *omegaSlider;
    QVBoxLayout *verticalLayout_5;
    QDoubleSpinBox *zetaMaxSpinBox;
    QDoubleSpinBox *omegaMaxSpinBox;
    QHBoxLayout *buttonHLayout;
    QPushButton *backButton;
    QPushButton *plotButton;
    QPushButton *confirmButton;
    QPushButton *upButton;

    void setupUi(QWidget *BodePlotWindow)
    {
        if (BodePlotWindow->objectName().isEmpty())
            BodePlotWindow->setObjectName(QStringLiteral("BodePlotWindow"));
        BodePlotWindow->resize(655, 644);
        centralWidget = new QWidget(BodePlotWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setGeometry(QRect(0, 0, 651, 641));
        customPlot = new QCustomPlot(centralWidget);
        customPlot->setObjectName(QStringLiteral("customPlot"));
        customPlot->setGeometry(QRect(80, 0, 480, 480));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 490, 619, 150));
        outerVLayout = new QVBoxLayout(layoutWidget);
        outerVLayout->setSpacing(6);
        outerVLayout->setContentsMargins(11, 11, 11, 11);
        outerVLayout->setObjectName(QStringLiteral("outerVLayout"));
        outerVLayout->setContentsMargins(0, 0, 0, 0);
        xyLabel = new QLabel(layoutWidget);
        xyLabel->setObjectName(QStringLiteral("xyLabel"));
        xyLabel->setAlignment(Qt::AlignCenter);

        outerVLayout->addWidget(xyLabel);

        topHLayout = new QVBoxLayout();
        topHLayout->setSpacing(6);
        topHLayout->setObjectName(QStringLiteral("topHLayout"));
        tfLabel = new QLabel(layoutWidget);
        tfLabel->setObjectName(QStringLiteral("tfLabel"));
        tfLabel->setMaximumSize(QSize(1000, 20));
        tfLabel->setAlignment(Qt::AlignCenter);

        topHLayout->addWidget(tfLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        zetaLabel = new QLabel(layoutWidget);
        zetaLabel->setObjectName(QStringLiteral("zetaLabel"));
        zetaLabel->setMaximumSize(QSize(75, 20));
        zetaLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(zetaLabel);

        omegaLabel = new QLabel(layoutWidget);
        omegaLabel->setObjectName(QStringLiteral("omegaLabel"));
        omegaLabel->setMaximumSize(QSize(75, 20));
        omegaLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(omegaLabel);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        zetaValSpinBox = new QDoubleSpinBox(layoutWidget);
        zetaValSpinBox->setObjectName(QStringLiteral("zetaValSpinBox"));
        zetaValSpinBox->setMaximumSize(QSize(16777215, 20));

        verticalLayout_2->addWidget(zetaValSpinBox);

        omegaValSpinBox = new QDoubleSpinBox(layoutWidget);
        omegaValSpinBox->setObjectName(QStringLiteral("omegaValSpinBox"));
        omegaValSpinBox->setMaximumSize(QSize(16777215, 20));

        verticalLayout_2->addWidget(omegaValSpinBox);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        zetaMinSpinBox = new QDoubleSpinBox(layoutWidget);
        zetaMinSpinBox->setObjectName(QStringLiteral("zetaMinSpinBox"));
        zetaMinSpinBox->setMaximumSize(QSize(16777215, 20));

        verticalLayout_3->addWidget(zetaMinSpinBox);

        omegaMinSpinBox = new QDoubleSpinBox(layoutWidget);
        omegaMinSpinBox->setObjectName(QStringLiteral("omegaMinSpinBox"));
        omegaMinSpinBox->setMaximumSize(QSize(16777215, 20));

        verticalLayout_3->addWidget(omegaMinSpinBox);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        zetaSlider = new QSlider(layoutWidget);
        zetaSlider->setObjectName(QStringLiteral("zetaSlider"));
        zetaSlider->setMaximumSize(QSize(16777215, 20));
        zetaSlider->setOrientation(Qt::Horizontal);

        verticalLayout_4->addWidget(zetaSlider);

        omegaSlider = new QSlider(layoutWidget);
        omegaSlider->setObjectName(QStringLiteral("omegaSlider"));
        omegaSlider->setMaximumSize(QSize(16777215, 20));
        omegaSlider->setOrientation(Qt::Horizontal);

        verticalLayout_4->addWidget(omegaSlider);


        horizontalLayout->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        zetaMaxSpinBox = new QDoubleSpinBox(layoutWidget);
        zetaMaxSpinBox->setObjectName(QStringLiteral("zetaMaxSpinBox"));
        zetaMaxSpinBox->setMaximumSize(QSize(16777215, 20));

        verticalLayout_5->addWidget(zetaMaxSpinBox);

        omegaMaxSpinBox = new QDoubleSpinBox(layoutWidget);
        omegaMaxSpinBox->setObjectName(QStringLiteral("omegaMaxSpinBox"));
        omegaMaxSpinBox->setMaximumSize(QSize(16777215, 20));

        verticalLayout_5->addWidget(omegaMaxSpinBox);


        horizontalLayout->addLayout(verticalLayout_5);

        horizontalLayout->setStretch(3, 1);

        topHLayout->addLayout(horizontalLayout);


        outerVLayout->addLayout(topHLayout);

        buttonHLayout = new QHBoxLayout();
        buttonHLayout->setSpacing(6);
        buttonHLayout->setObjectName(QStringLiteral("buttonHLayout"));
        backButton = new QPushButton(layoutWidget);
        backButton->setObjectName(QStringLiteral("backButton"));

        buttonHLayout->addWidget(backButton);

        plotButton = new QPushButton(layoutWidget);
        plotButton->setObjectName(QStringLiteral("plotButton"));

        buttonHLayout->addWidget(plotButton);

        confirmButton = new QPushButton(layoutWidget);
        confirmButton->setObjectName(QStringLiteral("confirmButton"));

        buttonHLayout->addWidget(confirmButton);


        outerVLayout->addLayout(buttonHLayout);

        upButton = new QPushButton(centralWidget);
        upButton->setObjectName(QStringLiteral("upButton"));
        upButton->setGeometry(QRect(10, 350, 51, 31));

        retranslateUi(BodePlotWindow);

        QMetaObject::connectSlotsByName(BodePlotWindow);
    } // setupUi

    void retranslateUi(QWidget *BodePlotWindow)
    {
        BodePlotWindow->setWindowTitle(QApplication::translate("BodePlotWindow", "BodePlotWindow", Q_NULLPTR));
        xyLabel->setText(QApplication::translate("BodePlotWindow", "xy Label", Q_NULLPTR));
        tfLabel->setText(QApplication::translate("BodePlotWindow", "Transfer Function", Q_NULLPTR));
        zetaLabel->setText(QApplication::translate("BodePlotWindow", "zeta", Q_NULLPTR));
        omegaLabel->setText(QApplication::translate("BodePlotWindow", "omega", Q_NULLPTR));
        backButton->setText(QApplication::translate("BodePlotWindow", "Go Back", Q_NULLPTR));
        plotButton->setText(QApplication::translate("BodePlotWindow", "Plot", Q_NULLPTR));
        confirmButton->setText(QApplication::translate("BodePlotWindow", "Confirm", Q_NULLPTR));
        upButton->setText(QApplication::translate("BodePlotWindow", "Up", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BodePlotWindow: public Ui_BodePlotWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BODEPLOTWINDOW_H
