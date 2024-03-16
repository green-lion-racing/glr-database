#include "aboutdatabase.h"
#include "ui_aboutdatabase.h"

aboutDatabase::aboutDatabase(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::aboutDatabase)
{
    ui->setupUi(this);

    QWidget::setWindowTitle("Über die GLR Datenbank");
}

aboutDatabase::~aboutDatabase()
{
    delete ui;
}
