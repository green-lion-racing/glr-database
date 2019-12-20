#include "createcompany.h"
#include "ui_createcompany.h"
#include <QString>

createCompany::createCompany(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createCompany)
{
    ui->setupUi(this);
    /*
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("sponsorendatenbank.db");

    db.open();
    */
}

createCompany::~createCompany()
{
    delete ui;
}

void createCompany::on_buttonBox_accepted()
{
    QSqlQuery createCompanyQquery("CREATE TABLE IF NOT EXISTS firmen (id INTEGER PRIMARY KEY, name TEXT, aktiv BOOL, seit TEXT, bis TEXT, Rang TEXT, Leistungstyp TEXT, Infos TEXT)");
    QString name = ui->le_name->text();
    bool activ = 1;     //neu angelegte Sponosoren sind immer aktiv

    QString since = ui->le_since->text();
    QString until = ui->le_until->text();
    QString type = ui->le_typ->text();
    QString info = ui->le_info->text();
    QSqlQuery insertCompanyQuery;
    insertCompanyQuery.prepare("INSERT INTO firmen(name, aktiv, seit, bis, Leistungstyp, Infos) VALUES (:name, :activ, :since, :until, :type, :info)");
    insertCompanyQuery.bindValue(":name", name);
    insertCompanyQuery.bindValue(":activ", activ);
    insertCompanyQuery.bindValue(":since", since);
    insertCompanyQuery.bindValue(":until", until);
    insertCompanyQuery.bindValue(":type", type);
    insertCompanyQuery.bindValue(":info", info);

    insertCompanyQuery.exec();
}
