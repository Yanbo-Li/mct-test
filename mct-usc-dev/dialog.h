#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <bodewindow.h>
#include <bodeplotwindow.h>
#include <mathengine.h>
#include <iostream>
#include <sstream>

namespace Ui {
class Dialog;
}

class MathEngine;

class Dialog : public QWidget
{
    Q_OBJECT

public:
     Dialog(MathEngine* me);
    ~Dialog();
     void tfUpdate();
     void trimString(std::string& str);

private slots:
    void on_enterButton_clicked();


private:
    // Pointers
    Ui::Dialog *ui;
    MathEngine* me;
    BodeWindow* bodewindow; //for bode window

    // Checks if user input is valid, only used in this class
    bool parseInput();

    // Member variables
    std::vector<float> numvec;
    std::vector<float> dnomvec;
};


#endif // DIALOG_H
