#include "communication.h"
#include "ui_communication.h"
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include "error.h"
#include <QMessageBox>

Communication::Communication(QWidget *parent, bool editMode) :
    QDialog(parent),
    ui(new Ui::Communication)
{
    ui->setupUi(this);

    Communication::editMode = editMode;

    if (editMode) {
        QWidget::setWindowTitle("GLR Datenbank - Kommunikation bearbeiten");
        ui->l_dialogTitle->setText("GLR Datenbank - Kommunikation bearbeiten");

        QSqlQuery selectCommunication;
        selectCommunication.prepare("SELECT kommunikationen.id, firmen.name, personen.vorname, personen.nachname, wann FROM kommunikationen JOIN firmen ON kommunikationen.firmen_id = firmen.id JOIN personen ON kommunikationen.personen_id = personen.id");
        selectCommunication.exec();

        while(selectCommunication.next()) {
            ui->cb_communication->addItem(selectCommunication.value(0).toString() + " - " +
                                          selectCommunication.value(1).toString() + " - " +
                                          selectCommunication.value(2).toString() + " " + selectCommunication.value(3).toString() + " - " +
                                          selectCommunication.value(4).toString(),
                                          selectCommunication.value(0).toInt());
        }

        if (ui->cb_communication->count() < 1) {
            ui->cb_communication->setDisabled(true);
        }

        ui->tb_add->setDisabled(true);
        ui->cb_company->setDisabled(true);
        ui->cb_person->setDisabled(true);
        ui->cw_calender->setDisabled(true);
        ui->le_when->setDisabled(true);
        ui->le_what->setDisabled(true);
        ui->pb_okay->setDisabled(true);

    } else {
        QWidget::setWindowTitle("GLR Datenbank - Kommunikation hinzufügen");
        ui->l_dialogTitle->setText("GLR Datenbank - Kommunikation hinzufügen");
        ui->cb_communication->setVisible(false);
        ui->label_5->setVisible(false);
        ui->cb_person->setDisabled(true);

        QObject::connect(ui->lw_files, SIGNAL(itemSelectionChanged()), this, SLOT(selectionChanged()));

        set_cb_company();
    }

    // Do not display week numbers
    ui->cw_calender->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

    // print initially selected date (today)
    ui->le_when->setText(ui->cw_calender->selectedDate().toString("yyyy-MM-dd"));

    ui->tb_remove->setDisabled(true);
    ui->tb_download->setDisabled(true);
    ui->lw_files->setDisabled(true);

    ui->lw_files->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

Communication::~Communication()
{
    delete ui;
}

void Communication::on_cb_communication_currentIndexChanged() {
    QSqlQuery selectCommunication;
    selectCommunication.prepare("SELECT kommunikationen.id, firmen.id, personen.id, wann, was FROM kommunikationen JOIN firmen ON kommunikationen.firmen_id = firmen.id JOIN personen ON kommunikationen.personen_id = personen.id WHERE kommunikationen.id = :communicationID");
    selectCommunication.bindValue(":communicationID", ui->cb_communication->currentData().toInt());
    selectCommunication.exec();
    selectCommunication.next();

    ui->cb_company->setDisabled(false);
    ui->cb_person->setDisabled(false);
    ui->cw_calender->setDisabled(false);
    ui->le_when->setDisabled(false);
    ui->le_what->setDisabled(false);
    ui->pb_okay->setDisabled(false);
    ui->tb_add->setDisabled(false);

    ui->tb_remove->setDisabled(true);
    ui->tb_download->setDisabled(true);

    QSqlQuery selectCommunicationFiles;
    selectCommunicationFiles.prepare("SELECT id, kommunikationen_id, dateiname, datei FROM kommunikationen_dateien WHERE kommunikationen_id = :communicationID");
    selectCommunicationFiles.bindValue(":communicationID", ui->cb_communication->currentData().toInt());
    selectCommunicationFiles.exec();

    ui->lw_files->clear();
    ui->tb_remove->setDisabled(true);
    while(selectCommunicationFiles.next()) {
        QListWidgetItem *item = new QListWidgetItem(selectCommunicationFiles.value(2).toString());
        int file_id = selectCommunicationFiles.value(0).toInt();
        QString file_content = NULL;

        QList<QVariant> list;
        list.append(QVariant(file_id));
        list.append(QVariant(file_content));

        item->setData(Qt::UserRole, list);
        ui->lw_files->addItem(item);
    }

    if (ui->lw_files->count() > 0) {
        ui->lw_files->setDisabled(false);
    } else {
        ui->lw_files->setDisabled(true);
    }

    QObject::connect(ui->lw_files, SIGNAL(itemSelectionChanged()), this, SLOT(selectionChanged()));

    set_cb_company(selectCommunication.value(1).toInt());
    set_cb_person(selectCommunication.value(2).toInt());
    ui->le_when->setText(selectCommunication.value(3).toString());
    ui->cw_calender->setSelectedDate(selectCommunication.value(3).toDate());
    ui->le_what->setText(selectCommunication.value(4).toString());
}

void Communication::on_cb_company_currentIndexChanged()
{
    set_cb_person();
}

void Communication::on_cw_calender_selectionChanged()
{
    ui->le_when->setText(ui->cw_calender->selectedDate().toString("yyyy-MM-dd"));
}

void Communication::on_pb_okay_clicked()
{
    int communicationID = ui->cb_communication->currentData().toInt();
    int companyID = ui->cb_company->currentData().toInt();
    int personID = ui->cb_person->currentData().toInt();
    QString when = ui->le_when->text();
    QString what = ui->le_what->text();

    QSqlQuery insertCommunicationQuery;
    if (editMode) {
        insertCommunicationQuery.prepare("UPDATE kommunikationen SET firmen_id = :companyID, personen_id = :personID, wann = :when, was = :what WHERE id = :communicationID");
        insertCommunicationQuery.bindValue(":communicationID", communicationID);
    } else {
        insertCommunicationQuery.prepare("INSERT INTO kommunikationen(firmen_id, personen_id, wann, was) VALUES (:companyID, :personID, :when, :what)");
    }

    insertCommunicationQuery.bindValue(":companyID", companyID);
    insertCommunicationQuery.bindValue(":personID", personID);
    insertCommunicationQuery.bindValue(":when", when);
    insertCommunicationQuery.bindValue(":what", what);
    insertCommunicationQuery.exec();

    if (!editMode) {
        communicationID = insertCommunicationQuery.lastInsertId().toInt();
        for (auto item : ui->lw_files->findItems("*", Qt::MatchWildcard)) {
            QList<QVariant> list = item->data(Qt::UserRole).toList();
            QString fileName = item->text();

            QSqlQuery insertCommunicationFileQuery;
            insertCommunicationFileQuery.prepare("INSERT INTO kommunikationen_dateien(kommunikationen_id, dateiname, datei) VALUES (:communicationId, :fileName, :fileContent)");
            insertCommunicationFileQuery.bindValue(":communicationId", communicationID);
            insertCommunicationFileQuery.bindValue(":fileName", fileName);
            insertCommunicationFileQuery.bindValue(":fileContent", list.at(1).toString());
            insertCommunicationFileQuery.exec();
        }
    }

    if (insertCommunicationQuery.next()) {
        Error errorWindow;
        errorWindow.setText("QSQLITE error: " + insertCommunicationQuery.lastError().text() + ",\nQSQLITE error code: " + insertCommunicationQuery.lastError().nativeErrorCode());
        errorWindow.setModal(true);
        errorWindow.exec();
    } else {
        this->accept();
    }
}

void Communication::on_tb_add_clicked() {
    static QString fileName;
    static QFile file;
    fileName = QFileDialog::getOpenFileName(this, "Datei öffnen");
    file.setFileName(fileName);
    file.open(QIODevice::ReadOnly);

    int communicationID = ui->cb_communication->currentData().toInt();

    QString date = ui->le_when->text();

    QByteArray fileContent = file.readAll();

    QFileInfo fileInfo(fileName);
    QString fileNameWithoutPath = date + "-" + fileInfo.fileName();

    QSqlQuery insertCommunicationFileQuery;
    if (editMode) {
        insertCommunicationFileQuery.prepare("INSERT INTO kommunikationen_dateien(kommunikationen_id, dateiname, datei) VALUES (:communicationID, :fileName, :fileContent)");
        insertCommunicationFileQuery.bindValue(":communicationID", communicationID);
        insertCommunicationFileQuery.bindValue(":fileName", fileNameWithoutPath);
        insertCommunicationFileQuery.bindValue(":fileContent", fileContent);
        insertCommunicationFileQuery.exec();
    }

    QListWidgetItem *item = new QListWidgetItem(fileNameWithoutPath);

    int file_id = 0;
    if (editMode) {
        file_id = insertCommunicationFileQuery.lastInsertId().toInt();
    }
    QByteArray file_content = NULL;
    if (!editMode) {
        file_content = fileContent;
    }

    QList<QVariant> list;
    list.append(QVariant(file_id));
    list.append(QVariant(file_content));

    item->setData(Qt::UserRole, list);
    ui->lw_files->addItem(item);
    ui->lw_files->setDisabled(false);

    file.close();
}

void Communication::on_tb_remove_clicked() {
    QList<QVariant> list = ui->lw_files->currentItem()->data(Qt::UserRole).toList();

    QMessageBox::StandardButton box = QMessageBox::Yes;
    box = QMessageBox::warning(this, "Löschen bestätigen",
                               tr("Möchtest du diese Datei wirklich löschen?"),
                               QMessageBox::No | QMessageBox::Yes,
                               QMessageBox::No);

    if (box == QMessageBox::Yes) {
        if (editMode) {
            QSqlQuery removeFile;
            removeFile.prepare("DELETE FROM kommunikationen_dateien WHERE id = :id;");
            removeFile.bindValue(":id", list.at(0).toInt());
            removeFile.exec();
        }

        ui->lw_files->takeItem(ui->lw_files->row(ui->lw_files->currentItem()));
        ui->lw_files->clearSelection();
        ui->tb_remove->setDisabled(true);
        if (ui->lw_files->count() == 0) {
            ui->lw_files->setDisabled(true);
        }
        ui->tb_download->setDisabled(true);
    }
}

void Communication::on_tb_download_clicked() {
    QString fileName;
    QByteArray fileContent;
    QString filePath;
    QFile file;
    QSqlQuery selectFileQuery;

    QList<QListWidgetItem *> items = ui->lw_files->selectedItems();

    if (items.length() > 1) {
        filePath = QFileDialog::getExistingDirectory(this, tr("Ordner benutzen"));
        if (filePath == "")
            return;
    }

    for (int i = 0; i < items.length(); i++) {
        if (editMode) {
            qDebug() << items[i]->data(Qt::UserRole).toList()[0];
            selectFileQuery.prepare("SELECT id, kommunikationen_id, dateiname, datei FROM kommunikationen_dateien WHERE id = :id");
            selectFileQuery.bindValue(":id", items[i]->data(Qt::UserRole).toList()[0].toInt());
            selectFileQuery.exec();
            selectFileQuery.next();
            fileName = selectFileQuery.value(2).toString();
            fileContent = selectFileQuery.value(3).toByteArray();
        } else {
            fileName = items[i]->text();
            fileContent = items[i]->data(Qt::UserRole).toList()[1].toByteArray();
        }

        if (items.length() > 1) {
            file.setFileName(filePath + "/" + fileName);
        } else {
            fileName = QFileDialog::getSaveFileName(this, tr("Kommunikation speichern"), fileName);
            if (fileName == "")
                return;
            file.setFileName(fileName);
        }

        file.open(QIODevice::ReadWrite | QIODevice::Truncate);
        file.write(fileContent);
        file.close();
    }
}

void Communication::selectionChanged() {
    if (ui->lw_files->currentItem() != NULL) {
        ui->tb_remove->setDisabled(false);
        ui->tb_download->setDisabled(false);
    } else {
        ui->tb_remove->setDisabled(true);
        ui->tb_download->setDisabled(true);
    }
}

void Communication::set_cb_company(int id) {
    ui->cb_company->clear();

    QSqlQuery selectName;
    selectName.prepare("SELECT id, name FROM firmen");
    selectName.exec();
    while(selectName.next()) {
        ui->cb_company->addItem(selectName.value(1).toString(), selectName.value(0));
        if (id == selectName.value(0)) {
            ui->cb_company->setCurrentIndex(ui->cb_company->count() - 1);
        }
    }

    if (ui->cb_company->count() > 0) {
        ui->cb_company->setEnabled(true);
    } else {
        ui->cb_company->setDisabled(true);
    }
}

void Communication::set_cb_person(int id) {
    ui->cb_person->clear();

    QSqlQuery selectName;
    selectName.prepare("SELECT id, vorname, nachname FROM personen WHERE firmen_id = :companyID");
    selectName.bindValue(":companyID", ui->cb_company->currentData().toInt());
    selectName.exec();
    while(selectName.next()) {
        ui->cb_person->addItem(selectName.value(1).toString() + " " + selectName.value(2).toString(), selectName.value(0));
        if (id == selectName.value(0))
            ui->cb_person->setCurrentIndex(ui->cb_person->count() - 1);
    }

    if (ui->cb_person->count() > 0) {
        ui->cb_person->setEnabled(true);
    } else {
        ui->cb_person->setDisabled(true);
    }
}
