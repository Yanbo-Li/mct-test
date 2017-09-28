#include "dialog.h"
#include "ui_dialog.h"
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

Dialog::Dialog(MathEngine* me) : ui(new Ui::Dialog)
{

    this->me = me;
    ui->setupUi(this);

    // For when user returns back to dialog screen from bodeplotwindow
    // Re-populates fields;
    if (me->getNum().size() > 0 && me->getDenom().size() > 0)
    {

        std::string numString, denomString;
        for (size_t i = 0; i < me->getNum().size(); i++)
        {
            numString += me->to_string_with_precision(me->getNum()[i], PRECISIONCONST) + " ";
        }

        for (size_t i = 0; i < me->getDenom().size(); i++)
        {
            denomString += me->to_string_with_precision(me->getDenom()[i], PRECISIONCONST) + " ";
        }

        ui->numLineEdit->setText(QString::fromStdString(numString));
        ui->denomLineEdit->setText(QString::fromStdString(denomString));
    }

    numvec = me->getNum();
    dnomvec = me->getDenom();
    tfUpdate();

}

Dialog::~Dialog()
{
    delete ui;
}

// Checks if the user input is valid, if it is then it calls tfUpdate()
void Dialog::on_enterButton_clicked()
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

        BodePlotWindow* bw = new BodePlotWindow(me);
        bw->show();
    }
}

bool Dialog::parseInput()
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

// Function to set precision of TF
std::string Dialog::to_string_with_precision(float a_value, const int n)
{
    std::ostringstream out;
    out << std::setprecision(n) << a_value;
    return out.str();
}

// Pass tf to mathengine and update the label
void Dialog::tfUpdate()
{
    // Update the engine data
    me->setTf(numvec, dnomvec);
    ui->tfNumLabel->setText(QString::fromStdString(me->getNumString()));
    ui->tfDenLabel->setText(QString::fromStdString(me->getDenomString()));

}


void Dialog::trimString(std::string& str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    str = str.substr(first, (last-first+1));
}
