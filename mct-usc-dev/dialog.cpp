#include "dialog.h"
#include "ui_dialog.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
//using namespace std;

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

// Passed all error checks, now updates tf label
    TFUpdate();


}

void Dialog::PrintVectors()
{
    for (size_t i = 0; i < numvec.size(); i++){
        std::cout << numvec[i] << " ";
    }
    std::cout << std::endl;

    for (size_t i = 0; i < dnomvec.size(); i++){
        std::cout << dnomvec[i] << " ";
    }
    std::cout << std::endl;
}

void Dialog::TFUpdate(){
    std::string numString, denomString;
    for (size_t i = 0; i < numvec.size(); i++)
    {
        int s = numvec.size() - 1 - i;

        // Formatting s
        if (s == 0)
        {
            numString += std::to_string(numvec[i]) + " + ";
        }
        else if (s == 1)
        {
            numString += std::to_string(numvec[i]) + "s" + " + ";
        }
        else
        {
            numString += std::to_string(numvec[i]) + "s^" + std::to_string(s) + " + ";
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
            denomString += std::to_string(dnomvec[i]) + " + ";
        }
        else if (s == 1)
        {
            denomString += std::to_string(dnomvec[i]) + "s" + " + ";
        }
        else
        {
            denomString += std::to_string(dnomvec[i]) + "s^" + std::to_string(s) + " + ";
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
