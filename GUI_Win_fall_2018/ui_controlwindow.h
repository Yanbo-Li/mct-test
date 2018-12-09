/********************************************************************************
** Form generated from reading UI file 'controlwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLWINDOW_H
#define UI_CONTROLWINDOW_H

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

class Ui_ControlWindow
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *outerVLayout;
    QVBoxLayout *topHLayout;
    QLabel *tfLabel;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *kVLayout;
    QLabel *kpLabel;
    QLabel *kdLabel;
    QLabel *kiLabel;
    QVBoxLayout *lineEditVLayout;
    QDoubleSpinBox *kpValBox;
    QDoubleSpinBox *kdValBox;
    QDoubleSpinBox *kiValBox;
    QVBoxLayout *minBoxVLayout;
    QDoubleSpinBox *kpMinBox;
    QDoubleSpinBox *kdMinBox;
    QDoubleSpinBox *kiMinBox;
    QVBoxLayout *sliderVLayout;
    QSlider *kpSlider;
    QSlider *kdSlider;
    QSlider *kiSlider;
    QVBoxLayout *maxBoxVLayout;
    QDoubleSpinBox *kdMaxBox;
    QDoubleSpinBox *kiMaxBox;
    QDoubleSpinBox *kpMaxBox;
    QHBoxLayout *buttonHLayout;
    QPushButton *backButton;
    QPushButton *plotButton;
    QPushButton *saveButton;
    QCustomPlot *stepPlot;
    QCustomPlot *rootLocusPlot;
    QLabel *tfLabel_2;
    QLabel *tfLabel_3;

    void setupUi(QWidget *ControlWindow)
    {
        if (ControlWindow->objectName().isEmpty())
            ControlWindow->setObjectName(QStringLiteral("ControlWindow"));
        ControlWindow->resize(971, 707);
        layoutWidget = new QWidget(ControlWindow);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(120, 510, 701, 191));
        outerVLayout = new QVBoxLayout(layoutWidget);
        outerVLayout->setObjectName(QStringLiteral("outerVLayout"));
        outerVLayout->setContentsMargins(0, 0, 0, 0);
        topHLayout = new QVBoxLayout();
        topHLayout->setObjectName(QStringLiteral("topHLayout"));
        tfLabel = new QLabel(layoutWidget);
        tfLabel->setObjectName(QStringLiteral("tfLabel"));
        tfLabel->setMaximumSize(QSize(1000, 20));
        tfLabel->setAlignment(Qt::AlignCenter);

        topHLayout->addWidget(tfLabel);


        outerVLayout->addLayout(topHLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        kVLayout = new QVBoxLayout();
        kVLayout->setObjectName(QStringLiteral("kVLayout"));
        kpLabel = new QLabel(layoutWidget);
        kpLabel->setObjectName(QStringLiteral("kpLabel"));
        kpLabel->setMaximumSize(QSize(75, 20));
        kpLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        kVLayout->addWidget(kpLabel);

        kdLabel = new QLabel(layoutWidget);
        kdLabel->setObjectName(QStringLiteral("kdLabel"));
        kdLabel->setMaximumSize(QSize(75, 20));
        kdLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        kVLayout->addWidget(kdLabel);

        kiLabel = new QLabel(layoutWidget);
        kiLabel->setObjectName(QStringLiteral("kiLabel"));
        kiLabel->setMaximumSize(QSize(75, 20));
        kiLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        kVLayout->addWidget(kiLabel);


        horizontalLayout->addLayout(kVLayout);

        lineEditVLayout = new QVBoxLayout();
        lineEditVLayout->setObjectName(QStringLiteral("lineEditVLayout"));
        lineEditVLayout->setContentsMargins(0, -1, 0, -1);
        kpValBox = new QDoubleSpinBox(layoutWidget);
        kpValBox->setObjectName(QStringLiteral("kpValBox"));
        kpValBox->setMaximumSize(QSize(16777215, 20));

        lineEditVLayout->addWidget(kpValBox);

        kdValBox = new QDoubleSpinBox(layoutWidget);
        kdValBox->setObjectName(QStringLiteral("kdValBox"));
        kdValBox->setMaximumSize(QSize(16777215, 20));

        lineEditVLayout->addWidget(kdValBox);

        kiValBox = new QDoubleSpinBox(layoutWidget);
        kiValBox->setObjectName(QStringLiteral("kiValBox"));
        kiValBox->setMaximumSize(QSize(16777215, 20));

        lineEditVLayout->addWidget(kiValBox);


        horizontalLayout->addLayout(lineEditVLayout);

        minBoxVLayout = new QVBoxLayout();
        minBoxVLayout->setObjectName(QStringLiteral("minBoxVLayout"));
        kpMinBox = new QDoubleSpinBox(layoutWidget);
        kpMinBox->setObjectName(QStringLiteral("kpMinBox"));
        kpMinBox->setMaximumSize(QSize(16777215, 20));

        minBoxVLayout->addWidget(kpMinBox);

        kdMinBox = new QDoubleSpinBox(layoutWidget);
        kdMinBox->setObjectName(QStringLiteral("kdMinBox"));
        kdMinBox->setMaximumSize(QSize(16777215, 20));

        minBoxVLayout->addWidget(kdMinBox);

        kiMinBox = new QDoubleSpinBox(layoutWidget);
        kiMinBox->setObjectName(QStringLiteral("kiMinBox"));
        kiMinBox->setMaximumSize(QSize(16777215, 20));

        minBoxVLayout->addWidget(kiMinBox);


        horizontalLayout->addLayout(minBoxVLayout);

        sliderVLayout = new QVBoxLayout();
        sliderVLayout->setObjectName(QStringLiteral("sliderVLayout"));
        kpSlider = new QSlider(layoutWidget);
        kpSlider->setObjectName(QStringLiteral("kpSlider"));
        kpSlider->setMaximumSize(QSize(16777215, 20));
        kpSlider->setOrientation(Qt::Horizontal);

        sliderVLayout->addWidget(kpSlider);

        kdSlider = new QSlider(layoutWidget);
        kdSlider->setObjectName(QStringLiteral("kdSlider"));
        kdSlider->setMaximumSize(QSize(16777215, 20));
        kdSlider->setOrientation(Qt::Horizontal);

        sliderVLayout->addWidget(kdSlider);

        kiSlider = new QSlider(layoutWidget);
        kiSlider->setObjectName(QStringLiteral("kiSlider"));
        kiSlider->setMaximumSize(QSize(16777215, 20));
        kiSlider->setOrientation(Qt::Horizontal);

        sliderVLayout->addWidget(kiSlider);


        horizontalLayout->addLayout(sliderVLayout);

        maxBoxVLayout = new QVBoxLayout();
        maxBoxVLayout->setObjectName(QStringLiteral("maxBoxVLayout"));
        kdMaxBox = new QDoubleSpinBox(layoutWidget);
        kdMaxBox->setObjectName(QStringLiteral("kdMaxBox"));
        kdMaxBox->setMaximumSize(QSize(16777215, 20));

        maxBoxVLayout->addWidget(kdMaxBox);

        kiMaxBox = new QDoubleSpinBox(layoutWidget);
        kiMaxBox->setObjectName(QStringLiteral("kiMaxBox"));
        kiMaxBox->setMaximumSize(QSize(16777215, 20));

        maxBoxVLayout->addWidget(kiMaxBox);

        kpMaxBox = new QDoubleSpinBox(layoutWidget);
        kpMaxBox->setObjectName(QStringLiteral("kpMaxBox"));
        kpMaxBox->setMaximumSize(QSize(16777215, 20));

        maxBoxVLayout->addWidget(kpMaxBox);


        horizontalLayout->addLayout(maxBoxVLayout);

        horizontalLayout->setStretch(3, 2);

        outerVLayout->addLayout(horizontalLayout);

        buttonHLayout = new QHBoxLayout();
        buttonHLayout->setObjectName(QStringLiteral("buttonHLayout"));
        backButton = new QPushButton(layoutWidget);
        backButton->setObjectName(QStringLiteral("backButton"));

        buttonHLayout->addWidget(backButton);

        plotButton = new QPushButton(layoutWidget);
        plotButton->setObjectName(QStringLiteral("plotButton"));

        buttonHLayout->addWidget(plotButton);

        saveButton = new QPushButton(layoutWidget);
        saveButton->setObjectName(QStringLiteral("saveButton"));

        buttonHLayout->addWidget(saveButton);


        outerVLayout->addLayout(buttonHLayout);

        stepPlot = new QCustomPlot(ControlWindow);
        stepPlot->setObjectName(QStringLiteral("stepPlot"));
        stepPlot->setGeometry(QRect(0, 29, 480, 451));
        rootLocusPlot = new QCustomPlot(ControlWindow);
        rootLocusPlot->setObjectName(QStringLiteral("rootLocusPlot"));
        rootLocusPlot->setGeometry(QRect(490, 29, 480, 451));
        tfLabel_2 = new QLabel(ControlWindow);
        tfLabel_2->setObjectName(QStringLiteral("tfLabel_2"));
        tfLabel_2->setGeometry(QRect(0, 10, 481, 20));
        tfLabel_2->setMaximumSize(QSize(1000, 20));
        tfLabel_2->setAlignment(Qt::AlignCenter);
        tfLabel_3 = new QLabel(ControlWindow);
        tfLabel_3->setObjectName(QStringLiteral("tfLabel_3"));
        tfLabel_3->setGeometry(QRect(490, 10, 481, 20));
        tfLabel_3->setMaximumSize(QSize(1000, 20));
        tfLabel_3->setAlignment(Qt::AlignCenter);
        stepPlot->raise();
        rootLocusPlot->raise();
        layoutWidget->raise();
        tfLabel_2->raise();
        tfLabel_3->raise();

        retranslateUi(ControlWindow);

        QMetaObject::connectSlotsByName(ControlWindow);
    } // setupUi

    void retranslateUi(QWidget *ControlWindow)
    {
        ControlWindow->setWindowTitle(QApplication::translate("ControlWindow", "ControlWindow", Q_NULLPTR));
        tfLabel->setText(QApplication::translate("ControlWindow", "Transfer Function", Q_NULLPTR));
        kpLabel->setText(QApplication::translate("ControlWindow", "Kp", Q_NULLPTR));
        kdLabel->setText(QApplication::translate("ControlWindow", "Kd", Q_NULLPTR));
        kiLabel->setText(QApplication::translate("ControlWindow", "Ki", Q_NULLPTR));
        backButton->setText(QApplication::translate("ControlWindow", "Go Back", Q_NULLPTR));
        plotButton->setText(QApplication::translate("ControlWindow", "Plot", Q_NULLPTR));
        saveButton->setText(QApplication::translate("ControlWindow", "Save Controller", Q_NULLPTR));
        tfLabel_2->setText(QApplication::translate("ControlWindow", "Step Response", Q_NULLPTR));
        tfLabel_3->setText(QApplication::translate("ControlWindow", "Root Locus", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ControlWindow: public Ui_ControlWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLWINDOW_H
