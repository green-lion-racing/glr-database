#include "createactivity.h"
#include "ui_createactivity.h"
#include <QVector>

createActivity::createActivity(QWidget *parent, bool editMode) :
    QDialog(parent/*,Qt::FramelessWindowHint*/),        // Frameless window no more
    ui(new Ui::createActivity)
{
    QVector<QString> activityNames;

    ui->setupUi(this);

    if (editMode) {
        QWidget::setWindowTitle("GLR Datenbank - Leistung bearbeiten");
        ui->l_dialogTitle->setText("GLR Datenbank - Leistung bearbeiten");

        QSqlQuery selectActivity;
        selectActivity.prepare("SELECT id, firma, ansprechpartner, wann FROM leistungen");
        selectActivity.exec();

        while(selectActivity.next()) {
            activityNames.push_back(selectActivity.value(0).toString() + " - " +
                                    selectActivity.value(1).toString() + " - " +
                                    selectActivity.value(2).toString() + " - " +
                                    selectActivity.value(3).toString());
        }

        for (int i = 0; i < activityNames.size(); i++) {
            ui->cb_activity->addItem(activityNames[i]);
        }

        if (activityNames.size() < 1) {
            ui->cb_activity->setDisabled(true);
        }

        ui->cb_company->setDisabled(true);
        ui->cb_person->setDisabled(true);
        ui->cw_calender->setDisabled(true);
        ui->le_when->setDisabled(true);
        ui->le_value->setDisabled(true);
        ui->le_what->setDisabled(true);
        ui->te_info->setDisabled(true);
        ui->pb_okay->setDisabled(true);

    } else {
        QWidget::setWindowTitle("GLR Datenbank - Leistung hinzufügen");
        ui->l_dialogTitle->setText("GLR Datenbank - Leistung hinzufügen");
        ui->cb_activity->setVisible(false);
        ui->label_7->setVisible(false);

        set_cb_company();
    }

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

void createActivity::on_cb_activity_currentTextChanged()
{
    QSqlQuery selectActivity;

    static QRegularExpression regex(" - ");
    int activityID = ui->cb_activity->currentText().split(regex)[0].toInt();

    selectActivity.prepare("SELECT * FROM leistungen WHERE id = :activityID");
    selectActivity.bindValue(":activityID", activityID);
    selectActivity.exec();
    selectActivity.next();

    ui->cb_company->setDisabled(false);
    ui->cb_person->setDisabled(false);
    ui->cw_calender->setDisabled(false);
    ui->le_when->setDisabled(false);
    ui->le_value->setDisabled(false);
    ui->le_what->setDisabled(false);
    ui->te_info->setDisabled(false);
    ui->pb_okay->setDisabled(false);

    set_cb_company(selectActivity.value(1).toString());
    set_cb_person(selectActivity.value(2).toString());
    ui->le_when->setText(selectActivity.value(3).toString());
    ui->cw_calender->setSelectedDate(selectActivity.value(3).toDate());
    ui->le_value->setText(selectActivity.value(4).toString());
    ui->le_what->setText(selectActivity.value(5).toString());
    ui->te_info->setText(selectActivity.value(6).toString());
}

void createActivity::on_cb_company_currentTextChanged()
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

    if (persons.size() > 0)
        ui->cb_person->setDisabled(false);
    else
        ui->cb_person->setDisabled(true);
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

void createActivity::set_cb_company(QString company) {
    QSqlQuery selectName;
    QVector<QString> companyNames;
    selectName.prepare("SELECT id, name FROM firmen");
    selectName.exec();
    while(selectName.next()) {
        companyNames.push_back(selectName.value(1).toString());
    }

    int index;
    for (int i = 0; i < companyNames.size(); i++) {
        ui->cb_company->addItem(companyNames[i]);
        if (!QString::compare(company, companyNames[i], Qt::CaseInsensitive))
            index = i;
    }
    ui->cb_company->setCurrentIndex(index);

    ui->cb_person->clear();
    if (company == "")
        ui->cb_person->setDisabled(true);
    else {
        ui->cb_person->setEnabled(true);
        set_cb_person();
    }
}

void createActivity::set_cb_person(QString person) {
    QSqlQuery selectName;
    QVector<QString> personNames;

    selectName.prepare("SELECT id, vorname, nachname FROM personen WHERE FirmenID = :companyID");
    selectName.bindValue(":companyID", getCompanyId());
    selectName.exec();
    while(selectName.next()) {
        personNames.push_back(selectName.value(1).toString() + " " + selectName.value(2).toString());
    }
    for (int i = 0; i < personNames.size(); i++) {
        ui->cb_company->addItem(personNames[i]);
        if (!QString::compare(person, personNames[i], Qt::CaseInsensitive))
            ui->cb_company->setCurrentIndex(i);
    }
}
