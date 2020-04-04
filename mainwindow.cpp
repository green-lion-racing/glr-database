#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "createcompany.h"
#include "createperson.h"
#include "createactivity.h"
#include "createcommunication.h"
#include "savefile.h"
#include "modifycompany.h"
#include "modifytables.h"
#include "displaytables.h"
#include "passwordinput.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(1);
    QWidget::setWindowTitle("GLR Sponsorendatenbank");

    QAction *actionClickLogIn = ui->le_password->addAction(QIcon(":/img/icon_arrow.png"), QLineEdit::TrailingPosition);
    connect(actionClickLogIn, &QAction::triggered, this, &MainWindow::on_icon_clicked);

    // Set l_title "GLR Sponsorentanbank" in different colors
    ui->l_title->setText("<font color=\'green\'>GLR</font> <font color=\'white\'>Sponsorendatenbank</font>");

    ui->pb_createCompany->setEnabled(false);
    ui->pb_createPerson->setEnabled(false);
    ui->pb_createActivity->setEnabled(false);
    ui->pb_createCommunication->setEnabled(false);
    ui->pb_modifyTables->setEnabled(false);
    ui->pb_seeTables->setEnabled(false);
    /*
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
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


void MainWindow::on_icon_clicked() {
    //this->hide();
    //mainWindow.show();
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pb_createCompany_clicked()
{
    createCompany company;
    company.setModal(true);
    company.exec();
    //QSqlQuery createCompanyQquery("CREATE TABLE firmen (id INTEGER PRIMARY KEY, name TEXT, aktiv BOOL, seit TEXT, bis TEXT, Rang TEXT, Leistungstyp TEXT, Infos TEXT)");
    //QSqlQuery insertCompanyQuery("INSERT INTO firmen(name) VALUES ('Firma 1')");

}

void MainWindow::on_pb_createPerson_clicked()
{
    //QSqlQuery createPersonQuery("CREATE TABLE personen (id INTEGER PRIMARY KEY, firma TEXT, vorname TEXT, nachname TEXT, telefon TEXT, fax TEXT, email TEXT, du_sie TEXT, aktiv BOOL, FOREIGN KEY (firma) REFERENCES firmen(name))");
    //QSqlQuery insertPersonQuerry("INSERT INTO personen(vorname, nachname) VALUES ('Vorname1', 'Nachname1')");
    createPerson person;
    person.setModal(true);
    person.exec();
}

void MainWindow::on_pb_createActivity_clicked()
{
    createActivity activity;
    activity.setModal(true);
    activity.exec();
}

void MainWindow::on_pb_createCommunication_clicked()
{
    createCommunication communication;
    communication.setModal(true);
    communication.exec();
}

void MainWindow::on_pb_saveFile_clicked()
{
    saveFile save;
    save.setModal(true);
    save.exec();
}

void MainWindow::on_pb_modifyTables_clicked()
{
    modifyTables *modifyTablesWindow;
    modifyTablesWindow = new modifyTables();
    modifyTablesWindow->show();
}

void MainWindow::on_pb_seeTables_clicked()
{
    displayTables tables;
    tables.setModal(true);
    tables.exec();
}

void MainWindow::on_openDatabase_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Datei öffnen","","DB (*.db)");
    //qDebug() << fileName;
    //QFile file(fileName);

    passwordInput password;
    password.setModal(true);
    password.exec();

    QSqlDatabase dbconn = QSqlDatabase::addDatabase("SQLITECIPHER");
    dbconn.setDatabaseName(fileName);
    dbconn.setPassword(enteredPassword);
    // to encrpyt existing database
    //dbconn.setConnectOptions("QSQLITE_CREATE_KEY");

    if (!dbconn.open()) {
        ui->l_db_status->setText("Öffnen fehlgeschalgen");
    }
    else {
        ui->l_db_status->setText("Verbunden");
        ui->pb_createCompany->setEnabled(true);
        ui->pb_createPerson->setEnabled(true);
        ui->pb_createActivity->setEnabled(true);
        ui->pb_createCommunication->setEnabled(true);
        ui->pb_modifyTables->setEnabled(true);
        ui->pb_seeTables->setEnabled(true);
    }

    /*
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
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
