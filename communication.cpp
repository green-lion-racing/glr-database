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
    QSqlQuery  CommunicationQuery("CREATE TABLE IF NOT EXISTS kommunikationen (id INTEGER PRIMARY KEY, firma TEXT, ansprechpartner TEXT, wann TEXT, was TEXT, FirmenID INTEGER, PersonenID INTEGER, FOREIGN KEY (FirmenID) REFERENCES firmen(id), FOREIGN KEY(PersonenID) REFERENCES personen(id))");
    QSqlQuery  CommunicationFileQuery("CREATE TABLE IF NOT EXISTS kommunikation_dateien (id INTEGER PRIMARY KEY, kommunikation_id INTEGER, datei BLOB, dateiname TEXT, FOREIGN KEY (kommunikation_id) REFERENCES kommunikationen(id))");

    ui->setupUi(this);

    Communication::editMode = editMode;

    QVector<QString> communicationNames;

    ui->tb_remove->setDisabled(true);

    if (editMode) {
        QWidget::setWindowTitle("GLR Datenbank - Kommunikation bearbeiten");
        ui->l_dialogTitle->setText("GLR Datenbank - Kommunikation bearbeiten");

        QSqlQuery selectCommunication;
        selectCommunication.prepare("SELECT id, firma, ansprechpartner, wann FROM kommunikationen");
        selectCommunication.exec();

        while(selectCommunication.next()) {
            communicationNames.push_back(selectCommunication.value(0).toString() + " - " +
                                    selectCommunication.value(1).toString() + " - " +
                                    selectCommunication.value(2).toString() + " - " +
                                    selectCommunication.value(3).toString());
        }

        for (int i = 0; i < communicationNames.size(); i++) {
            ui->cb_communication->addItem(communicationNames[i]);
        }

        if (communicationNames.size() < 1) {
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

        QObject::connect(ui->lw_files, SIGNAL(itemSelectionChanged()), this, SLOT(selectionChanged()));

        set_cb_company();
    }

    // Do not display week numbers
    ui->cw_calender->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

    // print initially selected date (today)
    ui->le_when->setText(ui->cw_calender->selectedDate().toString("yyyy-MM-dd"));
}

Communication::~Communication()
{
    delete ui;
}

void Communication::on_cb_communication_currentTextChanged()
{
    QSqlQuery selectCommunication;

    static QRegularExpression regex(" - ");
    int communicationID = ui->cb_communication->currentText().split(regex)[0].toInt();

    selectCommunication.prepare("SELECT * FROM kommunikationen WHERE id = :communicationID");
    selectCommunication.bindValue(":communicationID", communicationID);
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

    QSqlQuery selectCommunicationFiles;
    selectCommunicationFiles.prepare("SELECT id, kommunikation_id, dateiname, datei FROM kommunikation_dateien WHERE kommunikation_id = :communicationID");
    selectCommunicationFiles.bindValue(":communicationID", communicationID);
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

    QObject::connect(ui->lw_files, SIGNAL(itemSelectionChanged()), this, SLOT(selectionChanged()));

    set_cb_company(selectCommunication.value(1).toString());
    set_cb_person(selectCommunication.value(2).toString());
    ui->le_when->setText(selectCommunication.value(3).toString());
    ui->cw_calender->setSelectedDate(selectCommunication.value(3).toDate());
    ui->le_what->setText(selectCommunication.value(4).toString());
}

void Communication::on_cb_company_currentTextChanged()
{
    set_cb_person();
}

void Communication::on_cw_calender_selectionChanged()
{
    ui->le_when->setText(ui->cw_calender->selectedDate().toString("yyyy-MM-dd"));
}

void Communication::on_pb_okay_clicked()
{
    int communicationID = ui->cb_communication->currentIndex();
    int personID = ui->cb_person->currentIndex();
    int companyID = ui->cb_company->currentIndex();
    QString company = ui->cb_company->currentText();
    QString person = ui->cb_person->currentText();
    QString when = ui->le_when->text();
    QString what = ui->le_what->text();

    QSqlQuery insertCommunicationQuery;
    if (editMode) {
        insertCommunicationQuery.prepare("UPDATE kommunikationen SET firma = :company, ansprechpartner = :person, wann = :when, was = :what, FirmenID = :companyID, PersonenID = :personID WHERE id = :communicationID");
        insertCommunicationQuery.bindValue(":communicationID", communicationID + 1);
    } else {
        insertCommunicationQuery.prepare("INSERT INTO kommunikationen(firma, ansprechpartner, wann, was, FirmenID, PersonenID) VALUES (:company, :person, :when, :what, :companyID, :personID)");
    }

    insertCommunicationQuery.bindValue(":person", person);
    insertCommunicationQuery.bindValue(":company", company);
    insertCommunicationQuery.bindValue(":when", when);
    insertCommunicationQuery.bindValue(":what", what);
    insertCommunicationQuery.bindValue(":companyID", companyID);
    insertCommunicationQuery.bindValue(":personID", personID);
    insertCommunicationQuery.exec();

    if (!editMode) {
        communicationID = insertCommunicationQuery.lastInsertId().toInt();
        for (auto item : ui->lw_files->findItems("*", Qt::MatchWildcard)) {
            QList<QVariant> list = item->data(Qt::UserRole).toList();
            QString fileName = item->text();

            QSqlQuery insertCommunicationFileQuery;
            insertCommunicationFileQuery.prepare("INSERT INTO kommunikation_dateien(kommunikation_id, datei, dateiname) VALUES (:communicationId, :fileContent, :fileName)");
            insertCommunicationFileQuery.bindValue(":communicationId", communicationID);
            insertCommunicationFileQuery.bindValue(":fileContent", list.at(1).toString());
            insertCommunicationFileQuery.bindValue(":fileName", fileName);
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


    int communicationId = ui->cb_communication->currentIndex();

    QString date = ui->le_when->text();

    QByteArray fileContent = file.readAll();

    QFileInfo onlyFileName(fileName);
    QString fileNameWithoutPath = onlyFileName.fileName();  // filename without path
    fileNameWithoutPath = date + "-" + fileNameWithoutPath;

    if (editMode) {
        QSqlQuery insertCommunicationFileQuery;
        insertCommunicationFileQuery.prepare("INSERT INTO kommunikation_dateien(kommunikation_id, datei, dateiname) VALUES (:communicationId, :fileContent, :fileNameWithoutPath)");
        insertCommunicationFileQuery.bindValue(":communicationId", communicationId + 1);
        insertCommunicationFileQuery.bindValue(":fileContent", fileContent);
        insertCommunicationFileQuery.bindValue(":fileNameWithoutPath", fileNameWithoutPath);
        insertCommunicationFileQuery.exec();
    }

    QListWidgetItem *item = new QListWidgetItem(fileNameWithoutPath);

    int file_id = communicationId + 1;
    if (!editMode) {
        file_id = 0;
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
            removeFile.prepare("DELETE FROM kommunikation_dateien WHERE id = :id;");
            removeFile.bindValue(":id", list.at(0).toInt());
            removeFile.exec();
        }

        ui->lw_files->takeItem(ui->lw_files->row(ui->lw_files->currentItem()));
        ui->lw_files->clearSelection();
        ui->tb_remove->setDisabled(true);
    }
}

void Communication::selectionChanged() {
    if (ui->lw_files->currentItem() != NULL) {
        ui->tb_remove->setDisabled(false);
    } else {
        ui->tb_remove->setDisabled(true);
    }
}

QString Communication::getCompanyId () {
    QSqlQuery queryCompanyId;
    QString companyName = ui->cb_company->currentText();
    queryCompanyId.prepare("SELECT id FROM firmen WHERE name = :companyName");
    queryCompanyId.bindValue(":companyName", companyName);
    queryCompanyId.exec();

    QString companyId;
    while (queryCompanyId.next())
        companyId = queryCompanyId.value(0).toString();

    return companyId;
}

void Communication::set_cb_company(QString company) {
    QSqlQuery selectName;
    QVector<QString> companyNames;

    ui->cb_company->clear();

    selectName.prepare("SELECT id, name FROM firmen");
    selectName.exec();
    while(selectName.next()) {
        companyNames.push_back(selectName.value(1).toString());
    }

    for (int i = 0; i < companyNames.size(); i++) {
        ui->cb_company->addItem(companyNames[i]);
        if (!QString::compare(company, companyNames[i], Qt::CaseInsensitive)) {
            ui->cb_company->setCurrentIndex(i);
        }
    }

    if (companyNames.size() > 0) {
        ui->cb_company->setEnabled(true);
    } else {
        ui->cb_company->setDisabled(true);
    }
}

void Communication::set_cb_person(QString person) {
    QSqlQuery selectName;
    QVector<QString> personNames;

    ui->cb_person->clear();

    selectName.prepare("SELECT id, vorname, nachname FROM personen WHERE FirmenID = :companyID");
    selectName.bindValue(":companyID", getCompanyId());
    selectName.exec();
    while(selectName.next()) {
        personNames.push_back(selectName.value(1).toString() + " " + selectName.value(2).toString());
    }
    for (int i = 0; i < personNames.size(); i++) {
        ui->cb_person->addItem(personNames[i]);
        if (!QString::compare(person, personNames[i], Qt::CaseInsensitive))
            ui->cb_person->setCurrentIndex(i);
    }

    if (personNames.size() > 0) {
        ui->cb_person->setEnabled(true);
    } else {
        ui->cb_person->setDisabled(true);
    }
}
