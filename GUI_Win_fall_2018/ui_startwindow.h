/********************************************************************************
** Form generated from reading UI file 'startwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTWINDOW_H
#define UI_STARTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartWindow
{
public:
    QLabel *gsLabel;
    QWidget *layoutWidget;
    QVBoxLayout *topLayout;
    QLabel *titleLabel;
    QHBoxLayout *horizLayout;
    QVBoxLayout *NDLayout;
    QLabel *numLabel;
    QLabel *denomLabel;
    QVBoxLayout *textBoxLayout;
    QLineEdit *numLineEdit;
    QLineEdit *denomLineEdit;
    QWidget *layoutWidget1;
    QVBoxLayout *botLayout;
    QLabel *tfNumLabel;
    QFrame *line;
    QLabel *tfDenLabel;
    QPushButton *enterButton;

    void setupUi(QWidget *StartWindow)
    {
        if (StartWindow->objectName().isEmpty())
            StartWindow->setObjectName(QStringLiteral("StartWindow"));
        StartWindow->resize(635, 442);
        gsLabel = new QLabel(StartWindow);
        gsLabel->setObjectName(QStringLiteral("gsLabel"));
        gsLabel->setGeometry(QRect(90, 230, 51, 31));
        layoutWidget = new QWidget(StartWindow);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 30, 578, 151));
        topLayout = new QVBoxLayout(layoutWidget);
        topLayout->setObjectName(QStringLiteral("topLayout"));
        topLayout->setContentsMargins(0, 0, 0, 0);
        titleLabel = new QLabel(layoutWidget);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));
        titleLabel->setTextFormat(Qt::AutoText);

        topLayout->addWidget(titleLabel);

        horizLayout = new QHBoxLayout();
        horizLayout->setObjectName(QStringLiteral("horizLayout"));
        NDLayout = new QVBoxLayout();
        NDLayout->setObjectName(QStringLiteral("NDLayout"));
        numLabel = new QLabel(layoutWidget);
        numLabel->setObjectName(QStringLiteral("numLabel"));

        NDLayout->addWidget(numLabel);

        denomLabel = new QLabel(layoutWidget);
        denomLabel->setObjectName(QStringLiteral("denomLabel"));

        NDLayout->addWidget(denomLabel);


        horizLayout->addLayout(NDLayout);

        textBoxLayout = new QVBoxLayout();
        textBoxLayout->setObjectName(QStringLiteral("textBoxLayout"));
        numLineEdit = new QLineEdit(layoutWidget);
        numLineEdit->setObjectName(QStringLiteral("numLineEdit"));

        textBoxLayout->addWidget(numLineEdit);

        denomLineEdit = new QLineEdit(layoutWidget);
        denomLineEdit->setObjectName(QStringLiteral("denomLineEdit"));

        textBoxLayout->addWidget(denomLineEdit);


        horizLayout->addLayout(textBoxLayout);


        topLayout->addLayout(horizLayout);

        layoutWidget1 = new QWidget(StartWindow);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(160, 200, 331, 100));
        botLayout = new QVBoxLayout(layoutWidget1);
        botLayout->setObjectName(QStringLiteral("botLayout"));
        botLayout->setContentsMargins(0, 0, 0, 0);
        tfNumLabel = new QLabel(layoutWidget1);
        tfNumLabel->setObjectName(QStringLiteral("tfNumLabel"));

        botLayout->addWidget(tfNumLabel);

        line = new QFrame(layoutWidget1);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        botLayout->addWidget(line);

        tfDenLabel = new QLabel(layoutWidget1);
        tfDenLabel->setObjectName(QStringLiteral("tfDenLabel"));

        botLayout->addWidget(tfDenLabel);

        enterButton = new QPushButton(layoutWidget1);
        enterButton->setObjectName(QStringLiteral("enterButton"));

        botLayout->addWidget(enterButton);

        layoutWidget->raise();
        layoutWidget->raise();
        gsLabel->raise();

        retranslateUi(StartWindow);

        QMetaObject::connectSlotsByName(StartWindow);
    } // setupUi

    void retranslateUi(QWidget *StartWindow)
    {
        StartWindow->setWindowTitle(QApplication::translate("StartWindow", "StartWindow", Q_NULLPTR));
        gsLabel->setText(QApplication::translate("StartWindow", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:600;\">G(s) =</span></p></body></html>", Q_NULLPTR));
        titleLabel->setText(QApplication::translate("StartWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:18pt; font-weight:600;\">Enter Transfer Function Coefficients</span></p></body></html>", Q_NULLPTR));
        numLabel->setText(QApplication::translate("StartWindow", "N", Q_NULLPTR));
        denomLabel->setText(QApplication::translate("StartWindow", "D", Q_NULLPTR));
        tfNumLabel->setText(QString());
        tfDenLabel->setText(QString());
        enterButton->setText(QApplication::translate("StartWindow", "Enter", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class StartWindow: public Ui_StartWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTWINDOW_H
