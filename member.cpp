#include "member.h"
#include "ui_member.h"
#include "error.h"

Member::Member(QWidget *parent, bool editMode) :
    QDialog(parent),
    ui(new Ui::Member)
{
    ui->setupUi(this);

    QSqlQuery  MemberQuery("CREATE TABLE IF NOT EXISTS mitglieder (id INTEGER PRIMARY KEY, vorname TEXT, nachname TEXT, position TEXT, matrikelnummer TEXT, email_glr TEXT, email_privat TEXT, telefon TEXT, anschrift TEXT, hemdgroesse TEXT, vdi_nummer TEXT, sprache TEXT, aktiv BOOL)");

    Member::editMode = editMode;

    QVector<QString> memberNames;

    if (editMode) {
        QWidget::setWindowTitle("GLR Datenbank - Mitglied bearbeiten");
        ui->l_dialogTitle->setText("GLR Datenbank - Mitglied bearbeiten");

        QSqlQuery selectMember;
        selectMember.prepare("SELECT id, vorname, nachname FROM mitglieder");
        selectMember.exec();

        while(selectMember.next()) {
            memberNames.push_back(selectMember.value(0).toString() + " - " + selectMember.value(1).toString() + " " + selectMember.value(2).toString());
        }

        for (int i = 0; i < memberNames.size(); i++) {
            ui->cb_member->addItem(memberNames[i]);
        }

        if (memberNames.size() < 1) {
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
        ui->le_language->setDisabled(true);
        ui->le_shirt_size->setDisabled(true);
        ui->le_vdi_number->setDisabled(true);
        ui->cb_active->setDisabled(true);

        ui->pb_okay->setDisabled(true);

    } else {
        QWidget::setWindowTitle("GLR Datenbank - Mitglied hinzufügen");
        ui->l_dialogTitle->setText("GLR Datenbank - Mitglied hinzufügen");

        ui->label_13->setVisible(false);
        ui->label_14->setVisible(false);
        ui->cb_member->setVisible(false);
        ui->cb_active->setVisible(false);
    }
}

Member::~Member()
{
    delete ui;
}

void Member::on_cb_member_currentTextChanged()
{
    QSqlQuery selectMember;

    static QRegularExpression regex(" - ");
    int mitgliederID = ui->cb_member->currentText().split(regex)[0].toInt();

    selectMember.prepare("SELECT * FROM mitglieder WHERE id = :mitgliederID");
    selectMember.bindValue(":mitgliederID", mitgliederID);
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
    ui->le_language->setDisabled(false);
    ui->le_shirt_size->setDisabled(false);
    ui->le_vdi_number->setDisabled(false);
    ui->cb_active->setDisabled(false);

    ui->pb_okay->setDisabled(false);

    ui->le_first_name->setText(selectMember.value(1).toString());
    ui->le_surname->setText(selectMember.value(2).toString());
    ui->le_position->setText(selectMember.value(3).toString());
    ui->le_student_number->setText(selectMember.value(4).toString());
    ui->le_email_glr->setText(selectMember.value(5).toString());
    ui->le_email_private->setText(selectMember.value(6).toString());
    ui->le_phone->setText(selectMember.value(7).toString());
    ui->le_address->setText(selectMember.value(8).toString());
    ui->le_language->setText(selectMember.value(11).toString());
    ui->le_shirt_size->setText(selectMember.value(9).toString());
    ui->le_vdi_number->setText(selectMember.value(10).toString());
    ui->cb_active->setChecked(selectMember.value(12).toBool());
}

void Member::on_pb_okay_clicked()
{
    int memberID =  ui->cb_member->currentIndex();
    QString first_name = ui->le_first_name->text();
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
    bool active = 1;     //neu angelegte Objekte immer aktiv

    QSqlQuery insertMemberQuery;
    if (editMode) {
        insertMemberQuery.prepare("UPDATE mitglieder SET vorname = :first_name, nachname = :surname, position = :position, matrikelnummer = :student_number, email_glr = :email_glr, email_privat = :email_private, telefon = :phone, anschrift = :address, hemdgroesse = :shirt_size, vdi_nummer = :vdi_number, sprache = :language, aktiv = :active WHERE id = :memberID");
        insertMemberQuery.bindValue(":memberID", memberID + 1);
    } else {
        insertMemberQuery.prepare("INSERT INTO mitglieder (vorname, nachname, position, matrikelnummer, email_glr, email_privat, telefon, anschrift, hemdgroesse, vdi_nummer, sprache, aktiv) VALUES (:first_name, :surname, :position, :student_number, :email_glr, :email_private, :phone, :address, :shirt_size, :vdi_number, :language, :active)");
    }
    insertMemberQuery.bindValue(":first_name", first_name);
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
    insertMemberQuery.bindValue(":active", active);
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
