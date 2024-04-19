#include "error.h"
#include "ui_error.h"

Error::Error(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Error)
{    
    ui->setupUi(this);

    QDialog::setWindowTitle("Fehler");
}

Error::~Error()
{
    delete ui;
}

void Error::setText(QString error) {
    ui->l_error->setText(error);
}

void Error::on_pb_okay_clicked()
{
    close();
}
