#include "bodewindow.h"
#include "ui_bodewindow.h"

BodeWindow::BodeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BodeWindow)
{
    ui->setupUi(this);
}

BodeWindow::~BodeWindow()
{
    delete ui;
}
