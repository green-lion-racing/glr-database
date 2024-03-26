#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdatabase.h"
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

    QWidget::setWindowTitle("Green Lion Racing Datenbank");

    ui->actionCloseDatabase->setEnabled(false);

    // temporarily disable password buttons
    ui->actionPasswordAdd->setEnabled(false);
    ui->actionPasswordRemove->setEnabled(false);
    ui->actionPasswordChange->setEnabled(false);



    // index 1 login
    ui->sw_main->setCurrentIndex(1);

    // display GLR logo at l_logo
    QPixmap logo(":img/logo_glr_white.png");
    ui->l_logo->setPixmap(logo);

    // Set title "GLR Datenbank" in different colors
    ui->l_title->setText("<font color=\'#66D104\'>GLR</font> <font color=\'white\'>Datenbank</font>");

    // no text in error at the beginning
    ui->l_error->setText("");

    // login via click on arrow
    QAction *actionClickLogIn = ui->le_password->addAction(QIcon(":img/icon_arrow.png"), QLineEdit::TrailingPosition);
    connect(actionClickLogIn, &QAction::triggered, this, &MainWindow::openDatabase);



    // index 0 management
    QIcon icon_person = QIcon(":img/icon_person.png");
    QIcon icon_company = QIcon(":img/icon_company.png");
    QIcon icon_communication = QIcon(":img/icon_communication.png");
    QIcon icon_activity = QIcon(":img/icon_activity.png");
    QSize size_big = QSize(200, 200);
    QSize size_small = QSize(75, 75);

    // tb_createMember
    ui->tb_createMember->setIcon(icon_person);
    ui->tb_createMember->setIconSize(size_big);
    // tb_modifyMember
    ui->tb_modifyMember->setIcon(icon_person);
    ui->tb_modifyMember->setIconSize(size_big);

    // tb_createPerson
    ui->tb_createPerson->setIcon(icon_person);
    ui->tb_createPerson->setIconSize(size_small);
    // tb_modifyPerson
    ui->tb_modifyPerson->setIcon(icon_person);
    ui->tb_modifyPerson->setIconSize(size_small);

    // tb_createCompany
    ui->tb_createCompany->setIcon(icon_company);
    ui->tb_createCompany->setIconSize(size_small);
    // tb_modifyCompany
    ui->tb_modifyCompany->setIcon(icon_company);
    ui->tb_modifyCompany->setIconSize(size_small);

    // tb_createCommunication
    ui->tb_createCommunication->setIcon(icon_communication);
    ui->tb_createCommunication->setIconSize(size_small);
    // tb_modifyCommunication
    ui->tb_modifyCommunication->setIcon(icon_communication);
    ui->tb_modifyCommunication->setIconSize(size_small);

    // tb_createActivity
    ui->tb_createActivity->setIcon(icon_activity);
    ui->tb_createActivity->setIconSize(size_small);
    // tb_modifyActivity
    ui->tb_modifyActivity->setIcon(icon_activity);
    ui->tb_modifyActivity->setIconSize(size_small);

    // tb_modifyTables
    ui->tb_modifyTables->setIcon(QIcon(":img/icon_edit.png"));
    ui->tb_modifyTables->setIconSize(size_big);

    // tb_displayTables
    ui->tb_displayTables->setIcon(QIcon(":img/icon_lens.png"));
    ui->tb_displayTables->setIconSize(size_big);



    // no database selected on start
    status_label->setText("Keine Datenbank gewählt.");
    ui->statusbar->addPermanentWidget(status_label, 100);
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

    if (currentFile.isEmpty()) {
        ui->l_error->setText("Keine Datenbank ausgewählt!");
        return;
    }

    dbconn = QSqlDatabase::addDatabase("QSQLITE");
    dbconn.setDatabaseName(currentFile);

    ui->actionCloseDatabase->setEnabled(true);

    // TODO check if selected file is a sqlite db and or cyphered
    // Magic Header String - Every valid SQLite database file begins with the following 16 bytes (in hex): 53 51 4c 69 74 65 20 66 6f 72 6d 61 74 20 33 00
    if (!dbconn.open()) {
        QString enteredPassword = ui->le_password->text();
        dbconn.setPassword(enteredPassword);
        if (!dbconn.open()) {
            ui->l_error->setText("Falsches Passwort oder keine Datenbank.");
            return;
        }
    }

    ui->sw_main->setCurrentIndex(0);
    QFile file(":stylesheet/stylesheet_main.qss");
    file.open(QFile::ReadOnly);
    QString stylesheet = QLatin1String(file.readAll());
    qApp->setStyleSheet(stylesheet);
}

void MainWindow::on_actionOpenDatabase_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Datei öffnen","","SQLite DB (*.db)");

    if (filePath.isEmpty())
        return;

    if (dbconn.isOpen())
        dbconn.close();

    currentFile = filePath;
    status_label->setText(currentFile);

    ui->l_error->setText("");
    ui->sw_main->setCurrentIndex(1);

    QFile file(":stylesheet/stylesheet.qss");
    file.open(QFile::ReadOnly);
    QString stylesheet = QLatin1String(file.readAll());
    qApp->setStyleSheet(stylesheet);
}

void MainWindow::on_actionCloseDatabase_triggered() {
    if (dbconn.isOpen())
        dbconn.close();

    ui->l_error->setText("");
    ui->sw_main->setCurrentIndex(1);

    ui->actionCloseDatabase->setEnabled(false);

    QFile file(":stylesheet/stylesheet.qss");
    file.open(QFile::ReadOnly);
    QString stylesheet = QLatin1String(file.readAll());
    qApp->setStyleSheet(stylesheet);
}

void MainWindow::on_actionPasswordRemove_triggered() {
    // to remove password
    //dbconn.setConnectOptions("QQSQLITE_REMOVE_KEY");
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
        ui->l_error->setText("Passwort wurde entfernt!");
    }
    else {
        ui->l_error->setText("Passwort konnte nicht entfernt werden!");
    }
}

void MainWindow::on_actionPasswordAdd_triggered() {
    // to encrpyt existing database
    //dbconn.setConnectOptions("QQSQLITE_CREATE_KEY");
}

void MainWindow::on_actionPasswordChange_triggered() {

}

void MainWindow::on_actionAbout_triggered() {
    aboutDatabase about;
    about.setModal(true);
    about.exec();
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

void MainWindow::on_tb_modifyCompany_clicked()
{
    // modifyCompany *modifyCompanyWindow;
    // modifyCompanyWindow = new modifyCompany();
    // modifyCompanyWindow->show();
}

void MainWindow::on_tb_displayTables_clicked()
{
    displayTables *tables;
    tables = new displayTables;
    tables->show();
}
