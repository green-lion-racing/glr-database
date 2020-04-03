#include "login.h"
#include "ui_login.h"

logIn::logIn(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::logIn)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(1);
    QAction *actionClickLogIn = ui->le_password->addAction(QIcon("/home/tobias/Downloads/icon_arrow.png"), QLineEdit::TrailingPosition);
    connect(actionClickLogIn, &QAction::triggered, this, &logIn::on_icon_clicked);
}

logIn::~logIn()
{
    delete ui;
}

void logIn::on_icon_clicked() {
    //this->hide();
    //mainWindow.show();
    ui->stackedWidget->setCurrentIndex(0);
}
