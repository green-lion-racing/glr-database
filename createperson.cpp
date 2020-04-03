#include "createperson.h"
#include "ui_createperson.h"

createPerson::createPerson(QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint),
    ui(new Ui::createPerson)
{
    ui->setupUi(this);

    QWidget::setWindowTitle("GLR Sponsorendatenbank - Person hinzufügen");

    ui->cb_you->addItem("Du");
    ui->cb_you->addItem("Sie");

    QSqlQuery selectName;
    selectName.prepare("SELECT name FROM firmen");
    selectName.exec();
    QSqlQueryModel * modal = new QSqlQueryModel();
    modal->setQuery(selectName);
    ui->cb_company->setModel(modal);
}

createPerson::~createPerson()
{
    delete ui;
}

void createPerson::on_buttonBox_accepted()
{
    //QSqlQuery createPersonQuery("CREATE TABLE IF NOT EXISTS personen (id INTEGER PRIMARY KEY, firma TEXT,titel TEXT, vorname TEXT, nachname TEXT, telefon TEXT, fax TEXT, email TEXT, Position TEXT, du_sie TEXT, sprache TEXT, aktiv BOOL, FOREIGN KEY (firma) REFERENCES firmen(name))");
    QSqlQuery createPersonQuery("CREATE TABLE IF NOT EXISTS personen (id INTEGER PRIMARY KEY, firma TEXT,titel TEXT, vorname TEXT, nachname TEXT, telefon TEXT, fax TEXT, email TEXT, Position TEXT, du_sie TEXT, sprache TEXT, aktiv BOOL, FirmenID INTEGER, FOREIGN KEY (FirmenID) REFERENCES firmen(id))");
    QString firstName = ui->le_firstName->text();
    bool activ = 1;     //neu angelgte Personen immer aktiv

    QString title = ui->le_title->text();
    QString surname = ui->le_surname->text();
    QString phone = ui->le_phone->text();
    QString fax = ui->le_fax->text();
    QString email = ui->le_email->text();
    QString position = ui->le_position->text();
    QString you = ui->cb_you->currentText();
    QString companyName = ui->cb_company->currentText();
    QString language = ui->le_language->text();
    QSqlQuery insertPersonQuery;

    QSqlQuery selectId;
    selectId.prepare("SELECT id FROM firmen WHERE name = :companyName");
    selectId.bindValue(":companyName", companyName);
    selectId.exec();
    int companyId = 0;
    while(selectId.next())
        companyId = (selectId.value(0).toString()).toInt();

    insertPersonQuery.prepare("INSERT INTO personen(firma, titel, vorname, nachname, telefon, fax, email, Position, du_sie, sprache, aktiv, FirmenID) VALUES (:companyName, :title, :firstName, :surname, :phone, :fax, :email, :position, :you, :language, :activ, :companyId)");
    insertPersonQuery.bindValue(":companyName", companyName);
    insertPersonQuery.bindValue(":title", title);
    insertPersonQuery.bindValue(":firstName", firstName);
    insertPersonQuery.bindValue(":surname", surname);
    insertPersonQuery.bindValue(":phone", phone);
    insertPersonQuery.bindValue(":fax", fax);
    insertPersonQuery.bindValue(":email", email);
    insertPersonQuery.bindValue(":position", position);
    insertPersonQuery.bindValue(":you", you);
    insertPersonQuery.bindValue(":language", language);
    insertPersonQuery.bindValue(":activ", activ);
    insertPersonQuery.bindValue(":companyId", companyId);

    insertPersonQuery.exec();

    if (insertPersonQuery.next())
    {
    } else {
        qDebug() << "SqLite error:" << insertPersonQuery.lastError().text() << ", SqLite error code:" << insertPersonQuery.lastError().number();
    }

}
