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

class Dialog : public QWidget
{
    Q_OBJECT

public:
     Dialog(MathEngine* me);
    ~Dialog();
     void tfUpdate();
     void trimString(std::string& str);
     std::string to_string_with_precision(float a_value, const int n);

private slots:
    void on_enterButton_clicked();


private:
    bool parseInput();
    Ui::Dialog *ui;
    MathEngine* me;
    std::vector<float> numvec;
    std::vector<float> dnomvec;
    BodeWindow * bodewindow; //for bode window
    //BodePlotWindow * bw;

};


#endif // DIALOG_H
