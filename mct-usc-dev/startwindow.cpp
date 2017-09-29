#include "startwindow.h"
#include "ui_startwindow.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <QtCore>
#include <QMessageBox>
#include <QtWidgets>

#define PRECISIONCONST 4

// Construct with MathEngine
StartWindow::StartWindow(MathEngine* me) : ui(new Ui::StartWindow)
{

    this->me = me;
    ui->setupUi(this);

    numvec = me->getNum();
    dnomvec = me->getDenom();
    tfUpdate();
}

StartWindow::~StartWindow()
{
    delete ui;
}

// Checks if the user input is valid, if it is then it calls tfUpdate()
void StartWindow::on_enterButton_clicked()
{
    // Don't proceed unless input is valid
    if (parseInput() == false)
        return;

    QString qQuestionStr = QString::fromStdString("Confirm Transfer Function:\n" + me->getNumString() + " / " + me->getDenomString());

// QMessageBox to confirm if the TF has been entered correctly
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Transfer Function",
                      qQuestionStr , QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {

        // Open the Bode plot window and hide this window
        this->hide();

        bodewindow = new BodeWindow();
        bodewindow->show();

        me->getBpwPtr()->show();
        //BodePlotWindow* bw = new BodePlotWindow(me);
        //bw->show();
    }
}

// Checks if user input is valid or not, returns true/false
bool StartWindow::parseInput()
{
    bool returnVal = true;

    // Get user input values
    std::string numStringVal = ui->numLineEdit->text().toStdString();
    std::string denomStringVal = ui->denomLineEdit->text().toStdString();
    double n;
    numvec.clear();
    dnomvec.clear();

    // This parses and checks datatype
    trimString(numStringVal);
    trimString(denomStringVal);
    std::istringstream iss (numStringVal);
    std::istringstream iss2 (denomStringVal);

    while(!iss.eof()){
        if (iss >> n)
        {
            numvec.push_back(n);
        }
        else
        {
            ui->tfNumLabel->setText("Char detected in num");
            returnVal = false;
        }
    }

    while(!iss2.eof()){
        if (iss2 >> n)
        {
            dnomvec.push_back(n);
        }
        else
        {
            ui->tfDenLabel->setText("Char detected in denom");
            returnVal = false;
        }
    }



    // Makes sure order of denominator is greater or equal to numerator "proper tf"
    if (dnomvec.size() < numvec.size()){
        ui->tfNumLabel->setText("Bad TF length");
        ui->tfDenLabel->setText("Bad TF length");
        returnVal = false;
    }

    // Passed all error checks, now updates tf label and string variables
    if (returnVal == true)
    {
        tfUpdate();// Get user input values
    }

    return returnVal;

}

// Pass tf to mathengine and update the label
void StartWindow::tfUpdate()
{
    // Update the engine data
    me->setTf(numvec, dnomvec);
    ui->tfNumLabel->setText(QString::fromStdString(me->getNumString()));
    ui->tfDenLabel->setText(QString::fromStdString(me->getDenomString()));

}

// Trim whitespace
void StartWindow::trimString(std::string& str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    str = str.substr(first, (last-first+1));
}
