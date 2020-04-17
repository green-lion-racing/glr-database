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
#include <QPixmap>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(1);
    QWidget::setWindowTitle("GLR Sponsorendatenbank");

    // display GLR logo at l_logo
    QPixmap logo(":/img/img/logo_glr.png");
    ui->l_logo->setPixmap(logo);


    QAction *actionClickLogIn = ui->le_password->addAction(QIcon(":/img/icon_arrow.png"), QLineEdit::TrailingPosition);
    connect(actionClickLogIn, &QAction::triggered, this, &MainWindow::on_icon_clicked);

    //
    QPixmap pixmap_createPerson = QPixmap(":/img/img/icon_person.png");
    ui->pb_createPerson->setPixmap(pixmap_createPerson);
    // tb_createPerson
    ui->tb_createPerson->setIcon(QIcon(":img/img/icon_person.png"));
    ui->tb_createPerson->setIconSize(QSize(200,200));

    // tb_createCompany
    ui->tb_createCompany->setIcon(QIcon(":img/img/icon_company.png"));
    ui->tb_createCompany->setIconSize(QSize(200,200));

    // tb_modifyTables
    ui->tb_modifyTables->setIcon(QIcon(":img/img/icon_edit.png"));
    ui->tb_modifyTables->setIconSize(QSize(200,200));

    // tb_displayTables
    ui->tb_displayTables->setIcon(QIcon(":img/img/icon_lens.png"));
    ui->tb_displayTables->setIconSize(QSize(200,200));

    /*
    auto act = new QAction();
    act->setIcon(QIcon(":/img/img/icon_person.png"));
    act->setText("Person hinzufügen");
    ui->tb_createPerson->setDefaultAction(act);
    */

    // Set l_title "GLR Sponsorentanbank" in different colors
    ui->l_title->setText("<font color=\'#00CC00\'>GLR</font> <font color=\'white\'>Sponsorendatenbank</font>");

    // disable push buttons
    ui->pb_createCompany->setEnabled(false);
    ui->pb_createPerson->setEnabled(false);
    ui->pb_createActivity->setEnabled(false);
    ui->pb_createCommunication->setEnabled(false);
    ui->pb_modifyTables->setEnabled(false);
    ui->pb_seeTables->setEnabled(false);

    // no text in l_wrongPassword at the beginning
    ui->l_wrongPassword->setText("");
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
    openDatabase();
}

void MainWindow::keyPressEvent(QKeyEvent * event) {
    if (ui->stackedWidget->currentIndex() == 1 && (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)) {
        openDatabase();
    }
}

void MainWindow::openDatabase() {
    //QString fileName = QFileDialog::getOpenFileName(this, "Datei öffnen","","DB (*.db)");
    QString fileName = "sponsorendatenbank.db";
    //qDebug() << fileName;
    //QFile file(fileName);

    //passwordInput password;
    //password.setModal(true);
    //password.exec();

    enteredPassword = ui->le_password->text();

    //QSqlDatabase dbconn = QSqlDatabase::addDatabase("SQLITECIPHER");
    dbconn = QSqlDatabase::addDatabase("SQLITECIPHER");
    dbconn.setDatabaseName(fileName);
    dbconn.setPassword(enteredPassword);
    // to encrpyt existing database
    //dbconn.setConnectOptions("QSQLITE_CREATE_KEY");

    // to remove password
    //dbconn.setConnectOptions("QSQLITE_REMOVE_KEY");

    if (!dbconn.open() || enteredPassword == "") {
        ui->l_wrongPassword->setText("Falsches Passwort!");
    }
    else {
        ui->stackedWidget->setCurrentIndex(0);

        // use different stylesheet for main menu
        QFile file(":/stylesheets/stylesheet_main.qss");
        file.open(QFile::ReadOnly);
        QString stylesheet = QLatin1String(file.readAll());

        qApp->setStyleSheet(stylesheet);

        // activate push button
        ui->pb_createCompany->setEnabled(true);
        ui->pb_createPerson->setEnabled(true);
        ui->pb_createActivity->setEnabled(true);
        ui->pb_createCommunication->setEnabled(true);
        ui->pb_modifyTables->setEnabled(true);
        ui->pb_seeTables->setEnabled(true);
    }
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

    }
    else {
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

void MainWindow::on_actionPasswort_entfernen_triggered()
{
    QString fileName = "sponsorendatenbank.db";

    enteredPassword = ui->le_password->text();
    dbconn.close();
    //QSqlDatabase dbconn = QSqlDatabase::addDatabase("SQLITECIPHER");
    dbconn = QSqlDatabase::addDatabase("SQLITECIPHER");
    dbconn.setDatabaseName(fileName);
    dbconn.setPassword(enteredPassword);
    // to encrpyt existing database
    //dbconn.setConnectOptions("QSQLITE_CREATE_KEY");

    // to remove password
    dbconn.setConnectOptions("QSQLITE_REMOVE_KEY");

    if (!dbconn.open() || enteredPassword == "") {
        ui->l_wrongPassword->setText("Passwort wurde entfernt!");
    }
    else {
        ui->l_wrongPassword->setText("Passwort konnte nicht entfernt werden!");
    }
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
