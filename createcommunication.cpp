#include "createcommunication.h"
#include "ui_createcommunication.h"
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include "addfile.h"
#include <ctime>

static QFile file;

createCommunication::createCommunication(QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint),
    ui(new Ui::createCommunication)
{
    ui->setupUi(this);

    QWidget::setWindowTitle("GLR Sponsorendatenbank - Kommunikation hinzufügen");

    QSqlQuery selectName;
    selectName.prepare("SELECT name FROM firmen");
    selectName.exec();
    QSqlQueryModel * modal = new QSqlQueryModel();
    modal->setQuery(selectName);
    ui->cb_company->setModel(modal);

    // Do not display week numbers
    ui->cw_calender->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    // print initially selected date (today)
    when = ui->cw_calender->selectedDate().toString("yyyy-MM-dd");      //Auswahl über Kalender Widget
    ui->le_when->setText(when);
}

createCommunication::~createCommunication()
{
    delete ui;
}

void createCommunication::on_cb_company_currentTextChanged(const QString &arg1)
{
    ui->cb_person->clear();

    QVector<QString> persons;
    //QVector<int> personIds;
    QSqlQuery selectPersons;

    //QString currentCompanyName = ui->cb_company->currentText();

    persons.clear();

    QString currentCompanyId = getCompanyId();
    selectPersons.prepare("SELECT id, vorname, nachname FROM personen WHERE FirmenID = :currentCompanyId");
    selectPersons.bindValue(":currentCompanyId", currentCompanyId);
    selectPersons.exec();
    while(selectPersons.next()) {
        personIds.push_back(selectPersons.value(0).toInt());
        persons.push_back(selectPersons.value(1).toString() + " " + selectPersons.value(2).toString());
    }

    for (int i = 0; i < persons.size(); i++) {
        ui->cb_person->addItem(persons[i]);
    }

}

void createCommunication::on_cw_calender_selectionChanged()
{
    when = ui->cw_calender->selectedDate().toString("yyyy-MM-dd");      //Auswahl über Kalender Widget
    ui->le_when->setText(when);
}

void createCommunication::on_pb_okay_clicked()
{
    //QSqlQuery createCommunicationQuery("CREATE TABLE IF NOT EXISTS kommunikationen (id INTEGER PRIMARY KEY, firma TEXT, ansprechpartner TEXT, wann TEXT, was TEXT, FOREIGN KEY (firma) REFERENCES firmen(name))");
    QSqlQuery createCommunicationQuery("CREATE TABLE IF NOT EXISTS kommunikationen (id INTEGER PRIMARY KEY, firma TEXT, ansprechpartner TEXT, wann TEXT, was TEXT, FirmenID INTEGER, PersonenID INTEGER, FOREIGN KEY (FirmenID) REFERENCES firmen(id), FOREIGN KEY(PersonenID) REFERENCES personen(id))");
    QString companyName = ui->cb_company->currentText();
    //QString when = ui->le_when->text();
    QString what = ui->le_what->text();
    QString person = ui->cb_person->currentText();
    //when = ui->cw_calender->selectedDate().toString("yyyy-MM-dd");      //Auswahl über Kalender Widget

    QSqlQuery selectId;
    selectId.prepare("SELECT id FROM firmen WHERE name = :companyName");
    selectId.bindValue(":companyName", companyName);
    selectId.exec();
    int companyId = 0;
    while(selectId.next())
        companyId = (selectId.value(0).toString()).toInt();

    // get firstName and surname via personId
    int personIdIndex = std::distance(persons.begin(), std::find(persons.begin(), persons.end(), person));
    //QString firstName;
    //QString surname;
    int personId = personIds[personIdIndex];

    /*
    QSqlQuery selectPersonId;
    selectId.prepare("SELECT id FROM personen WHERE firma = :companyName AND vorname = :firstName AND nachname = :surname");
    selectId.bindValue(":companyName", companyName);
    selectId.bindValue(":firstName", firstName);
    selectId.bindValue(":surname", surname);
    selectId.exec();
    int personId = 0;
    while(selectId.next())
        personId = (selectId.value(0).toString()).toInt();
    */

    QSqlQuery insertCommunicationQuery;
    insertCommunicationQuery.prepare("INSERT INTO kommunikationen(firma, ansprechpartner, wann, was, FirmenID, PersonenID) VALUES (:companyName, :person, :when, :what, :companyId, :personId)");
    insertCommunicationQuery.bindValue(":person", person);
    insertCommunicationQuery.bindValue(":companyName", companyName);
    insertCommunicationQuery.bindValue(":when", when);
    insertCommunicationQuery.bindValue(":what", what);
    insertCommunicationQuery.bindValue(":companyId", companyId);
    insertCommunicationQuery.bindValue(":personId", personId);

    insertCommunicationQuery.exec();

    if (insertCommunicationQuery.next())
    {
    } else {
        qDebug() << "QSQLITE error:" << insertCommunicationQuery.lastError().text() << ", QSQLITE error code:" << insertCommunicationQuery.lastError().nativeErrorCode();
    }

    close();    //Fenster schließen, um zu dem Nächsten zukommen (Dateien anhängen)
    addFile file;
    file.setModal(true);
    file.exec();
}

void createCommunication::on_pb_close_clicked()
{
    this->reject();
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
