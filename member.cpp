#include "member.h"
#include "ui_member.h"
#include "error.h"

Member::Member(QWidget *parent, bool editMode) :
    QDialog(parent),
    ui(new Ui::Member)
{
    ui->setupUi(this);

    Member::editMode = editMode;

    if (editMode) {
        QWidget::setWindowTitle("GLR Datenbank - Mitglied bearbeiten");
        ui->l_dialogTitle->setText("GLR Datenbank - Mitglied bearbeiten");

        QSqlQuery selectMember;
        selectMember.prepare("SELECT id, vorname, nachname FROM mitglieder");
        selectMember.exec();

        while(selectMember.next()) {
            ui->cb_member->addItem(selectMember.value(1).toString() + " " + selectMember.value(2).toString(), selectMember.value(0).toInt());
        }

        if (ui->cb_member->count() < 1) {
            ui->cb_member->setDisabled(true);
        }

        ui->le_first_name->setDisabled(true);
        ui->le_surname->setDisabled(true);
        ui->le_position->setDisabled(true);
        ui->le_student_number->setDisabled(true);
        ui->le_email_glr->setDisabled(true);
        ui->le_email_private->setDisabled(true);
        ui->le_phone->setDisabled(true);
        ui->le_address->setDisabled(true);
        ui->le_shirt_size->setDisabled(true);
        ui->le_vdi_number->setDisabled(true);
        ui->le_language->setDisabled(true);

        ui->pb_okay->setDisabled(true);

    } else {
        QWidget::setWindowTitle("GLR Datenbank - Mitglied hinzufügen");
        ui->l_dialogTitle->setText("GLR Datenbank - Mitglied hinzufügen");

        ui->label_13->setVisible(false);
        ui->label_14->setVisible(false);
        ui->cb_member->setVisible(false);
    }
}

Member::~Member()
{
    delete ui;
}

void Member::on_cb_member_currentIndexChanged()
{
    QSqlQuery selectMember;
    selectMember.prepare("SELECT id, vorname, nachname, position, matrikelnummer, email_glr, email_privat, telefon, anschrift, hemdgroesse, vdi_nummer, sprache FROM mitglieder WHERE id = :mitgliederID");
    selectMember.bindValue(":mitgliederID", ui->cb_member->currentData().toInt());
    selectMember.exec();
    selectMember.next();

    ui->le_first_name->setDisabled(false);
    ui->le_surname->setDisabled(false);
    ui->le_position->setDisabled(false);
    ui->le_student_number->setDisabled(false);
    ui->le_email_glr->setDisabled(false);
    ui->le_email_private->setDisabled(false);
    ui->le_phone->setDisabled(false);
    ui->le_address->setDisabled(false);
    ui->le_shirt_size->setDisabled(false);
    ui->le_vdi_number->setDisabled(false);
    ui->le_language->setDisabled(false);

    ui->pb_okay->setDisabled(false);

    ui->le_first_name->setText(selectMember.value(1).toString());
    ui->le_surname->setText(selectMember.value(2).toString());
    ui->le_position->setText(selectMember.value(3).toString());
    ui->le_student_number->setText(selectMember.value(4).toString());
    ui->le_email_glr->setText(selectMember.value(5).toString());
    ui->le_email_private->setText(selectMember.value(6).toString());
    ui->le_phone->setText(selectMember.value(7).toString());
    ui->le_address->setText(selectMember.value(8).toString());
    ui->le_shirt_size->setText(selectMember.value(9).toString());
    ui->le_vdi_number->setText(selectMember.value(10).toString());
    ui->le_language->setText(selectMember.value(11).toString());
}

void Member::on_pb_okay_clicked()
{
    int memberID =  ui->cb_member->currentData().toInt();
    QString firstName = ui->le_first_name->text();
    QString surname = ui->le_surname->text();
    QString position = ui->le_position->text();
    QString studentNumber = ui->le_student_number->text();
    QString emailGLR = ui->le_email_glr->text();
    QString emailPrivate = ui->le_email_private->text();
    QString phone = ui->le_phone->text();
    QString address = ui->le_address->text();
    QString shirtSize = ui->le_shirt_size->text();
    QString vdiNumber = ui->le_vdi_number->text();
    QString language = ui->le_language->text();

    QSqlQuery insertMemberQuery;
    if (editMode) {
        insertMemberQuery.prepare("UPDATE mitglieder SET vorname = :firstName, nachname = :surname, position = :position, matrikelnummer = :studentNumber, email_glr = :emailGLR, email_privat = :emailPrivate, telefon = :phone, anschrift = :address, hemdgroesse = :shirtSize, vdi_nummer = :vdiNumber, sprache = :language WHERE id = :memberID");
        insertMemberQuery.bindValue(":memberID", memberID);
    } else {
        insertMemberQuery.prepare("INSERT INTO mitglieder (vorname, nachname, position, matrikelnummer, email_glr, email_privat, telefon, anschrift, hemdgroesse, vdi_nummer, sprache) VALUES (:firstName, :surname, :position, :studentNumber, :emailGLR, :emailPrivate, :phone, :address, :shirtSize, :vdiNumber, :language)");
    }
    insertMemberQuery.bindValue(":firstName", firstName);
    insertMemberQuery.bindValue(":surname", surname);
    insertMemberQuery.bindValue(":position", position);
    insertMemberQuery.bindValue(":studentNumber", studentNumber);
    insertMemberQuery.bindValue(":emailGLR", emailGLR);
    insertMemberQuery.bindValue(":emailPrivate", emailPrivate);
    insertMemberQuery.bindValue(":phone", phone);
    insertMemberQuery.bindValue(":address", address);
    insertMemberQuery.bindValue(":shirtSize", shirtSize);
    insertMemberQuery.bindValue(":vdiNumber", vdiNumber);
    insertMemberQuery.bindValue(":language", language);
    insertMemberQuery.exec();

    if (insertMemberQuery.next()) {
        Error errorWindow;
        errorWindow.setText("QSQLITE error: " + insertMemberQuery.lastError().text() + ",\nQSQLITE error code: " + insertMemberQuery.lastError().nativeErrorCode());
        errorWindow.setModal(true);
        errorWindow.exec();
    } else {
        this->accept();
    }
}
