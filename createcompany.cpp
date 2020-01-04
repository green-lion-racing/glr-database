#include "createcompany.h"
#include "ui_createcompany.h"
#include <QString>
#include <QVector>
#include "error.h"

createCompany::createCompany(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createCompany)
{
    ui->setupUi(this);

    QWidget::setWindowTitle("GLR Sponsorendatenbank - Unternehmen hinzufügen");
}

createCompany::~createCompany()
{
    delete ui;
}

void createCompany::on_buttonBox_accepted()
{
    bool nameIsNotDistinct = 0;
    QSqlQuery createCompanyQquery("CREATE TABLE IF NOT EXISTS firmen (id INTEGER PRIMARY KEY, name TEXT, aktiv BOOL, seit TEXT, bis TEXT, Rang TEXT, Leistungstyp TEXT, Str TEXT, Hausnummer TEXT, Ort TEXT, PLZ INTEGER, Land TEXT, Infos TEXT)");
    QString name = ui->le_name->text();
    bool activ = 1;     //neu angelegte Sponosoren sind immer aktiv

    QString since = ui->le_since->text();
    QString until = ui->le_until->text();
    QString type = ui->le_typ->text();
    QString street = ui->le_street->text();
    QString houseNumber = ui->le_houseNumber->text();
    QString city = ui->le_city->text();
    int zip = (ui->le_zip->text()).toInt();
    QString country = ui->le_country->text();
    QString info = ui->le_info->text();

    QSqlQuery insertCompanyQuery;

    insertCompanyQuery.prepare("INSERT INTO firmen(name, aktiv, seit, bis, Leistungstyp, Str, Hausnummer, Ort, PLZ, Land, Infos) VALUES (:name, :activ, :since, :until, :type, :street, :houseNumber, :city, :zip, :country, :info)");
    insertCompanyQuery.bindValue(":name", name);
    insertCompanyQuery.bindValue(":activ", activ);
    insertCompanyQuery.bindValue(":since", since);
    insertCompanyQuery.bindValue(":until", until);
    insertCompanyQuery.bindValue(":type", type);
    insertCompanyQuery.bindValue(":street", street);
    insertCompanyQuery.bindValue(":houseNumber", houseNumber);
    insertCompanyQuery.bindValue(":city", city);
    insertCompanyQuery.bindValue(":zip", zip);
    insertCompanyQuery.bindValue(":country", country);
    insertCompanyQuery.bindValue(":info", info);

    QSqlQuery selectName;
    QVector<QString> allCompanyNames;
    selectName.prepare("SELECT name FROM firmen");
    selectName.exec();
    while (selectName.next()) {
        allCompanyNames.push_back(selectName.value(0).toString());
    }

    for (int i = 0; i < allCompanyNames.size(); i++) {
        if (allCompanyNames[i] == name)
            nameIsNotDistinct = 1;
    }

    if (!nameIsNotDistinct)
        insertCompanyQuery.exec();
    else {
        error errorWindow;
        errorWindow.setModal(true);
        errorWindow.exec();
    }
}
