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

    Company::editMode = editMode;

    if (editMode) {
        QWidget::setWindowTitle("GLR Datenbank - Unternehmen bearbeiten");
        ui->l_dialogTitle->setText("GLR Datenbank - Unternehmen bearbeiten");

        QSqlQuery selectCompany;
        selectCompany.prepare("SELECT id, name FROM firmen");
        selectCompany.exec();

        while(selectCompany.next()) {
            ui->cb_company->addItem(selectCompany.value(1).toString(), selectCompany.value(0).toInt());
        }

        if (ui->cb_company->count() < 1) {
            ui->cb_company->setDisabled(true);
        }

        ui->le_name->setDisabled(true);
        ui->le_since->setDisabled(true);
        ui->le_until->setDisabled(true);
        ui->rb_gold->setDisabled(true);
        ui->rb_silver->setDisabled(true);
        ui->rb_bronze->setDisabled(true);
        ui->rb_supporter->setDisabled(true);
        ui->le_typ->setDisabled(true);
        ui->le_info->setDisabled(true);
        ui->le_address->setDisabled(true);

        ui->pb_okay->setDisabled(true);

    } else {
        QWidget::setWindowTitle("GLR Datenbank - Unternehmen hinzufügen");
        ui->l_dialogTitle->setText("GLR Datenbank - Unternehmen hinzufügen");

        ui->label_11->setVisible(false);
        ui->label_12->setVisible(false);
        ui->cb_company->setVisible(false);
    }
}

Company::~Company()
{
    delete ui;
}

void Company::on_cb_company_currentIndexChanged()
{
    QSqlQuery selectCompany;
    selectCompany.prepare("SELECT id, name, seit, bis, rang, leistungstyp, infos, anschrift FROM firmen WHERE id = :companyID");
    selectCompany.bindValue(":companyID", ui->cb_company->currentData().toInt());
    selectCompany.exec();
    selectCompany.next();

    ui->le_name->setDisabled(false);
    ui->le_since->setDisabled(false);
    ui->le_until->setDisabled(false);
    ui->rb_gold->setDisabled(false);
    ui->rb_silver->setDisabled(false);
    ui->rb_bronze->setDisabled(false);
    ui->rb_supporter->setDisabled(false);
    ui->le_typ->setDisabled(false);
    ui->le_info->setDisabled(false);
    ui->le_address->setDisabled(false);

    ui->pb_okay->setDisabled(false);

    ui->le_name->setText(selectCompany.value(1).toString());
    ui->le_since->setText(selectCompany.value(2).toString());
    ui->le_until->setText(selectCompany.value(3).toString());

    QString rank = selectCompany.value(4).toString();
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

    ui->le_typ->setText(selectCompany.value(5).toString());
    ui->le_info->setText(selectCompany.value(6).toString());
    ui->le_address->setText(selectCompany.value(7).toString());
}

void Company::on_pb_okay_clicked()
{
    int companyID = ui->cb_company->currentData().toInt();
    QString name = ui->le_name->text();
    QString since = ui->le_since->text();
    QString until = ui->le_until->text();
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
    QString type = ui->le_typ->text();
    QString info = ui->le_info->text();
    QString address = ui->le_address->text();

    QSqlQuery insertCompanyQuery;
    if (editMode) {
        insertCompanyQuery.prepare("UPDATE firmen SET name = :name, seit = :since, bis = :until, rang = :rank, leistungstyp = :type, infos = :info, anschrift = :address WHERE id = :companyID");
        insertCompanyQuery.bindValue(":companyID", companyID);
    } else {
        insertCompanyQuery.prepare("INSERT INTO firmen(name, seit, bis, rang, leistungstyp, infos, anschrift) VALUES (:name, :since, :until, :rank, :type, :info, :address)");
    }
    insertCompanyQuery.bindValue(":name", name);
    insertCompanyQuery.bindValue(":since", since);
    insertCompanyQuery.bindValue(":until", until);
    insertCompanyQuery.bindValue(":rank", rank);
    insertCompanyQuery.bindValue(":type", type);
    insertCompanyQuery.bindValue(":info", info);
    insertCompanyQuery.bindValue(":address", address);

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
