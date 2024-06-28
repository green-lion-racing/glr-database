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
        ui->le_student_number->setDisabled(true);
        ui->le_email_glr->setDisabled(true);
        ui->le_email_private->setDisabled(true);
        ui->le_phone->setDisabled(true);
        ui->le_address->setDisabled(true);
        ui->le_shirt_size->setDisabled(true);
        ui->le_vdi_number->setDisabled(true);
        ui->le_language->setDisabled(true);
        ui->lw_changes->setDisabled(true);
        ui->tb_add->setDisabled(true);
        ui->tb_remove->setDisabled(true);
        ui->le_since->setDisabled(true);
        ui->le_until->setDisabled(true);
        ui->le_position->setDisabled(true);

        ui->pb_okay->setDisabled(true);

    } else {
        QWidget::setWindowTitle("GLR Datenbank - Mitglied hinzufügen");
        ui->l_dialogTitle->setText("GLR Datenbank - Mitglied hinzufügen");

        ui->label_13->setVisible(false);
        ui->cb_member->setVisible(false);
        ui->tb_remove->setDisabled(true);
        ui->lw_changes->setDisabled(true);
        ui->le_since->setDisabled(true);
        ui->le_until->setDisabled(true);
        ui->le_position->setDisabled(true);

        QObject::connect(ui->lw_changes, SIGNAL(itemSelectionChanged()), this, SLOT(selectionChanged()));
    }
}

Member::~Member()
{
    delete ui;
}

void Member::on_cb_member_currentIndexChanged()
{
    QSqlQuery selectMember;
    selectMember.prepare("SELECT id, vorname, nachname, matrikelnummer, email_glr, email_privat, telefon, anschrift, hemdgroesse, vdi_nummer, sprache FROM mitglieder WHERE id = :mitgliederID");
    selectMember.bindValue(":mitgliederID", ui->cb_member->currentData().toInt());
    selectMember.exec();
    selectMember.next();

    QSqlQuery selectMemberChanges;
    selectMemberChanges.prepare("SELECT id, mitglieder_id, von, bis, position FROM mitglieder_aenderungen WHERE mitglieder_id = :memberID");
    selectMemberChanges.bindValue(":memberID", ui->cb_member->currentData().toInt());
    selectMemberChanges.exec();

    ui->lw_changes->clear();
    while (selectMemberChanges.next()) {
        QListWidgetItem* item = new QListWidgetItem(selectMemberChanges.value(2).toString() + " - " + selectMemberChanges.value(3).toString() + ", " + selectMemberChanges.value(4).toString());
        item->setData(Qt::UserRole, selectMemberChanges.value(0).toInt());
        ui->lw_changes->addItem(item);
    }

    QObject::connect(ui->lw_changes, SIGNAL(itemSelectionChanged()), this, SLOT(selectionChanged()));

    ui->le_first_name->setDisabled(false);
    ui->le_surname->setDisabled(false);
    ui->le_student_number->setDisabled(false);
    ui->le_email_glr->setDisabled(false);
    ui->le_email_private->setDisabled(false);
    ui->le_phone->setDisabled(false);
    ui->le_address->setDisabled(false);
    ui->le_shirt_size->setDisabled(false);
    ui->le_vdi_number->setDisabled(false);
    ui->le_language->setDisabled(false);
    ui->tb_add->setDisabled(false);
    ui->tb_remove->setDisabled(true);

    if (ui->lw_changes->count() > 0) {
        ui->lw_changes->setDisabled(false);
    } else {
        ui->lw_changes->setDisabled(true);
    }

    ui->le_since->setDisabled(true);
    ui->le_until->setDisabled(true);
    ui->le_position->setDisabled(true);

    ui->pb_okay->setDisabled(false);

    ui->le_first_name->setText(selectMember.value(1).toString());
    ui->le_surname->setText(selectMember.value(2).toString());
    ui->le_student_number->setText(selectMember.value(3).toString());
    ui->le_email_glr->setText(selectMember.value(4).toString());
    ui->le_email_private->setText(selectMember.value(5).toString());
    ui->le_phone->setText(selectMember.value(6).toString());
    ui->le_address->setText(selectMember.value(7).toString());
    ui->le_shirt_size->setText(selectMember.value(8).toString());
    ui->le_vdi_number->setText(selectMember.value(9).toString());
    ui->le_language->setText(selectMember.value(10).toString());

    ui->le_since->setText("");
    ui->le_until->setText("");
    ui->le_position->setText("");

    selected = NULL;
}


void Member::on_tb_add_clicked() {
    ui->lw_changes->setDisabled(false);
    if (editMode) {
        QSqlQuery insertMemberChangesQuery;
        insertMemberChangesQuery.prepare("INSERT INTO mitglieder_aenderungen(mitglieder_id, von, bis, position) VALUES (:mitgliederID, '', '', '')");
        insertMemberChangesQuery.bindValue(":mitgliederID", ui->cb_member->currentData().toInt());
        insertMemberChangesQuery.exec();
        int id = insertMemberChangesQuery.lastInsertId().toInt();

        QListWidgetItem* item = new QListWidgetItem(" - , ");
        item->setData(Qt::UserRole, id);
        ui->lw_changes->addItem(item);
        ui->lw_changes->setCurrentItem(item);
    } else {
        QListWidgetItem* item = new QListWidgetItem(" - , ");
        QList<QVariant> list;
        list.append("");
        list.append("");
        list.append("");
        list.append("");
        item->setData(Qt::UserRole, list);
        ui->lw_changes->addItem(item);
        ui->lw_changes->setCurrentItem(item);
    }
}

void Member::on_tb_remove_clicked() {
    if (editMode) {
        QSqlQuery removeMemberChanges;
        removeMemberChanges.prepare("DELETE FROM mitglieder_aenderungen WHERE id = :id");
        removeMemberChanges.bindValue(":id", selected->data(Qt::UserRole).toInt());
        removeMemberChanges.exec();

        QListWidgetItem *temp = selected;
        selected = NULL;
        ui->lw_changes->takeItem(ui->lw_changes->row(temp));
    } else {
        QListWidgetItem *temp = selected;
        selected = NULL;
        ui->lw_changes->takeItem(ui->lw_changes->row(temp));
    }
    if (ui->lw_changes->count() == 0) {
        ui->lw_changes->setDisabled(true);
        ui->tb_remove->setDisabled(true);
    }
}

void Member::on_pb_okay_clicked()
{
    QSqlQuery insertMemberQuery;
    if (editMode) {
        insertMemberQuery.prepare("UPDATE mitglieder SET vorname = :firstName, nachname = :surname, matrikelnummer = :studentNumber, email_glr = :emailGLR, email_privat = :emailPrivate, telefon = :phone, anschrift = :address, hemdgroesse = :shirtSize, vdi_nummer = :vdiNumber, sprache = :language WHERE id = :memberID");
        insertMemberQuery.bindValue(":memberID", ui->cb_member->currentData().toInt());

        if (selected != NULL) {
            QSqlQuery submitMemberChanges;
            submitMemberChanges.prepare("UPDATE mitglieder_aenderungen SET von = :since, bis = :until, position = :position WHERE id = :id");
            submitMemberChanges.bindValue(":id", selected->data(Qt::UserRole).toInt());
            submitMemberChanges.bindValue(":since", ui->le_since->text());
            submitMemberChanges.bindValue(":until", ui->le_until->text());
            submitMemberChanges.bindValue(":position", ui->le_position->text());
            submitMemberChanges.exec();
        }
    } else {
        insertMemberQuery.prepare("INSERT INTO mitglieder (vorname, nachname, matrikelnummer, email_glr, email_privat, telefon, anschrift, hemdgroesse, vdi_nummer, sprache) VALUES (:firstName, :surname, :studentNumber, :emailGLR, :emailPrivate, :phone, :address, :shirtSize, :vdiNumber, :language)");
    }
    insertMemberQuery.bindValue(":firstName", ui->le_first_name->text());
    insertMemberQuery.bindValue(":surname", ui->le_surname->text());
    insertMemberQuery.bindValue(":studentNumber", ui->le_student_number->text());
    insertMemberQuery.bindValue(":emailGLR", ui->le_email_glr->text());
    insertMemberQuery.bindValue(":emailPrivate", ui->le_email_private->text());
    insertMemberQuery.bindValue(":phone", ui->le_phone->text());
    insertMemberQuery.bindValue(":address", ui->le_address->text());
    insertMemberQuery.bindValue(":shirtSize", ui->le_shirt_size->text());
    insertMemberQuery.bindValue(":vdiNumber", ui->le_vdi_number->text());
    insertMemberQuery.bindValue(":language", ui->le_language->text());
    insertMemberQuery.exec();

    if (!editMode && ui->lw_changes->count() > 0) {
        int id = insertMemberQuery.lastInsertId().toInt();

        QList<QVariant> list;
        list.append(ui->le_since->text());
        list.append(ui->le_until->text());
        list.append(ui->le_position->text());
        ui->lw_changes->currentItem()->setData(Qt::UserRole, list);

        foreach (QListWidgetItem* listItem, ui->lw_changes->findItems("*", Qt::MatchWildcard)) {
            QList<QVariant> list = listItem->data(Qt::UserRole).toList();

            QSqlQuery insertMemberChangesQuery;
            insertMemberChangesQuery.prepare("INSERT INTO mitglieder_aenderungen(mitglieder_id, von, bis, position) VALUES (:memberID, :since, :until, :position)");
            insertMemberChangesQuery.bindValue(":memberID", id);
            insertMemberChangesQuery.bindValue(":since", list.at(0).toString());
            insertMemberChangesQuery.bindValue(":until", list.at(1).toString());
            insertMemberChangesQuery.bindValue(":position", list.at(2).toString());
            insertMemberChangesQuery.exec();
        }
    }

    if (insertMemberQuery.next()) {
        Error errorWindow;
        errorWindow.setText("QSQLITE error: " + insertMemberQuery.lastError().text() + ",\nQSQLITE error code: " + insertMemberQuery.lastError().nativeErrorCode());
        errorWindow.setModal(true);
        errorWindow.exec();
    } else {
        this->accept();
    }
}

void Member::selectionChanged() {
    // update previous data
    if (selected != NULL) {
        if (editMode) {
            QSqlQuery submitMemberChanges;
            submitMemberChanges.prepare("UPDATE mitglieder_aenderungen SET von = :since, bis = :until, position = :position WHERE id = :id");

            submitMemberChanges.bindValue(":id", selected->data(Qt::UserRole).toInt());
            submitMemberChanges.bindValue(":since", ui->le_since->text());
            submitMemberChanges.bindValue(":until", ui->le_until->text());
            submitMemberChanges.bindValue(":position", ui->le_position->text());
            submitMemberChanges.exec();

            QSqlQuery selectMemberChanges;
            selectMemberChanges.prepare("SELECT id, mitglieder_id, von, bis, position FROM mitglieder_aenderungen WHERE id = :id");
            selectMemberChanges.bindValue(":id", selected->data(Qt::UserRole).toInt());
            selectMemberChanges.exec();
            selectMemberChanges.next();

            selected->setText(selectMemberChanges.value(2).toString() + " - " + selectMemberChanges.value(3).toString() + ", " + selectMemberChanges.value(4).toString());
        } else {
            QList<QVariant> list;
            list.append(ui->le_since->text());
            list.append(ui->le_until->text());
            list.append(ui->le_position->text());
            selected->setData(Qt::UserRole, list);
            selected->setText(ui->le_since->text() + " - " + ui->le_until->text() + ", " + ui->le_position->text());
        }
    }

    // set new data
    if (ui->lw_changes->currentItem() != NULL) {
        if (editMode) {
            QSqlQuery selectMemberChanges;
            selectMemberChanges.prepare("SELECT id, mitglieder_id, von, bis, position FROM mitglieder_aenderungen WHERE id = :id");

            selectMemberChanges.bindValue(":id", ui->lw_changes->currentItem()->data(Qt::UserRole).toInt());
            selectMemberChanges.exec();
            selectMemberChanges.next();

            ui->tb_remove->setDisabled(false);
            ui->le_since->setDisabled(false);
            ui->le_until->setDisabled(false);
            ui->le_position->setDisabled(false);

            ui->le_since->setText(selectMemberChanges.value(2).toString());
            ui->le_until->setText(selectMemberChanges.value(3).toString());
            ui->le_position->setText(selectMemberChanges.value(4).toString());
        } else {
            QList<QVariant> list = ui->lw_changes->currentItem()->data(Qt::UserRole).toList();
            ui->tb_remove->setDisabled(false);
            ui->le_since->setDisabled(false);
            ui->le_until->setDisabled(false);
            ui->le_position->setDisabled(false);

            ui->le_since->setText(list.at(0).toString());
            ui->le_until->setText(list.at(1).toString());
            ui->le_position->setText(list.at(2).toString());
        }
    } else {
        ui->tb_remove->setDisabled(true);
        ui->le_since->setDisabled(true);
        ui->le_until->setDisabled(true);
        ui->le_position->setDisabled(true);

        ui->le_since->setText("");
        ui->le_until->setText("");
        ui->le_position->setText("");
    }

    selected = ui->lw_changes->currentItem();
}
