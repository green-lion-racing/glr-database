#include "passwordinput.h"
#include "ui_passwordinput.h"

QString enteredPassword;

passwordInput::passwordInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::passwordInput)
{
    ui->setupUi(this);

    QWidget::setWindowTitle("GLR Sponsorendatenbank - Passwort eingeben");

}

passwordInput::~passwordInput()
{
    delete ui;
}

void passwordInput::on_buttonBox_accepted()
{
    enteredPassword = ui->le_password->text();
}
