#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <bodeplotwindow.h>
#include <mathengine.h>
#include <iostream>
#include <sstream>

namespace Ui {
class StartWindow;
}

class MathEngine;

class StartWindow : public QWidget
{
    Q_OBJECT

public:
     StartWindow(MathEngine* me);
    ~StartWindow();
     void tfUpdate();
     void trimString(std::string& str);

private slots:
    void on_enterButton_clicked();


private:
    // Pointers
    Ui::StartWindow *ui;
    MathEngine* me;

    // Checks if user input is valid, only used in this class
    bool parseInput();

    // Member variables
    std::vector<float> numvec;
    std::vector<float> dnomvec;
};


#endif // STARTWINDOW_H
