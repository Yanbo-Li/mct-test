#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

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

<<<<<<< HEAD
    std::vector<int> numvec;
    std::vector<int> dnomvec;
=======
    std::vector<float> numvec;
    std::vector<float> dnomvec;
>>>>>>> 964a5d7209f3793cbba5880f821ebb3dd5c0adf8
};


#endif // DIALOG_H
