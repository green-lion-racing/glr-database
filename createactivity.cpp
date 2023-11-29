#include "createactivity.h"
#include "ui_createactivity.h"
#include <QVector>

createActivity::createActivity(QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint),        // Frameless window
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

    // Do not display week numbers
    ui->cw_calender->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    // print initially selected date (today)
    when = ui->cw_calender->selectedDate().toString("yyyy-MM-dd");      //Auswahl über Kalender Widget
    ui->le_when->setText(when);
}

createActivity::~createActivity()
{
    delete ui;
}

void createActivity::on_cb_company_currentTextChanged(const QString &arg1)
{

    ui->cb_person->clear();

    QVector<QString> persons;
    QSqlQuery selectPersons;

    //QString currentCompanyName = ui->cb_company->currentText();
    QString currentCompanyId = getCompanyId();
    selectPersons.prepare("SELECT vorname, nachname FROM personen WHERE FirmenID = :currentCompanyId");
    selectPersons.bindValue(":currentCompanyId", currentCompanyId);
    selectPersons.exec();
    while(selectPersons.next()) {
        persons.push_back(selectPersons.value(0).toString() + " " + selectPersons.value(1).toString());
    }

    for (int i = 0; i < persons.size(); i++) {
        ui->cb_person->addItem(persons[i]);
    }
}

void createActivity::on_cw_calender_selectionChanged()
{
    when = ui->cw_calender->selectedDate().toString("yyyy-MM-dd");      //Auswahl über Kalender Widget
    ui->le_when->setText(when);
}

void createActivity::on_pb_okay_clicked()
{
    QSqlQuery createActivityQquery("CREATE TABLE IF NOT EXISTS leistungen (id INTEGER PRIMARY KEY, firma TEXT, ansprechpartner TEXT, wann TEXT, wert TEXT, was TEXT, infos TEXT, FOREIGN KEY (firma) REFERENCES firmen(name))");
    QString person = ui->cb_person->currentText();
    //QString when = ui->le_when->text();
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
        qDebug() << "QSQLITE error:" << insertActivityQuery.lastError().text() << ", QSQLITE error code:" << insertActivityQuery.lastError().nativeErrorCode();
    }

    this->accept();
}

void createActivity::on_pb_close_clicked()
{
    this->reject();
}

QString createActivity::getCompanyId () {
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
