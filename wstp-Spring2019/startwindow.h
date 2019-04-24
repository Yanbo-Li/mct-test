#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <bodeplotwindow.h>
#include <mathengine.h>
#include <iostream>
#include <sstream>
#include "wolframlink.h"
#include "graphs.h"

namespace Ui {
class StartWindow;
}

class MathEngine;

class StartWindow : public QWidget
{
    Q_OBJECT

public:
     StartWindow(MathEngine* me, Graphs* graphs );
    ~StartWindow();
     void tfUpdate();
     void trimString(std::string& str);

private slots:
    void on_enterButton_clicked();


private:
    // Pointers
    Ui::StartWindow *ui;
    MathEngine* me;
    Graphs *graphs;
    // Checks if user input is valid, only used in this class
    bool parseInput();

    // Member variables
    std::vector<double> numvec;
    std::vector<double> dnomvec;
};


#endif // STARTWINDOW_H
