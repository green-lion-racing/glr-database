#include "createperson.h"
#include "ui_createperson.h"
#include "error.h"

createPerson::createPerson(QWidget *parent, bool editMode) :
    QDialog(parent),
    ui(new Ui::createPerson)
{
    ui->setupUi(this);

    QSqlQuery createPersonQuery("CREATE TABLE IF NOT EXISTS personen (id INTEGER PRIMARY KEY, titel TEXT, vorname TEXT, nachname TEXT, telefon TEXT, fax TEXT, email TEXT, Position TEXT, du_sie TEXT, sprache TEXT, aktiv BOOL, FirmenID INTEGER, FOREIGN KEY (FirmenID) REFERENCES firmen(id))");

    createPerson::editMode = editMode;

    ui->cb_you->addItem("Du");
    ui->cb_you->addItem("Sie");

    QVector<QString> personNames;
    QVector<QString> companyNames;

    if (editMode) {
        QWidget::setWindowTitle("GLR Datenbank - Person bearbeiten");
        ui->l_dialogTitle->setText("GLR Datenbank - Person bearbeiten");

        QSqlQuery selectPerson;
        selectPerson.prepare("SELECT id, vorname, nachname FROM personen");
        selectPerson.exec();

        while(selectPerson.next()) {
            personNames.push_back(selectPerson.value(0).toString() + " - " + selectPerson.value(1).toString() + " " + selectPerson.value(2).toString());
        }

        for (int i = 0; i < personNames.size(); i++) {
            ui->cb_person->addItem(personNames[i]);
        }

        if (personNames.size() < 1) {
            ui->cb_person->setDisabled(true);
        }

        ui->cb_company->setDisabled(true);
        ui->le_title->setDisabled(true);
        ui->le_first_name->setDisabled(true);
        ui->le_surname->setDisabled(true);
        ui->le_phone->setDisabled(true);
        ui->le_fax->setDisabled(true);
        ui->le_email->setDisabled(true);
        ui->le_position->setDisabled(true);
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
            companyNames.push_back(selectCompany.value(1).toString());
        }

        for (int i = 0; i < companyNames.size(); i++) {
            ui->cb_company->addItem(companyNames[i]);
        }

        if (companyNames.size() < 1) {
            ui->cb_company->setDisabled(true);
        }
    }
}

createPerson::~createPerson()
{
    delete ui;
}

void createPerson::on_cb_person_currentTextChanged()
{
    QSqlQuery selectPerson;

    static QRegularExpression regex(" - ");
    int personenID = ui->cb_person->currentText().split(regex)[0].toInt();

    selectPerson.prepare("SELECT * FROM personen WHERE id = :personenID");
    selectPerson.bindValue(":personenID", personenID);
    selectPerson.exec();
    selectPerson.next();

    ui->cb_company->setDisabled(false);
    ui->le_title->setDisabled(false);
    ui->le_first_name->setDisabled(false);
    ui->le_surname->setDisabled(false);
    ui->le_phone->setDisabled(false);
    ui->le_fax->setDisabled(false);
    ui->le_email->setDisabled(false);
    ui->le_position->setDisabled(false);
    ui->cb_you->setDisabled(false);
    ui->le_language->setDisabled(false);
    ui->cb_active->setDisabled(false);

    ui->pb_okay->setDisabled(false);


    QVector<QString> companyNames;
    QSqlQuery selectCompany;
    selectCompany.prepare("SELECT id, name FROM firmen");
    selectCompany.exec();

    ui->cb_company->clear();

    while(selectCompany.next()) {
        companyNames.push_back(selectCompany.value(1).toString());
    }

    for (int i = 0; i < companyNames.size(); i++) {
        ui->cb_company->addItem(companyNames[i]);
        if (i == selectPerson.value(12).toInt() - 1)
            ui->cb_company->setCurrentIndex(i);
    }

    if (companyNames.size() < 1) {
        ui->cb_company->setDisabled(true);
    }

    ui->le_title->setText(selectPerson.value(2).toString());
    ui->le_first_name->setText(selectPerson.value(3).toString());
    ui->le_surname->setText(selectPerson.value(4).toString());
    ui->le_phone->setText(selectPerson.value(5).toString());
    ui->le_fax->setText(selectPerson.value(6).toString());
    ui->le_email->setText(selectPerson.value(7).toString());
    ui->le_position->setText(selectPerson.value(8).toString());

    if (selectPerson.value(9).toString() == "Du")
        ui->cb_you->setCurrentIndex(0);
    else
        ui->cb_you->setCurrentIndex(1);

    ui->le_language->setText(selectPerson.value(10).toString());
    ui->cb_active->setChecked(selectPerson.value(11).toBool());
}

void createPerson::on_pb_okay_clicked()
{
    int personID = ui->cb_person->currentIndex();
    QString title = ui->le_title->text();
    QString first_name = ui->le_first_name->text();
    QString surname = ui->le_surname->text();
    QString phone = ui->le_phone->text();
    QString fax = ui->le_fax->text();
    QString email = ui->le_email->text();
    QString position = ui->le_position->text();
    QString you = ui->cb_you->currentText();
    QString company_name = ui->cb_company->currentText();
    QString language = ui->le_language->text();
    bool activ = 1;     //neu angelgte Personen immer aktiv
    int companyID = ui->cb_company->currentIndex();

    // issue on update with key?
    QSqlQuery insertPersonQuery;
    if (editMode) {
        insertPersonQuery.prepare("UPDATE personen SET titel = :title, vorname = :first_name, nachname = :surname, Position = :position, email = :email, fax = :fax, telefon = :phone, du_sie = :you, sprache = :language, aktiv = :active, FirmenID = :companyID WHERE id = :personID");
        insertPersonQuery.bindValue(":personID", personID + 1);
    } else {
        insertPersonQuery.prepare("INSERT INTO personen(titel, vorname, nachname, telefon, fax, email, Position, du_sie, sprache, aktiv, FirmenID) VALUES (:title, :first_name, :surname, :phone, :fax, :email, :position, :you, :language, :active, :companyID)");
    }

    insertPersonQuery.prepare("INSERT INTO personen(titel, vorname, nachname, telefon, fax, email, Position, du_sie, sprache, aktiv, FirmenID) VALUES (:title, :first_name, :surname, :phone, :fax, :email, :position, :you, :language, :active, :companyID)");
    insertPersonQuery.bindValue(":title", title);
    insertPersonQuery.bindValue(":first_name", first_name);
    insertPersonQuery.bindValue(":surname", surname);
    insertPersonQuery.bindValue(":phone", phone);
    insertPersonQuery.bindValue(":fax", fax);
    insertPersonQuery.bindValue(":email", email);
    insertPersonQuery.bindValue(":position", position);
    insertPersonQuery.bindValue(":you", you);
    insertPersonQuery.bindValue(":language", language);
    insertPersonQuery.bindValue(":active", activ);
    insertPersonQuery.bindValue(":companyID", companyID + 1);

    insertPersonQuery.exec();

    if (insertPersonQuery.next()) {
        error errorWindow;
        errorWindow.setText("QSQLITE error: " + insertPersonQuery.lastError().text() + ",\nQSQLITE error code: " + insertPersonQuery.lastError().nativeErrorCode());
        errorWindow.setModal(true);
        errorWindow.exec();
    } else {
        this->accept();
    }
}
