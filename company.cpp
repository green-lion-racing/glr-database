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
        ui->lw_changes->setDisabled(true);
        ui->tb_add->setDisabled(true);
        ui->tb_remove->setDisabled(true);
        ui->pb_okay->setDisabled(true);

    } else {
        QWidget::setWindowTitle("GLR Datenbank - Unternehmen hinzufügen");
        ui->l_dialogTitle->setText("GLR Datenbank - Unternehmen hinzufügen");

        ui->label_11->setVisible(false);
        ui->cb_company->setVisible(false);
        ui->tb_remove->setDisabled(true);

        QObject::connect(ui->lw_changes, SIGNAL(itemSelectionChanged()), this, SLOT(selectionChanged()));
    }
}

Company::~Company()
{
    delete ui;
}

void Company::on_cb_company_currentIndexChanged()
{
    QSqlQuery selectCompany;
    selectCompany.prepare("SELECT id, name, infos, anschrift FROM firmen WHERE id = :companyID");
    selectCompany.bindValue(":companyID", ui->cb_company->currentData().toInt());
    selectCompany.exec();
    selectCompany.next();

    QSqlQuery selectCompanyChanges;
    selectCompanyChanges.prepare("SELECT id, firmen_id, von, bis, rang, leistungstyp FROM firmen_aenderungen WHERE firmen_id = :companyID");
    selectCompanyChanges.bindValue(":companyID", ui->cb_company->currentData().toInt());
    selectCompanyChanges.exec();

    ui->lw_changes->clear();
    while (selectCompanyChanges.next()) {
        QListWidgetItem* item = new QListWidgetItem(selectCompanyChanges.value(2).toString() + " - " + selectCompanyChanges.value(3).toString() + ", " + selectCompanyChanges.value(4).toString() + ", " + selectCompanyChanges.value(5).toString());
        item->setData(Qt::UserRole, selectCompanyChanges.value(0).toInt());
        ui->lw_changes->addItem(item);
    }

    QObject::connect(ui->lw_changes, SIGNAL(itemSelectionChanged()), this, SLOT(selectionChanged()));

    ui->le_name->setDisabled(false);
    ui->le_info->setDisabled(false);
    ui->le_address->setDisabled(false);
    ui->tb_add->setDisabled(false);

    if (ui->lw_changes->count() > 0) {
        ui->lw_changes->setDisabled(false);
        ui->tb_remove->setDisabled(false);
    }

    ui->le_since->setDisabled(true);
    ui->le_until->setDisabled(true);
    ui->rb_gold->setDisabled(true);
    ui->rb_silver->setDisabled(true);
    ui->rb_bronze->setDisabled(true);
    ui->rb_supporter->setDisabled(true);
    ui->le_typ->setDisabled(true);

    ui->pb_okay->setDisabled(false);

    ui->le_name->setText(selectCompany.value(1).toString());
    ui->le_info->setText(selectCompany.value(2).toString());
    ui->le_address->setText(selectCompany.value(3).toString());

    ui->le_since->setText("");
    ui->le_until->setText("");

    ui->buttonGroup->setExclusive(false);
    ui->rb_gold->setChecked(false);
    ui->rb_silver->setChecked(false);
    ui->rb_bronze->setChecked(false);
    ui->rb_supporter->setChecked(false);
    ui->buttonGroup->setExclusive(true);

    ui->le_typ->setText("");

    selected = NULL;
}


void Company::on_tb_add_clicked() {
    if (editMode) {
        QSqlQuery insertCompanyChangesQuery;
        insertCompanyChangesQuery.prepare("INSERT INTO firmen_aenderungen(firmen_id, von, bis, rang, leistungstyp) VALUES (:companyID, '', '', '', '')");
        insertCompanyChangesQuery.bindValue(":companyID", ui->cb_company->currentData().toInt());
        insertCompanyChangesQuery.exec();
        int id = insertCompanyChangesQuery.lastInsertId().toInt();

        QListWidgetItem* item = new QListWidgetItem(" - , , ");
        item->setData(Qt::UserRole, id);
        ui->lw_changes->addItem(item);
        ui->lw_changes->setCurrentItem(item);
    } else {
        QListWidgetItem* item = new QListWidgetItem(" - , , ");
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

void Company::on_tb_remove_clicked() {
    if (editMode) {
        QSqlQuery removeCompanyChanges;
        removeCompanyChanges.prepare("DELETE FROM firmen_aenderungen WHERE id = :id");
        removeCompanyChanges.bindValue(":id", selected->data(Qt::UserRole).toInt());
        removeCompanyChanges.exec();

        QListWidgetItem *temp = selected;
        selected = NULL;
        ui->lw_changes->takeItem(ui->lw_changes->row(temp));
    } else {
        QListWidgetItem *temp = selected;
        selected = NULL;
        ui->lw_changes->takeItem(ui->lw_changes->row(temp));
    }
}

void Company::on_pb_okay_clicked() {
    QSqlQuery insertCompanyQuery;
    if (editMode) {
        insertCompanyQuery.prepare("UPDATE firmen SET name = :name, infos = :info, anschrift = :address WHERE id = :companyID");
        insertCompanyQuery.bindValue(":companyID", ui->cb_company->currentData().toInt());

        if (selected != NULL) {
            QSqlQuery submitCompanyChanges;
            submitCompanyChanges.prepare("UPDATE firmen_aenderungen SET von = :since, bis = :until, rang = :rank, leistungstyp = :type WHERE id = :id");
            submitCompanyChanges.bindValue(":id", selected->data(Qt::UserRole).toInt());
            submitCompanyChanges.bindValue(":since", ui->le_since->text());
            submitCompanyChanges.bindValue(":until", ui->le_until->text());
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
            submitCompanyChanges.bindValue(":rank", rank);
            submitCompanyChanges.bindValue(":type", ui->le_typ->text());
            submitCompanyChanges.exec();
        }
    } else {
        insertCompanyQuery.prepare("INSERT INTO firmen(name, infos, anschrift) VALUES (:name, :info, :address)");
    }
    insertCompanyQuery.bindValue(":name", ui->le_name->text());
    insertCompanyQuery.bindValue(":info", ui->le_info->text());
    insertCompanyQuery.bindValue(":address", ui->le_address->text());
    insertCompanyQuery.exec();

    if (!editMode) {
        int id = insertCompanyQuery.lastInsertId().toInt();

        foreach (QListWidgetItem* listItem, ui->lw_changes->findItems("*", Qt::MatchWildcard)) {
            QList<QVariant> list = listItem->data(Qt::UserRole).toList();

            QSqlQuery insertCompanyChangesQuery;
            insertCompanyChangesQuery.prepare("INSERT INTO firmen_aenderungen(firmen_id, von, bis, rang, leistungstyp) VALUES (:companyID, :since, :until, :rank, :type)");
            insertCompanyChangesQuery.bindValue(":companyID", id);
            insertCompanyChangesQuery.bindValue(":since", list.at(0).toString());
            insertCompanyChangesQuery.bindValue(":until", list.at(1).toString());
            insertCompanyChangesQuery.bindValue(":rank", list.at(2).toString());
            insertCompanyChangesQuery.bindValue(":type", list.at(3).toString());
            insertCompanyChangesQuery.exec();
        }
    }

    if (insertCompanyQuery.next()) {
        Error errorWindow;
        errorWindow.setText("QSQLITE error: " + insertCompanyQuery.lastError().text() + ",\nQSQLITE error code: " + insertCompanyQuery.lastError().nativeErrorCode());
        errorWindow.setModal(true);
        errorWindow.exec();
    } else {
        this->accept();
    }
}

void Company::selectionChanged() {
    // update previous data
    if (selected != NULL) {
        if (editMode) {
            QSqlQuery submitCompanyChanges;
            submitCompanyChanges.prepare("UPDATE firmen_aenderungen SET von = :since, bis = :until, rang = :rank, leistungstyp = :type WHERE id = :id");

            submitCompanyChanges.bindValue(":id", selected->data(Qt::UserRole).toInt());
            submitCompanyChanges.bindValue(":since", ui->le_since->text());
            submitCompanyChanges.bindValue(":until", ui->le_until->text());
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
            submitCompanyChanges.bindValue(":rank", rank);
            submitCompanyChanges.bindValue(":type", ui->le_typ->text());
            submitCompanyChanges.exec();

            QSqlQuery selectCompanyChanges;
            selectCompanyChanges.prepare("SELECT id, firmen_id, von, bis, rang, leistungstyp FROM firmen_aenderungen WHERE id = :id");
            selectCompanyChanges.bindValue(":id", selected->data(Qt::UserRole).toInt());
            selectCompanyChanges.exec();
            selectCompanyChanges.next();

            selected->setText(selectCompanyChanges.value(2).toString() + " - " + selectCompanyChanges.value(3).toString() + ", " + selectCompanyChanges.value(4).toString() + ", " + selectCompanyChanges.value(5).toString());
        } else {
            QList<QVariant> list;
            list.append(ui->le_since->text());
            list.append(ui->le_until->text());
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
            list.append(rank);
            list.append(ui->le_typ->text());
            selected->setData(Qt::UserRole, list);
            selected->setText(ui->le_since->text() + " - " + ui->le_until->text() + ", " + rank + ", " + ui->le_typ->text());
        }
    }

    // set new data
    ui->buttonGroup->setExclusive(false);
    ui->rb_gold->setChecked(false);
    ui->rb_silver->setChecked(false);
    ui->rb_bronze->setChecked(false);
    ui->rb_supporter->setChecked(false);
    ui->buttonGroup->setExclusive(true);

    if (ui->lw_changes->currentItem() != NULL) {
        if (editMode) {
            QSqlQuery selectCompanyChanges;
            selectCompanyChanges.prepare("SELECT id, firmen_id, von, bis, rang, leistungstyp FROM firmen_aenderungen WHERE id = :id");

            selectCompanyChanges.bindValue(":id", ui->lw_changes->currentItem()->data(Qt::UserRole).toInt());
            selectCompanyChanges.exec();
            selectCompanyChanges.next();

            ui->tb_remove->setDisabled(false);
            ui->le_since->setDisabled(false);
            ui->le_until->setDisabled(false);
            ui->rb_gold->setDisabled(false);
            ui->rb_silver->setDisabled(false);
            ui->rb_bronze->setDisabled(false);
            ui->rb_supporter->setDisabled(false);
            ui->le_typ->setDisabled(false);

            ui->le_since->setText(selectCompanyChanges.value(2).toString());
            ui->le_until->setText(selectCompanyChanges.value(3).toString());
            QString rank = selectCompanyChanges.value(4).toString();
            if (rank == "Gold") {
                ui->rb_gold->setChecked(true);
            } else if (rank == "Silber") {
                ui->rb_silver->setChecked(true);
            } else if (rank == "Bronze") {
                ui->rb_bronze->setChecked(true);
            } else if (rank == "Supporter") {
                ui->rb_supporter->setChecked(true);
            }
            ui->le_typ->setText(selectCompanyChanges.value(5).toString());
        } else {
            QList<QVariant> list = ui->lw_changes->currentItem()->data(Qt::UserRole).toList();
            ui->tb_remove->setDisabled(false);
            ui->le_since->setDisabled(false);
            ui->le_until->setDisabled(false);
            ui->rb_gold->setDisabled(false);
            ui->rb_silver->setDisabled(false);
            ui->rb_bronze->setDisabled(false);
            ui->rb_supporter->setDisabled(false);
            ui->le_typ->setDisabled(false);

            ui->le_since->setText(list.at(0).toString());
            ui->le_until->setText(list.at(1).toString());
            QString rank = list.at(2).toString();
            if (rank == "Gold") {
                ui->rb_gold->setChecked(true);
            } else if (rank == "Silber") {
                ui->rb_silver->setChecked(true);
            } else if (rank == "Bronze") {
                ui->rb_bronze->setChecked(true);
            } else if (rank == "Supporter") {
                ui->rb_supporter->setChecked(true);
            }
            ui->le_typ->setText(list.at(3).toString());
        }
    } else {
        ui->tb_remove->setDisabled(true);
        ui->le_since->setDisabled(true);
        ui->le_until->setDisabled(true);
        ui->rb_gold->setDisabled(true);
        ui->rb_silver->setDisabled(true);
        ui->rb_bronze->setDisabled(true);
        ui->rb_supporter->setDisabled(true);
        ui->le_typ->setDisabled(true);

        ui->le_since->setText("");
        ui->le_until->setText("");
        ui->le_typ->setText("");
    }

    selected = ui->lw_changes->currentItem();
}
