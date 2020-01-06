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
    QDialog(parent),
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

}

createCommunication::~createCommunication()
{
    delete ui;
}

void createCommunication::on_buttonBox_accepted()
{
    /*
    QSqlQuery createCommunicationQuery("CREATE TABLE IF NOT EXISTS kommunikationen (id INTEGER PRIMARY KEY, firma TEXT, wann TEXT, was TEXT, FOREIGN KEY (firma) REFERENCES firmen(name))");
    QString companyName = ui->cb_company->currentText();
    QString when = ui->le_when->text();
    QString what = ui->le_what->text();

    //QSqlQuery selectId("SELECT id FROM kommunikationen ORDER BY id DESC LIMIT 1");
    //while (selectId.next()) {
        //nextId = (selectId.value(0).toInt())+

    QSqlQuery insertCommunicationQuery;
    insertCommunicationQuery.prepare("INSERT INTO kommunikationen(firma, wann, was) VALUES (:companyName, :when, :what)");
    //insertCommunicationQuery.bindValue(":id", nextId);
    insertCommunicationQuery.bindValue(":companyName", companyName);
    insertCommunicationQuery.bindValue(":when", when);
    insertCommunicationQuery.bindValue(":what", what);

    insertCommunicationQuery.exec();

    if (insertCommunicationQuery.next())
    {
    } else {
        qDebug() << "SqLite error:" << insertCommunicationQuery.lastError().text() << ", SqLite error code:" << insertCommunicationQuery.lastError().number();
    }
    */
}

void createCommunication::on_pb_file_clicked()
{
    //QSqlQuery createCommunicationQuery("CREATE TABLE IF NOT EXISTS kommunikationen (id INTEGER PRIMARY KEY, firma TEXT, ansprechpartner TEXT, wann TEXT, was TEXT, FOREIGN KEY (firma) REFERENCES firmen(name))");
    QSqlQuery createCommunicationQuery("CREATE TABLE IF NOT EXISTS kommunikationen (id INTEGER PRIMARY KEY, firma TEXT, ansprechpartner TEXT, wann TEXT, was TEXT, FirmenID INTEGER, PersonenID INTEGER, FOREIGN KEY (FirmenID) REFERENCES firmen(id), FOREIGN KEY(PersonenID) REFERENCES personen(id))");
    QString companyName = ui->cb_company->currentText();
    QString when = ui->le_when->text();
    QString what = ui->le_what->text();
    QString person = ui->cb_person->currentText();

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
        qDebug() << "SqLite error:" << insertCommunicationQuery.lastError().text() << ", SqLite error code:" << insertCommunicationQuery.lastError().number();
    }

    close();    //Fenster schließen, um zu dem Nächsten zukommen (Dateien anhängen)
    addFile file;
    file.setModal(true);
    file.exec();
}

void createCommunication::on_cb_company_currentTextChanged(const QString &arg1)
{
    ui->cb_person->clear();

    //QVector<QString> persons;
    //QVector<int> personIds;
    QSqlQuery selectPersons;

    QString currentCompanyName = ui->cb_company->currentText();

    selectPersons.prepare("SELECT id, vorname, nachname FROM personen WHERE firma = :currentCompanyName");
    selectPersons.bindValue(":currentCompanyName", currentCompanyName);
    selectPersons.exec();
    while(selectPersons.next()) {
        personIds.push_back(selectPersons.value(0).toInt());
        persons.push_back(selectPersons.value(1).toString() + " " + selectPersons.value(2).toString());
    }

    for (int i = 0; i < persons.size(); i++) {
        ui->cb_person->addItem(persons[i]);
    }

}
