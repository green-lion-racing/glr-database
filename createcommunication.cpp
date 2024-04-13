#include "createcommunication.h"
#include "ui_createcommunication.h"
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include "addfile.h"
#include "error.h"

static QFile file;

createCommunication::createCommunication(QWidget *parent, bool editMode) :
    QDialog(parent),
    ui(new Ui::createCommunication)
{
    QSqlQuery createCommunicationQuery("CREATE TABLE IF NOT EXISTS kommunikationen (id INTEGER PRIMARY KEY, firma TEXT, ansprechpartner TEXT, wann TEXT, was TEXT, FirmenID INTEGER, PersonenID INTEGER, FOREIGN KEY (FirmenID) REFERENCES firmen(id), FOREIGN KEY(PersonenID) REFERENCES personen(id))");

    ui->setupUi(this);

    createCommunication::editMode = editMode;

    QVector<QString> communicationNames;

    if (editMode) {
        QWidget::setWindowTitle("GLR Datenbank - Leistung bearbeiten");
        ui->l_dialogTitle->setText("GLR Datenbank - Leistung bearbeiten");

        QSqlQuery selectActivity;
        selectActivity.prepare("SELECT id, firma, ansprechpartner, wann FROM kommunikationen");
        selectActivity.exec();

        while(selectActivity.next()) {
            communicationNames.push_back(selectActivity.value(0).toString() + " - " +
                                    selectActivity.value(1).toString() + " - " +
                                    selectActivity.value(2).toString() + " - " +
                                    selectActivity.value(3).toString());
        }

        for (int i = 0; i < communicationNames.size(); i++) {
            ui->cb_communication->addItem(communicationNames[i]);
        }

        if (communicationNames.size() < 1) {
            ui->cb_communication->setDisabled(true);
        }

        ui->cb_company->setDisabled(true);
        ui->cb_person->setDisabled(true);
        ui->cw_calender->setDisabled(true);
        ui->le_when->setDisabled(true);
        ui->le_what->setDisabled(true);
        ui->pb_okay->setDisabled(true);

    } else {
        QWidget::setWindowTitle("GLR Datenbank - Leistung hinzufügen");
        ui->l_dialogTitle->setText("GLR Datenbank - Leistung hinzufügen");
        ui->cb_communication->setVisible(false);
        ui->label_5->setVisible(false);

        set_cb_company();
    }

    // Do not display week numbers
    ui->cw_calender->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

    // print initially selected date (today)
    ui->le_when->setText(ui->cw_calender->selectedDate().toString("yyyy-MM-dd"));
}

createCommunication::~createCommunication()
{
    delete ui;
}

void createCommunication::on_cb_communication_currentTextChanged()
{
    QSqlQuery selectActivity;

    static QRegularExpression regex(" - ");
    int activityID = ui->cb_communication->currentText().split(regex)[0].toInt();

    selectActivity.prepare("SELECT * FROM kommunikationen WHERE id = :activityID");
    selectActivity.bindValue(":activityID", activityID);
    selectActivity.exec();
    selectActivity.next();

    ui->cb_company->setDisabled(false);
    ui->cb_person->setDisabled(false);
    ui->cw_calender->setDisabled(false);
    ui->le_when->setDisabled(false);
    ui->le_what->setDisabled(false);
    ui->pb_okay->setDisabled(false);


    set_cb_company(selectActivity.value(1).toString());
    set_cb_person(selectActivity.value(2).toString());
    ui->le_when->setText(selectActivity.value(3).toString());
    ui->cw_calender->setSelectedDate(selectActivity.value(3).toDate());
    ui->le_what->setText(selectActivity.value(4).toString());
}

void createCommunication::on_cb_company_currentTextChanged()
{
    set_cb_person();
}

void createCommunication::on_cw_calender_selectionChanged()
{
    ui->le_when->setText(ui->cw_calender->selectedDate().toString("yyyy-MM-dd"));
}

void createCommunication::on_pb_okay_clicked()
{
    int communicationID = ui->cb_communication->currentIndex();
    int personID = ui->cb_person->currentIndex();
    int companyID = ui->cb_company->currentIndex();
    QString company = ui->cb_company->currentText();
    QString person = ui->cb_person->currentText();
    QString when = ui->le_when->text();
    QString what = ui->le_what->text();

    QSqlQuery insertCommunicationQuery;
    if (editMode) {
        insertCommunicationQuery.prepare("UPDATE kommunikationen SET firma = :company, ansprechpartner = :person, wann = :when, was = :what, FirmenID = :companyID, PersonenID = :personID WHERE id = :communicationID");
        insertCommunicationQuery.bindValue(":communicationID", communicationID + 1);
    } else {
        insertCommunicationQuery.prepare("INSERT INTO kommunikationen(firma, ansprechpartner, wann, was, FirmenID, PersonenID) VALUES (:company, :person, :when, :what, :companyID, :personID)");
    }

    insertCommunicationQuery.bindValue(":person", person);
    insertCommunicationQuery.bindValue(":company", company);
    insertCommunicationQuery.bindValue(":when", when);
    insertCommunicationQuery.bindValue(":what", what);
    insertCommunicationQuery.bindValue(":companyID", companyID);
    insertCommunicationQuery.bindValue(":personID", personID);

    insertCommunicationQuery.exec();

    if (insertCommunicationQuery.next()) {
        error errorWindow;
        errorWindow.setText("QSQLITE error: " + insertCommunicationQuery.lastError().text() + ",\nQSQLITE error code: " + insertCommunicationQuery.lastError().nativeErrorCode());
        errorWindow.setModal(true);
        errorWindow.exec();
    } else {
        // TODO
        addFile file;
        file.setModal(true);
        file.exec();

        this->accept();
    }
}

QString createCommunication::getCompanyId () {
    QSqlQuery queryCompanyId;
    QString companyName = ui->cb_company->currentText();
    queryCompanyId.prepare("SELECT id FROM firmen WHERE name = :companyName");
    queryCompanyId.bindValue(":companyName", companyName);
    queryCompanyId.exec();

    QString companyId;
    while (queryCompanyId.next())
        companyId = queryCompanyId.value(0).toString();

    return companyId;
}

void createCommunication::set_cb_company(QString company) {
    QSqlQuery selectName;
    QVector<QString> companyNames;

    ui->cb_company->clear();

    selectName.prepare("SELECT id, name FROM firmen");
    selectName.exec();
    while(selectName.next()) {
        companyNames.push_back(selectName.value(1).toString());
    }

    for (int i = 0; i < companyNames.size(); i++) {
        ui->cb_company->addItem(companyNames[i]);
        if (!QString::compare(company, companyNames[i], Qt::CaseInsensitive)) {
            ui->cb_company->setCurrentIndex(i);
        }
    }

    if (companyNames.size() > 0) {
        ui->cb_company->setEnabled(true);
    } else {
        ui->cb_company->setDisabled(true);
    }
}

void createCommunication::set_cb_person(QString person) {
    QSqlQuery selectName;
    QVector<QString> personNames;

    ui->cb_person->clear();

    selectName.prepare("SELECT id, vorname, nachname FROM personen WHERE FirmenID = :companyID");
    selectName.bindValue(":companyID", getCompanyId());
    selectName.exec();
    while(selectName.next()) {
        personNames.push_back(selectName.value(1).toString() + " " + selectName.value(2).toString());
    }
    for (int i = 0; i < personNames.size(); i++) {
        ui->cb_person->addItem(personNames[i]);
        if (!QString::compare(person, personNames[i], Qt::CaseInsensitive))
            ui->cb_person->setCurrentIndex(i);
    }

    if (personNames.size() > 0) {
        ui->cb_person->setEnabled(true);
    } else {
        ui->cb_person->setDisabled(true);
    }
}
