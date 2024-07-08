#include "member.h"
#include "ui_member.h"
#include "error.h"
#include <QFileDialog>

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
        ui->tb_add->setDisabled(true);

        ui->pb_okay->setDisabled(true);

    } else {
        QWidget::setWindowTitle("GLR Datenbank - Mitglied hinzufügen");
        ui->l_dialogTitle->setText("GLR Datenbank - Mitglied hinzufügen");

        ui->label_13->setVisible(false);
        ui->cb_member->setVisible(false);

        QObject::connect(ui->lw_changes, SIGNAL(itemSelectionChanged()), this, SLOT(selectionChanged()));
    }

    ui->lw_changes->setDisabled(true);
    ui->tb_remove->setDisabled(true);
    ui->le_since->setDisabled(true);
    ui->le_until->setDisabled(true);
    ui->le_position->setDisabled(true);
    ui->pb_signature_export->setDisabled(true);
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
        ui->pb_signature_export->setDisabled(false);
    } else {
        ui->lw_changes->setDisabled(true);
        ui->pb_signature_export->setDisabled(true);
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
    ui->pb_signature_export->setDisabled(false);
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
        ui->pb_signature_export->setDisabled(true);
    }
}

void Member::on_pb_signature_export_clicked() {
    QString fileName;
    QString fileContent;
    QFile file;

    QString firstName = "";
    QString surname = "";
    QString position = "";
    QString phone = "";
    QString mail = "";

    firstName = ui->le_first_name->text();

    surname = ui->le_surname->text();

    if (!ui->le_phone->text().isEmpty()) {
        phone = "<a href='tel:" + ui->le_phone->text() + "'>" + ui->le_phone->text() + "</a><br>";
    }

    if (!ui->le_email_glr->text().isEmpty()) {
        mail = "<a href='mailto:" + ui->le_email_glr->text() + "'>" + ui->le_email_glr->text() + "</a><br>";
    }

    if (editMode) {
        QSqlQuery selectMemberChangesQuery;
        selectMemberChangesQuery.prepare("SELECT id, mitglieder_id, position FROM mitglieder_aenderungen WHERE id = :id");
        selectMemberChangesQuery.bindValue(":id", ui->lw_changes->item(ui->lw_changes->count() - 1)->data(Qt::UserRole).toInt());
        selectMemberChangesQuery.exec();
        selectMemberChangesQuery.next();

        if (ui->lw_changes->currentIndex().row() != ui->lw_changes->count() - 1) {
            position = selectMemberChangesQuery.value(2).toString();
        } else {
            position = ui->le_position->text();
        }
    } else {
        if (ui->lw_changes->currentIndex().row() != ui->lw_changes->count() - 1) {
            position = ui->lw_changes->item(ui->lw_changes->count() - 1)->data(Qt::UserRole).toList()[2].toString();
        } else {
            position = ui->le_position->text();
        }
    }

    QString filter = "TXT Files (*.txt)";
    fileName = QFileDialog::getSaveFileName(this, tr("Signatur speichern"), "Signatur " + firstName + " " + surname + ".txt", filter, &filter);
    if (fileName == "")
        return;
    file.setFileName(fileName);

    fileContent = "<br>"
                  "Mit freundlichen Grüßen<br>"
                  "<br>"
                  "<b>" + firstName + " " + surname + "<br>" +
                  position + "</b><br>"
                  "<br>"
                  "<b><img alt='Green Lion Racing' src='data:image/png;base64,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'/></b><br>" +
                  "<br>"
                  "<i>Bergische Universität Wuppertal<br>"
                  "Lehrstuhl Konstruktion<br>"
                  "Raum W.08.40<br>"
                  "Gaußstraße 20, 42119 Wuppertal, Deutschland</i><br>"
                  "<br>" +
                  phone +
                  mail +
                  "<a href='https://glracing.de/'>glracing.de</a>";

    file.open(QIODevice::ReadWrite | QIODevice::Truncate);
    file.write(fileContent.toUtf8());
    file.close();
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
