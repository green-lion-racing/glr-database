#ifndef PASSWORDINPUT_H
#define PASSWORDINPUT_H

#include <QDialog>

extern QString enteredPassword;

namespace Ui {
class passwordInput;
}

class passwordInput : public QDialog
{
    Q_OBJECT

public:
    explicit passwordInput(QWidget *parent = nullptr);
    ~passwordInput();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::passwordInput *ui;

    //QString enteredPassword;
};

#endif // PASSWORDINPUT_H
