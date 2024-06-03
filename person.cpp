#include "person.h"
#include "ui_person.h"
#include "error.h"

Person::Person(QWidget *parent, bool editMode) :
    QDialog(parent),
    ui(new Ui::Person)
{
    ui->setupUi(this);

    Person::editMode = editMode;

    if (editMode) {
        QWidget::setWindowTitle("GLR Datenbank - Person bearbeiten");
        ui->l_dialogTitle->setText("GLR Datenbank - Person bearbeiten");

        QSqlQuery selectPerson;
        selectPerson.prepare("SELECT id, vorname, nachname FROM personen");
        selectPerson.exec();

        while(selectPerson.next()) {
            ui->cb_person->addItem(selectPerson.value(1).toString() + " " + selectPerson.value(2).toString(), selectPerson.value(0).toInt());
        }

        if (ui->cb_person->count() < 1) {
            ui->cb_person->setDisabled(true);
        }

        ui->cb_company->setDisabled(true);
        ui->le_title->setDisabled(true);
        ui->le_first_name->setDisabled(true);
        ui->le_surname->setDisabled(true);
        ui->le_position->setDisabled(true);
        ui->le_phone->setDisabled(true);
        ui->le_email->setDisabled(true);
        ui->cb_you->setDisabled(true);
        ui->le_language->setDisabled(true);
        ui->cb_active->setDisabled(true);

        ui->pb_okay->setDisabled(true);

    } else {
        QWidget::setWindowTitle("GLR Datenbank - Person hinzufügen");
        ui->l_dialogTitle->setText("GLR Datenbank - Person hinzufügen");

        ui->label_11->setVisible(false);
        ui->label_12->setVisible(false);
        ui->cb_person->setVisible(false);
        ui->cb_active->setVisible(false);

        QSqlQuery selectCompany;
        selectCompany.prepare("SELECT id, name FROM firmen");
        selectCompany.exec();

        while(selectCompany.next()) {
            ui->cb_company->addItem(selectCompany.value(1).toString(), selectCompany.value(0).toInt());
        }

        if (ui->cb_company->count() < 1) {
            ui->cb_company->setDisabled(true);
        }
    }

    ui->cb_you->addItem("Du");
    ui->cb_you->addItem("Sie");
}

Person::~Person()
{
    delete ui;
}

void Person::on_cb_person_currentIndexChanged()
{
    QSqlQuery selectPerson;
    selectPerson.prepare("SELECT id , firmen_id, titel, vorname, nachname, position, telefon, email, du_sie, sprache, aktiv FROM personen WHERE id = :personenID");
    selectPerson.bindValue(":personenID", ui->cb_person->currentData().toInt());
    selectPerson.exec();
    selectPerson.next();

    ui->cb_company->setDisabled(false);
    ui->le_title->setDisabled(false);
    ui->le_first_name->setDisabled(false);
    ui->le_surname->setDisabled(false);
    ui->le_position->setDisabled(false);
    ui->le_phone->setDisabled(false);
    ui->le_email->setDisabled(false);
    ui->cb_you->setDisabled(false);
    ui->le_language->setDisabled(false);
    ui->cb_active->setDisabled(false);

    ui->pb_okay->setDisabled(false);

    ui->cb_company->clear();
    QSqlQuery selectCompany;
    selectCompany.prepare("SELECT id, name FROM firmen");
    selectCompany.exec();

    while(selectCompany.next()) {
        ui->cb_company->addItem(selectCompany.value(1).toString(), selectCompany.value(0).toInt());
        if (selectCompany.value(0) == selectPerson.value(1).toInt())
            ui->cb_company->setCurrentIndex(ui->cb_company->count() - 1);
    }

    if (ui->cb_company->count() < 1) {
        ui->cb_company->setDisabled(true);
    }

    ui->le_title->setText(selectPerson.value(2).toString());
    ui->le_first_name->setText(selectPerson.value(3).toString());
    ui->le_surname->setText(selectPerson.value(4).toString());
    ui->le_position->setText(selectPerson.value(5).toString());
    ui->le_phone->setText(selectPerson.value(6).toString());
    ui->le_email->setText(selectPerson.value(7).toString());

    if (selectPerson.value(8).toString() == "Du")
        ui->cb_you->setCurrentIndex(0);
    else
        ui->cb_you->setCurrentIndex(1);

    ui->le_language->setText(selectPerson.value(9).toString());
    ui->cb_active->setChecked(selectPerson.value(10).toBool());
}

void Person::on_pb_okay_clicked()
{
    int personID = ui->cb_person->currentData().toInt();
    int companyID = ui->cb_company->currentData().toInt();
    QString title = ui->le_title->text();
    QString first_name = ui->le_first_name->text();
    QString surname = ui->le_surname->text();
    QString position = ui->le_position->text();
    QString phone = ui->le_phone->text();
    QString email = ui->le_email->text();
    QString you = ui->cb_you->currentText();
    QString language = ui->le_language->text();
    bool activ = ui->cb_active->isChecked();

    //neu angelegte Sponosoren sind immer aktiv
    if (!editMode)
        activ = true;

    QSqlQuery insertPersonQuery;
    if (editMode) {
        insertPersonQuery.prepare("UPDATE personen SET firmen_id = :companyID, titel = :title, vorname = :first_name, nachname = :surname, position = :position, telefon = :phone, email = :email, du_sie = :you, sprache = :language, aktiv = :active WHERE id = :personID");
        insertPersonQuery.bindValue(":personID", personID);
    } else {
        insertPersonQuery.prepare("INSERT INTO personen(firmen_id, titel, vorname, nachname, position, telefon, email, du_sie, sprache, aktiv) VALUES (:companyID, :title, :first_name, :surname, :position, :phone, :email, :you, :language, :active)");
    }

    insertPersonQuery.bindValue(":companyID", companyID);
    insertPersonQuery.bindValue(":title", title);
    insertPersonQuery.bindValue(":first_name", first_name);
    insertPersonQuery.bindValue(":surname", surname);
    insertPersonQuery.bindValue(":position", position);
    insertPersonQuery.bindValue(":phone", phone);
    insertPersonQuery.bindValue(":email", email);
    insertPersonQuery.bindValue(":you", you);
    insertPersonQuery.bindValue(":language", language);
    insertPersonQuery.bindValue(":active", activ);

    insertPersonQuery.exec();

    if (insertPersonQuery.next()) {
        Error errorWindow;
        errorWindow.setText("QSQLITE error: " + insertPersonQuery.lastError().text() + ",\nQSQLITE error code: " + insertPersonQuery.lastError().nativeErrorCode());
        errorWindow.setModal(true);
        errorWindow.exec();
    } else {
        this->accept();
    }
}
