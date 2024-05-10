#include "company.h"
#include "ui_company.h"
#include <QString>
#include <QVector>
#include "error.h"

Company::Company(QWidget *parent, bool editMode) :
    QDialog(parent),
    ui(new Ui::Company)
{
    ui->setupUi(this);

    QSqlQuery  CompanyQquery("CREATE TABLE IF NOT EXISTS firmen (id INTEGER PRIMARY KEY, name TEXT, aktiv BOOL, seit TEXT, bis TEXT, Rang TEXT, Leistungstyp TEXT, Str TEXT, Hausnummer TEXT, Ort TEXT, PLZ INTEGER, Land TEXT, Infos TEXT)");

    Company::editMode = editMode;

    QVector<QString> companyNames;

    if (editMode) {
        QWidget::setWindowTitle("GLR Datenbank - Unternehmen bearbeiten");
        ui->l_dialogTitle->setText("GLR Datenbank - Unternehmen bearbeiten");

        QSqlQuery selectCompany;
        selectCompany.prepare("SELECT id, name FROM firmen");
        selectCompany.exec();

        while(selectCompany.next()) {
            companyNames.push_back(selectCompany.value(0).toString() + " - " + selectCompany.value(1).toString());
        }

        for (int i = 0; i < companyNames.size(); i++) {
            ui->cb_company->addItem(companyNames[i]);
        }

        if (companyNames.size() < 1) {
            ui->cb_company->setDisabled(true);
        }

        ui->le_name->setDisabled(true);
        ui->le_since->setDisabled(true);
        ui->le_until->setDisabled(true);

        ui->rb_gold->setDisabled(true);
        ui->rb_silver->setDisabled(true);
        ui->rb_bronze->setDisabled(true);
        ui->rb_supporter->setDisabled(true);

        ui->le_street->setDisabled(true);
        ui->le_houseNumber->setDisabled(true);
        ui->le_zip->setDisabled(true);
        ui->le_city->setDisabled(true);
        ui->le_country->setDisabled(true);
        ui->le_info->setDisabled(true);
        ui->cb_active->setDisabled(true);

        ui->pb_okay->setDisabled(true);

    } else {
        QWidget::setWindowTitle("GLR Datenbank - Unternehmen hinzufügen");
        ui->l_dialogTitle->setText("GLR Datenbank - Unternehmen hinzufügen");

        ui->label_11->setVisible(false);
        ui->label_12->setVisible(false);
        ui->cb_company->setVisible(false);
        ui->cb_active->setVisible(false);
    }
}

Company::~Company()
{
    delete ui;
}

void Company::on_cb_company_currentTextChanged()
{
    QSqlQuery selectCompany;

    static QRegularExpression regex(" - ");
    int companyID = ui->cb_company->currentText().split(regex)[0].toInt();

    selectCompany.prepare("SELECT * FROM firmen WHERE id = :companyID");
    selectCompany.bindValue(":companyID", companyID);
    selectCompany.exec();
    selectCompany.next();

    ui->le_name->setDisabled(false);
    ui->le_since->setDisabled(false);
    ui->le_until->setDisabled(false);

    ui->rb_gold->setDisabled(false);
    ui->rb_silver->setDisabled(false);
    ui->rb_bronze->setDisabled(false);
    ui->rb_supporter->setDisabled(false);

    ui->le_street->setDisabled(false);
    ui->le_houseNumber->setDisabled(false);
    ui->le_zip->setDisabled(false);
    ui->le_city->setDisabled(false);
    ui->le_country->setDisabled(false);
    ui->le_info->setDisabled(false);
    ui->cb_active->setDisabled(false);

    ui->pb_okay->setDisabled(false);

    ui->le_name->setText(selectCompany.value(1).toString());
    ui->le_since->setText(selectCompany.value(3).toString());
    ui->le_until->setText(selectCompany.value(4).toString());

    QString rank = selectCompany.value(5).toString();
    if (rank == "Gold") {
        ui->rb_gold->setChecked(true);
    } else if (rank == "Silber") {
        ui->rb_silver->setChecked(true);
    } else if (rank == "Bronze") {
        ui->rb_bronze->setChecked(true);
    } else if (rank == "Supporter") {
        ui->rb_supporter->setChecked(true);
    } else {
        ui->buttonGroup->setExclusive(false);

        ui->rb_gold->setChecked(false);
        ui->rb_silver->setChecked(false);
        ui->rb_bronze->setChecked(false);
        ui->rb_supporter->setChecked(false);

        ui->buttonGroup->setExclusive(true);
    }

    ui->le_typ->setText(selectCompany.value(6).toString());
    ui->le_street->setText(selectCompany.value(7).toString());
    ui->le_houseNumber->setText(selectCompany.value(8).toString());
    ui->le_zip->setText(selectCompany.value(10).toString());
    ui->le_city->setText(selectCompany.value(9).toString());
    ui->le_country->setText(selectCompany.value(11).toString());
    ui->le_info->setText(selectCompany.value(12).toString());
    ui->cb_active->setChecked(selectCompany.value(2).toBool());
}

void Company::on_pb_okay_clicked()
{
    int companyID = ui->cb_company->currentIndex();
    QString name = ui->le_name->text();
    if (!editMode) {
        //neu angelegte Sponosoren sind immer aktiv
        ui->cb_active->setChecked(true);
    };
    bool active = ui->cb_active->isChecked();
    QString since = ui->le_since->text();
    QString until = ui->le_until->text();
    QString type = ui->le_typ->text();
    QString street = ui->le_street->text();
    QString houseNumber = ui->le_houseNumber->text();
    QString city = ui->le_city->text();
    QString country = ui->le_country->text();
    QString info = ui->le_info->text();

    QSqlQuery insertCompanyQuery;
    if (editMode) {
        insertCompanyQuery.prepare("UPDATE firmen SET name = :name, aktiv = :active, seit = :since, bis = :until, Rang = :rank, Leistungstyp = :type, Str = :street, Hausnummer = :houseNumber, Ort = :city, PLZ = :zip, Land = :country, Infos = :info WHERE id = :companyID");
        insertCompanyQuery.bindValue(":companyID", companyID + 1);
    } else {
        insertCompanyQuery.prepare("INSERT INTO firmen(name, aktiv, seit, bis, Rang, Leistungstyp, Str, Hausnummer, Ort, PLZ, Land, Infos) VALUES (:name, :active, :since, :until, :rank, :type, :street, :houseNumber, :city, :zip, :country, :info)");
    }
    insertCompanyQuery.bindValue(":name", name);
    insertCompanyQuery.bindValue(":active", active);
    insertCompanyQuery.bindValue(":since", since);
    insertCompanyQuery.bindValue(":until", until);

    QString rank = "";
    if (ui->rb_gold->isChecked()) {
        rank = "Gold";
    } else if (ui->rb_silver->isChecked()) {
        rank = "Silber";
    } else if (ui->rb_bronze->isChecked()) {
        rank = "Bronze";
    } else if (ui->rb_supporter->isChecked()) {
        rank = "Supporter";
    }
    insertCompanyQuery.bindValue(":rank", rank);

    insertCompanyQuery.bindValue(":type", type);
    insertCompanyQuery.bindValue(":street", street);
    insertCompanyQuery.bindValue(":houseNumber", houseNumber);
    insertCompanyQuery.bindValue(":city", city);

    if (ui->le_zip->text() != "") {
        insertCompanyQuery.bindValue(":zip", ui->le_zip->text().toInt());
    } else {
        insertCompanyQuery.bindValue(":zip", QVariant(QMetaType::fromType<int>()));
    }

    insertCompanyQuery.bindValue(":country", country);
    insertCompanyQuery.bindValue(":info", info);

    insertCompanyQuery.exec();

    if (insertCompanyQuery.next()) {
        Error errorWindow;
        errorWindow.setText("QSQLITE error: " + insertCompanyQuery.lastError().text() + ",\nQSQLITE error code: " + insertCompanyQuery.lastError().nativeErrorCode());
        errorWindow.setModal(true);
        errorWindow.exec();
    } else {
        this->accept();
    }
}
