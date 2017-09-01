#include "dialog.h"
#include "ui_dialog.h"
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

    QFont f("Arial", 16, QFont::Bold);
    ui->titleLabel -> setFont(f);

    //ui->numLineEdit->setValidator(new QDoubleValidator(-100, 100, 0, this));
    //ui->denomLineEdit->setValidator(new QDoubleValidator(-100, 100, 0, this));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_enterButton_clicked()
{

    // Error checking

    // correct spacing & number of int arguments
        // use stringstream to parse
    std::string numStringVal = ui->numLineEdit->text().toStdString();
    std::string denomStringVal = ui->denomLineEdit->text().toStdString();
    std::istringstream iss (numStringVal);
    std::istringstream iss2 (denomStringVal);
    int n;
    std::vector<int> numvec;
    std::vector<int> dnomvec;
// This parses and checks datatype
    while(!iss.eof()){
        if (iss >> n)
        {
            numvec.push_back(n);
        }
        else // TODO: trailing space issue needs to be fixed
        {
            ui->tfLabel->setText("Char detected in num");
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
            ui->tfLabel->setText("Char detected in denom");
            return;
        }
    }


// this prints out vector to console for debugging
    for (int i = 0; i < numvec.size(); i++){
        std::cout << numvec[i] << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < dnomvec.size(); i++){
        std::cout << dnomvec[i] << " ";
    }
    std::cout << std::endl;

// Makes sure order of denominator is greater or equal to numerator "proper tf"
    if (dnomvec.size() < numvec.size()){
        ui->tfLabel->setText("Bad TF length");
        return;
    }

// Passed all error checks, now updates tf label
    std::string numString, denomString;
    for (int i = 0; i < numvec.size(); i++)
    {
        int s = numvec.size() - 1 - i;
        numString += std::to_string(numvec[i]) + "s^" + std::to_string(s) + " + ";
    }
    for (int i = 0; i < dnomvec.size(); i++)
    {
        int s = dnomvec.size() - 1 - i;
        denomString += std::to_string(dnomvec[i]) + "s^" + std::to_string(s) + " + ";
    }

    ui->tfLabel->setText(QString::fromStdString(numString) + " / " + QString::fromStdString(denomString));

}

