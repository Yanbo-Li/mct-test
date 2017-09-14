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

    std::vector<int> numvec;
    std::vector<int> dnomvec;
};

#endif // DIALOG_H
