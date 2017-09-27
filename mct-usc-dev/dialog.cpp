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
#include <QtGui>>
#include <QMessageBox>
#include <QtWidgets>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);


    //ui->numLineEdit->setValidator(new QDoubleValidator(-100, 100, 0, this));
    //ui->denomLineEdit->setValidator(new QDoubleValidator(-100, 100, 0, this));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_enterButton_clicked()
{
// Get user input values
    std::string numStringVal = ui->numLineEdit->text().toStdString();
    std::string denomStringVal = ui->denomLineEdit->text().toStdString();

    double n;

    numvec.clear();
    dnomvec.clear();

// This parses and checks datatype
    TrimString(numStringVal);
    TrimString(denomStringVal);
    std::istringstream iss (numStringVal);
    std::istringstream iss2 (denomStringVal);

    while(!iss.eof()){
        if (iss >> n)
        {
            numvec.push_back(n);
        }
        else // TODO: trailing space issue needs to be fixed
        {
            ui->tfNumLabel->setText("Char detected in num");
            return;
        }
    }

    while(!iss2.eof()){
        if (iss2 >> n)
        {
            dnomvec.push_back(n);
        }
        else // TODO: trailing space issues needs to be fixed
        {
            ui->tfDenLabel->setText("Char detected in denom");
            return;
        }
    }


// this prdoubles out vector to console for debugging
    // PrintVectors();


// Makes sure order of denominator is greater or equal to numerator "proper tf"
    if (dnomvec.size() < numvec.size()){
        ui->tfNumLabel->setText("Bad TF length");
        ui->tfDenLabel->setText("Bad TF length");
        return;
    }

// Passed all error checks, now updates tf label and string variables
    TFUpdate();

    QString qQuestionStr = QString::fromStdString("Confirm Transfer Function:\n" + numString + " / " + denomString);

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

    bw = new BodePlotWindow(/*this*/);
    bw->show();
}




}

void Dialog::PrintVectors()
{
    for (size_t i = 0; i < numvec.size(); i++){
        std::cout  << std::setprecision(3) << numvec[i] << std::setprecision(3) << " " ;
    }
    std::cout << std::endl;

    for (size_t i = 0; i < dnomvec.size(); i++){
        std::cout << dnomvec[i] << " ";
    }
    std::cout << std::endl;
}

// Function to set precision of TF
std::string Dialog::to_string_with_precision(float a_value, const int n)
{
    std::ostringstream out;
    out << std::setprecision(n) << a_value;
    return out.str();
}

void Dialog::TFUpdate(){
    int precisionConst = 4;
    numString.clear();
    denomString.clear();

    for (size_t i = 0; i < numvec.size(); i++)
    {
        int s = numvec.size() - 1 - i;

        // Formatting s
        if (s == 0)
        {
            numString += to_string_with_precision(numvec[i], precisionConst) + " + ";
        }
        else if (s == 1)
        {
            numString += to_string_with_precision(numvec[i], precisionConst) + "s" + " + ";
        }
        else
        {
            numString += to_string_with_precision(numvec[i], precisionConst) + "s^" + std::to_string(s) + " + ";
        }

        // Delete final +
        if (i == numvec.size() - 1)
        {
            numString.resize(numString.size() - 3);
        }
    }

    for (size_t i = 0; i < dnomvec.size(); i++)
    {
        int s = dnomvec.size() - 1 - i;
        // Formatting s
        if (s == 0)
        {
            denomString += to_string_with_precision(dnomvec[i], precisionConst) + " + ";
        }
        else if (s == 1)
        {
            denomString += to_string_with_precision(dnomvec[i], precisionConst) + "s" + " + ";
        }
        else
        {
            denomString += to_string_with_precision(dnomvec[i], precisionConst) + "s^" + std::to_string(s) + " + ";
        }

        // Delete final +
        if (i == dnomvec.size() - 1)
        {
            denomString.resize(denomString.size() - 3);
        }
    }

    ui->tfNumLabel->setText(QString::fromStdString(numString));
    ui->tfDenLabel->setText(QString::fromStdString(denomString));
}


void Dialog::TrimString(std::string& str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    str = str.substr(first, (last-first+1));
}
