#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <bodeplotwindow.h>
#include <controlsystemwindow.h>
#include <mathengine.h>
#include <iostream>
#include <sstream>
#include "wolframlink.h"

namespace Ui {
class StartWindow;
}

class MathEngine;

class StartWindow : public QWidget
{
    Q_OBJECT

public:
     StartWindow(MathEngine* me, WolframLink * link );
    ~StartWindow();
     void tfUpdate();
     void trimString(std::string& str);

private slots:
    void on_enterButton_clicked();


private:
    // Pointers
    Ui::StartWindow *ui;
    MathEngine* me;
    WolframLink * link;
    // Checks if user input is valid, only used in this class
    bool parseInput();

    // Member variables
    std::vector<double> numvec;
    std::vector<double> dnomvec;
};


#endif // STARTWINDOW_H
