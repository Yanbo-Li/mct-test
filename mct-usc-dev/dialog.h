#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <bodewindow.h>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_enterButton_clicked();


private:
    Ui::Dialog *ui;
    void PrintVectors();
    void TFUpdate();
    void TrimString(std::string& str);
    std::string to_string_with_precision(float a_value, const int n);

    std::vector<float> numvec;
    std::vector<float> dnomvec;
    std::string numString;
    std::string denomString;
    BodeWindow * bodewindow; //for bode window
};


#endif // DIALOG_H
