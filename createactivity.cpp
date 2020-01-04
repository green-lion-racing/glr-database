#include "createactivity.h"
#include "ui_createactivity.h"
#include <QVector>

createActivity::createActivity(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createActivity)
{
    QVector<QString> companyNames;
    QVector<int> companyIds;
    QVector<QVector<QString>> companies;
    ui->setupUi(this);

    QWidget::setWindowTitle("GLR Sponsorendatenbank - Leistung hinzufügen");

    QSqlQuery selectName;
    selectName.prepare("SELECT id, name FROM firmen");
    selectName.exec();
    while(selectName.next()) {
        companyIds.push_back(selectName.value(0).toInt());
        companyNames.push_back(selectName.value(1).toString());
    }
    companies.push_back(companyNames);
    for (int i = 0; i < companyNames.size(); i++) {
        ui->cb_company->addItem(companyNames[i]);
    }

    QVector<QString> persons;
    QSqlQuery selectPersons;

}

createActivity::~createActivity()
{
    delete ui;
}

void createActivity::on_buttonBox_accepted()
{
    QSqlQuery createActivityQquery("CREATE TABLE IF NOT EXISTS leistungen (id INTEGER PRIMARY KEY, firma TEXT, ansprechpartner TEXT, wann TEXT, wert TEXT, was TEXT, infos TEXT, FOREIGN KEY (firma) REFERENCES firmen(name))");
    QString person = ui->cb_person->currentText();
    QString when = ui->le_when->text();
    QString value = ui->le_value->text();
    QString what = ui->le_what->text();
    QString info = ui->te_info->toPlainText();
    QString companyName = ui->cb_company->currentText();
    QSqlQuery insertActivityQuery;
    insertActivityQuery.prepare("INSERT INTO leistungen(firma, ansprechpartner, wann, wert, was, infos) VALUES (:companyName, :person, :when, :value, :what, :info)");
    insertActivityQuery.bindValue(":companyName", companyName);
    insertActivityQuery.bindValue(":person", person);
    insertActivityQuery.bindValue(":when", when);
    insertActivityQuery.bindValue(":value", value);
    insertActivityQuery.bindValue(":what", what);
    insertActivityQuery.bindValue(":info", info);

    insertActivityQuery.exec();

    if (insertActivityQuery.next())
    {
    } else {
        qDebug() << "SqLite error:" << insertActivityQuery.lastError().text() << ", SqLite error code:" << insertActivityQuery.lastError().number();
    }
}

void createActivity::on_cb_company_currentTextChanged(const QString &arg1)
{

    ui->cb_person->clear();

    QVector<QString> persons;
    QSqlQuery selectPersons;

    QString currentCompanyName = ui->cb_company->currentText();

    selectPersons.prepare("SELECT vorname, nachname FROM personen WHERE firma = :currentCompanyName");
    selectPersons.bindValue(":currentCompanyName", currentCompanyName);
    selectPersons.exec();
    while(selectPersons.next()) {
        persons.push_back(selectPersons.value(0).toString() + " " + selectPersons.value(1).toString());
    }

    for (int i = 0; i < persons.size(); i++) {
        ui->cb_person->addItem(persons[i]);
    }
}
