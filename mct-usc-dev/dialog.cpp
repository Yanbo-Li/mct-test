#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QFont f("Arial", 16, QFont::Bold);
    ui->titleLabel -> setFont(f);
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

    // Adding s, s^2, etc in a loop

    // Ask user if it's what they want
    ui->tfLabel->setText(ui->numLineEdit->text() + " / " + ui->denomLineEdit->text());
}

