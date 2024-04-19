#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::About)
{
    ui->setupUi(this);

    QWidget::setWindowTitle("Über die GLR Datenbank");
}

About::~About()
{
    delete ui;
}
