#include "error.h"
#include "ui_error.h"

error::error(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::error)
{
    QWidget::setWindowTitle("Fehler");

    ui->setupUi(this);
}

error::~error()
{
    delete ui;
}

void error::setText(QString error) {
    ui->l_error->setText(error);
}

void error::on_pb_okay_clicked()
{
    close();
}
