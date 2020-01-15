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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget::setWindowTitle("GLR Sponsorendatenbank");

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("sponsorendatenbank.db");

    if (!db.open())
        ui->l_db_status->setText("Öffnen fehlgeschalgen");
    else
        ui->l_db_status->setText("Verbunden");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pB_createCompany_clicked()
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

void MainWindow::on_pB_createActivity_clicked()
{
    createActivity activity;
    activity.setModal(true);
    activity.exec();
}

void MainWindow::on_pushButton_clicked()
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

void MainWindow::on_pb_modifyCompany_clicked()
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
