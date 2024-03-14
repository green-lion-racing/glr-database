#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "createcompany.h"
#include "createperson.h"
#include "createmember.h"
#include "createactivity.h"
#include "createcommunication.h"
#include "modifytables.h"
#include "displaytables.h"
#include <QFileDialog>
#include <QPixmap>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->sw_main->setCurrentIndex(1);
    QWidget::setWindowTitle("GLR Datenbank");

    // login index 1
    // display GLR logo at l_logo
    QPixmap logo(":img/logo_glr_white.png");
    ui->l_logo->setPixmap(logo);

    // login via click on arrow
    QAction *actionClickLogIn = ui->le_password->addAction(QIcon(":img/icon_arrow.png"), QLineEdit::TrailingPosition);
    connect(actionClickLogIn, &QAction::triggered, this, &MainWindow::openDatabase);

    // management index 0
    // tb_createMember
    ui->tb_createMember->setIcon(QIcon(":img/icon_person.png"));
    ui->tb_createMember->setIconSize(QSize(200,200));

    // tb_createPerson
    ui->tb_createPerson->setIcon(QIcon(":img/icon_person.png"));
    ui->tb_createPerson->setIconSize(QSize(200,200));

    // tb_createCompany
    ui->tb_createCompany->setIcon(QIcon(":img/icon_company.png"));
    ui->tb_createCompany->setIconSize(QSize(200,200));

    // tb_createCommunication
    ui->tb_createCommunication->setIcon(QIcon(":img/icon_communication.png"));
    ui->tb_createCommunication->setIconSize(QSize(200,200));

    // tb_createActivity
    ui->tb_createActivity->setIcon(QIcon(":img/icon_activity.png"));
    ui->tb_createActivity->setIconSize(QSize(200,200));

    // tb_modifyTables
    ui->tb_modifyTables->setIcon(QIcon(":img/icon_edit.png"));
    ui->tb_modifyTables->setIconSize(QSize(200,200));

    // tb_displayTables
    ui->tb_displayTables->setIcon(QIcon(":img/icon_lens.png"));
    ui->tb_displayTables->setIconSize(QSize(200,200));

    // Set l_title "GLR Datenbank" in different colors
    ui->l_title->setText("<font color=\'#66D104\'>GLR</font> <font color=\'white\'>Datenbank</font>");

    // no text in l_wrongPassword at the beginning
    ui->l_wrongPassword->setText("");
    /*
    QSqlDatabase db = QSqlDatabase::addDatabase("QQSQLITE");
    db.setDatabaseName("sponsorendatenbank.db");

    if (!db.open())
        ui->l_db_status->setText("Öffnen fehlgeschalgen");
    else
        ui->l_db_status->setText("Verbunden");
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent * event) {
    if (ui->sw_main->currentIndex() == 1 && (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)) {
        openDatabase();
    }
}

void MainWindow::openDatabase() {
//    QString fileName = QFileDialog::getOpenFileName(this, "Datei öffnen","","DB (*.db)");
    QString fileName = "sponsorendatenbank.db";
    //qDebug() << fileName;
    //QFile file(fileName);

//    passwordInput password;
//    password.setModal(true);
//    password.exec();

    QString enteredPassword = ui->le_password->text();

    //QSqlDatabase dbconn = QSqlDatabase::addDatabase("QSQLITE");
    dbconn = QSqlDatabase::addDatabase("QSQLITE");
    dbconn.setDatabaseName(fileName);
    //dbconn.setPassword(enteredPassword);

    // to encrpyt existing database
    //dbconn.setConnectOptions("QQSQLITE_CREATE_KEY");

    // to remove password
    //dbconn.setConnectOptions("QQSQLITE_REMOVE_KEY");


    ui->sw_main->setCurrentIndex(0);

    // use different stylesheet for main menu
    QFile file(":stylesheet/stylesheet_main.qss");
    file.open(QFile::ReadOnly);
    QString stylesheet = QLatin1String(file.readAll());

    qApp->setStyleSheet(stylesheet);

    if (!dbconn.open() || enteredPassword == "") {
        ui->l_wrongPassword->setText("Falsches Passwort!");
    }
    else {
        ui->sw_main->setCurrentIndex(0);

        // use different stylesheet for main menu
        QFile file(":stylesheet/stylesheet_main.qss");
        file.open(QFile::ReadOnly);
        QString stylesheet = QLatin1String(file.readAll());

        qApp->setStyleSheet(stylesheet);
    }
}

//void MainWindow::on_pb_saveFile_clicked()
//{
//    saveFile save;
//    save.setModal(true);
//    save.exec();
//}

// Ueberarbeiten!!!
void MainWindow::on_actionOpenDatabase_triggered()
{
    // Funktion ueberarbeiten!!!
    // Überschneidung mit openDatabase()!!!
    QString fileName = QFileDialog::getOpenFileName(this, "Datei öffnen","","DB (*.db)");
    //qDebug() << fileName;
    //QFile file(fileName);

    //passwordInput password;
    //password.setModal(true);
    //password.exec();

    QSqlDatabase dbconn = QSqlDatabase::addDatabase("QSQLITE");
    dbconn.setDatabaseName(fileName);
    //dbconn.setPassword(enteredPassword);

    // to encrpyt existing database
    //dbconn.setConnectOptions("QQSQLITE_CREATE_KEY");

    // use different stylesheet for main menu
    QFile file(":stylesheet/stylesheet_main.qss");
    file.open(QFile::ReadOnly);
    QString stylesheet = QLatin1String(file.readAll());

    qApp->setStyleSheet(stylesheet);

    if (!dbconn.open()) {

    }
    else {

    }

    /*
    QSqlDatabase db = QSqlDatabase::addDatabase("QQSQLITE");
    db.setDatabaseName(fileName);
    if (!db.open())
        ui->l_db_status->setText("Öffnen fehlgeschalgen");
    else {
        ui->l_db_status->setText("Verbunden");
        ui->pb_createCompany->setEnabled(true);
        ui->pb_createPerson->setEnabled(true);
        ui->pb_createActivity->setEnabled(true);
        ui->pb_createCommunication->setEnabled(true);
        ui->pb_modifyTables->setEnabled(true);
        ui->pb_seeTables->setEnabled(true);
    }
    */
}

void MainWindow::on_actionPasswordRemove_triggered()
{
    QString fileName = "sponsorendatenbank.db";

    QString enteredPassword = ui->le_password->text();
    dbconn.close();
    //QSqlDatabase dbconn = QSqlDatabase::addDatabase("QSQLITE");
    dbconn = QSqlDatabase::addDatabase("QSQLITE");
    dbconn.setDatabaseName(fileName);
    dbconn.setPassword(enteredPassword);
    // to encrpyt existing database
    //dbconn.setConnectOptions("QQSQLITE_CREATE_KEY");

    // to remove password
    dbconn.setConnectOptions("QQSQLITE_REMOVE_KEY");

    if (!dbconn.open() || enteredPassword == "") {
        ui->l_wrongPassword->setText("Passwort wurde entfernt!");
    }
    else {
        ui->l_wrongPassword->setText("Passwort konnte nicht entfernt werden!");
    }
}

void MainWindow::on_tb_createMember_clicked()
{
    createMember member;
    member.setModal(true);
    member.exec();
}

void MainWindow::on_tb_createPerson_clicked()
{
    createPerson person;
    person.setModal(true);
    person.exec();
}

void MainWindow::on_tb_createCompany_clicked()
{
    createCompany company;
    company.setModal(true);
    company.exec();
}

void MainWindow::on_tb_createCommunication_clicked()
{
    createCommunication communicaion;
    communicaion.setModal(true);
    communicaion.exec();
}

void MainWindow::on_tb_createActivity_clicked()
{
    createActivity activity;
    activity.setModal(true);
    activity.exec();
}

void MainWindow::on_tb_modifyTables_clicked()
{
    modifyTables *modifyTablesWindow;
    modifyTablesWindow = new modifyTables();
    modifyTablesWindow->show();
}

void MainWindow::on_tb_displayTables_clicked()
{
    displayTables *tables;
    tables = new displayTables;
    tables->show();
}
