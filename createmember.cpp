#include "createmember.h"
#include "ui_createmember.h"

createMember::createMember(QWidget *parent) :
    QDialog(parent/*,Qt::FramelessWindowHint*/),
    ui(new Ui::createMember)
{
    ui->setupUi(this);

    QWidget::setWindowTitle("GLR Datenbank - Mitglied hinzufügen");
}

createMember::~createMember()
{
    delete ui;
}

void createMember::on_pb_okay_clicked()
{
    QSqlQuery createMemberQuery("CREATE TABLE IF NOT EXISTS mitglieder (id INTEGER PRIMARY KEY, vorname TEXT, nachname TEXT, position TEXT, matrikelnummer TEXT, email_glr TEXT, email_privat TEXT, telefon TEXT, anschrift TEXT, hemdgroesse TEXT, vdi_nummer TEXT, sprache TEXT, aktiv BOOL)");

    QString firstName = ui->le_firstName->text();
    QString surname = ui->le_surname->text();
    QString position = ui->le_position->text();
    QString student_number = ui->le_student_number->text();
    QString email_glr = ui->le_email_glr->text();
    QString email_private = ui->le_email_private->text();
    QString shirt_size = ui->le_shirt_size->text();
    QString vdi_number = ui->le_vdi_number->text();
    QString phone = ui->le_phone->text();
    QString address = ui->le_address->text();
    QString language = ui->le_language->text();
    bool activ = 1;     //neu angelegte Objekte immer aktiv
    QSqlQuery insertMemberQuery;

    insertMemberQuery.prepare("INSERT INTO mitglieder (vorname, nachname, position, matrikelnummer, email_glr, email_privat, telefon, anschrift, hemdgroesse, vdi_nummer, sprache, aktiv) VALUES (:firstName, :surname, :position, :student_number, :email_glr, :email_private, :phone, :address, :shirt_size, :vdi_number, :language, :activ)");
    insertMemberQuery.bindValue(":firstName", firstName);
    insertMemberQuery.bindValue(":surname", surname);
    insertMemberQuery.bindValue(":position", position);
    insertMemberQuery.bindValue(":student_number", student_number);
    insertMemberQuery.bindValue(":email_glr", email_glr);
    insertMemberQuery.bindValue(":email_private", email_private);
    insertMemberQuery.bindValue(":phone", phone);
    insertMemberQuery.bindValue(":address", address);
    insertMemberQuery.bindValue(":shirt_size", shirt_size);
    insertMemberQuery.bindValue(":vdi_number", vdi_number);
    insertMemberQuery.bindValue(":language", language);
    insertMemberQuery.bindValue(":activ", activ);
    insertMemberQuery.exec();

    /*
    if (insertMemberQuery.next())
    {
    } else {
        qDebug() << "QSQLITE error:" << insertMemberQuery.lastError().text() << ", QSQLITE error code:" << insertMemberQuery.lastError().number();
    }
    */

    this->accept();
}
