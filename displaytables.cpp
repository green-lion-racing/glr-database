#include "displaytables.h"
#include "ui_displaytables.h"
#include <QFileDialog>

displayTables::displayTables(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::displayTables)
{
    ui->setupUi(this);

    QWidget::setWindowTitle("GLR Datenbank - Einträge ansehen");

    QSqlQuery selectTable;
    selectTable.prepare("SELECT name FROM (SELECT * FROM sqlite_master UNION ALL SELECT * FROM sqlite_temp_master)WHERE type='table' ORDER BY name");
    selectTable.exec();

    QSqlQueryModel * modalComboBox = new QSqlQueryModel();
    modalComboBox->setQuery(selectTable);

    ui->cb_table->setModel(modalComboBox);

    ui->tv_table->verticalHeader()->setVisible(false);
    ui->tv_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

displayTables::~displayTables()
{
    delete ui;
}

QString displayTables::getCompanyId () {
    QSqlQuery queryCompanyId;
    QString companyName = ui->cb_filter->currentText();
    queryCompanyId.prepare("SELECT id FROM firmen WHERE name = :companyName");
    queryCompanyId.bindValue(":companyName", companyName);
    queryCompanyId.exec();

    QString companyId;
    queryCompanyId.next();
    companyId = queryCompanyId.value(0).toString();

    return companyId;
}

void displayTables::on_cb_table_currentTextChanged()
{
    ui->cb_filter->setVisible(false);
    ui->pb_download->setVisible(false);
    ui->pb_download_all->setVisible(false);
    ui->pb_save->setVisible(false);

    // Checkboxes
    ui->cb_filter_gold->setVisible(false);
    ui->cb_filter_silver->setVisible(false);
    ui->cb_filter_bronze->setVisible(false);
    ui->cb_filter_supporter->setVisible(false);

    selectedTable = ui->cb_table->currentText();
    modal = new QSqlTableModel();
    modal->setQuery("SELECT * FROM " + selectedTable);

    if (selectedTable == "kommunikation_dateien") {
        download_mode = 0;
        ui->pb_download->setText("Ausgewählte Kommunikationen speichern");
        ui->pb_download->setVisible(true);
        ui->pb_download_all->setText("Alle Kommunikationen speichern");
        ui->pb_download_all->setVisible(true);
    } else if (selectedTable == "firmen") {
        //ui->cb_rank->setVisible(true);
        //rank = ui->cb_rank->currentText();
        //filter = "firma = '" + rank + "'";

        //modal->setFilter(filter);
        modal->setQuery("SELECT * FROM " + selectedTable);
        ui->cb_filter_gold->setVisible(true);
        ui->cb_filter_silver->setVisible(true);
        ui->cb_filter_bronze->setVisible(true);
        ui->cb_filter_supporter->setVisible(true);
    } else if (selectedTable == "personen" || selectedTable=="kommunikationen") {
        //Alle Firmennamen
        QString companyName;
        QSqlQuery selectName;
        selectName.prepare("SELECT name FROM firmen");
        selectName.exec();
        QSqlQueryModel * modalComboBox = new QSqlQueryModel();
        modalComboBox->setQuery(selectName);
        ui->cb_filter->setModel(modalComboBox);

        ui->cb_filter->setVisible(true);
        companyName = ui->cb_filter->currentText();

        QString companyId = getCompanyId();
        if (selectedTable == "kommunikationen") {
            ui->pb_save->setVisible(true);

            modal->setQuery("SELECT k.id, k.firma, k.ansprechpartner, k.wann, k.was, count(*) FROM kommunikationen k, kommunikation_dateien d  WHERE k.FirmenID = '" + companyId + "' AND k.id = d.kommunikation_id GROUP BY kommunikation_id");
        } else if (selectedTable == "personen") {
            // display filter company name
            //ui->cb_companyName->setVisible(true);
            //companyName = ui->cb_companyName->currentText();
            //filter = "firma = '" + companyName + "'";
            modal->setQuery("SELECT * FROM " + selectedTable + " WHERE FirmenId = '" + companyId + "'");
        }
    } else if (selectedTable == "mitglieder") {
        download_mode = 1;
        ui->pb_download->setText("Ausgewählte Signaturen speichern");
        ui->pb_download->setVisible(true);
        ui->pb_download_all->setText("Alle Signaturen speichern");
        ui->pb_download_all->setVisible(true);
    }

    //modal->select();
    ui->tv_table->setSortingEnabled(true);
    //modal->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tv_table->setModel(modal);
}

void displayTables::on_cb_filter_currentTextChanged()
{
    ui->cb_filter->setVisible(true);
    QString companyName = ui->cb_filter->currentText();
    QString companyId = getCompanyId();
    if (selectedTable == "kommunikationen")
        modal->setQuery("SELECT k.id, k.firma, k.ansprechpartner, k.wann, k.was, count(*) FROM kommunikationen k, kommunikation_dateien d  WHERE k.FirmenID = '" + companyId + "' AND k.id = d.kommunikation_id GROUP BY kommunikation_id");
    else
        modal->setQuery("SELECT * FROM " + selectedTable + " WHERE firma = '" + companyName  + "'");
    /*QString filter = "firma = '" + companyName + "'";
    //modal->select();
    ui->tv_table->setModel(modal);
    //modal->setFilter(filter);
    //modal->setFilter(filter);
    //modal->select();
    ui->tv_table->setModel(modal);
    */
}

void displayTables::on_cb_filter_gold_stateChanged() {
    update_cb_filter();
}

void displayTables::on_cb_filter_silver_stateChanged() {
    update_cb_filter();
}

void displayTables::on_cb_filter_bronze_stateChanged() {
    update_cb_filter();
}

void displayTables::on_cb_filter_supporter_stateChanged() {
    update_cb_filter();
}

void displayTables::update_cb_filter() {
    QVector<QString> checks;
    QString filter = "";

    if (ui->cb_filter_gold->isChecked()) {
        checks.push_back("rang = 'Gold'");
    }

    if (ui->cb_filter_silver->isChecked()) {
        checks.push_back("rang = 'Silber'");
    }

    if (ui->cb_filter_bronze->isChecked()) {
        checks.push_back("rang = 'Bronze'");
    }

    if (ui->cb_filter_supporter->isChecked()) {
        checks.push_back("rang = 'Supporter'");
    }

    for (int i = 0; i < checks.length() - 1; i++) {
        filter += checks[i] + " OR ";
    }
    if (!checks.isEmpty())
        filter += checks.constLast();

    modal->setTable("firmen");
    modal->setFilter(filter);
    modal->select();
    ui->tv_table->setModel(modal);
}

void displayTables::on_tv_table_clicked(const QModelIndex &index)
{
    int row = index.row();
    QSqlRecord record = modal->record(row);
    id = record.value(0).toInt();
}

void displayTables::on_pb_download_clicked() {
    QString fileName;
    QString fileContent;
    QFile file;
    QSqlQuery selectFileQuery;

    if (download_mode == 0) {

        selectFileQuery.prepare("SELECT datei, dateiname FROM kommunikation_dateien WHERE id = :id");
        selectFileQuery.bindValue(":id", id);
        selectFileQuery.exec();
        selectFileQuery.next();

        fileName = QFileDialog::getSaveFileName(this, tr("Kommunikation speichern"), selectFileQuery.value(1).toString());
        if (fileName == "")
            return;

        fileContent = selectFileQuery.value(0).toByteArray();
        fileName = selectFileQuery.value(1).toString();

        file.setFileName(fileName);
        file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
        file.write(fileContent.toUtf8());
    } else if (download_mode == 1) {

        selectFileQuery.prepare("SELECT vorname, nachname, position, telefon, email_glr FROM mitglieder WHERE id = :id");
        selectFileQuery.bindValue(":id", id);
        selectFileQuery.exec();
        selectFileQuery.next();

        QString filter = "HTML Files (*.html)";
        fileName = QFileDialog::getSaveFileName(this, tr("Signatur speichern"), "Signatur " + selectFileQuery.value(0).toByteArray() + " " + selectFileQuery.value(1).toByteArray() + ".html", filter, &filter);
        if (fileName == "")
            return;

        QString phone = "";
        if (!selectFileQuery.value(3).toString().isEmpty()) {
            phone = "<a href='tel:" + selectFileQuery.value(3).toString() + "'>" + selectFileQuery.value(3).toString() + "</a><br>";
        }

        QString mail = "";
        if (!selectFileQuery.value(4).toString().isEmpty()) {
            mail = "<a href='mailto:" + selectFileQuery.value(4).toString() + "'>" + selectFileQuery.value(4).toString() + "</a><br>";
        }

        fileContent = "Mit freundlichen Grüßen<br><br><table><tr><th style='text-align: left;'><b>" + selectFileQuery.value(0).toString() + " " + selectFileQuery.value(1).toString() +
                      "<br>" + selectFileQuery.value(2).toString() +
                      "<br><span style='color:#99cc00;'>Green</span> Lion Racing</b></th><th style='padding-left: 50px;'><img src='https://glracing.de/wp-content/uploads/2024/03/black_inline_transparent.png' alt='' style='height:53px;'></th></tr></table><br>Bergische Universität Wuppertal<br>Raum W.08.40<br>Gaußstraße 20, 42119 Wuppertal, Deutschland<br><br>" +
                      phone +
                      mail +
                      "<a href='https://glracing.de/'>glracing.de</a>";

        file.setFileName(fileName);
        file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
        file.write(fileContent.toUtf8());
    }
}

void displayTables::on_pb_download_all_clicked() {
    QVector<QString> fileName;
    QVector<QString> fileContent;
    QString filePath;
    QFile file;
    QSqlQuery selectFileQuery;

    filePath = QFileDialog::getExistingDirectory(this, tr("Ordner benutzen"));
    if (filePath == "")
        return;

    if (download_mode == 0) {

        selectFileQuery.prepare("SELECT datei, dateiname FROM kommunikation_dateien");
        selectFileQuery.exec();
        while(selectFileQuery.next()) {
            fileContent.push_back(selectFileQuery.value(0).toString());
            fileName.push_back(selectFileQuery.value(1).toString());
        }

        for (int i = 0; i < fileName.length(); i++) {
            file.setFileName(filePath + "/" + fileName[i]);
            file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
            file.write(fileContent[i].toUtf8());
        }
    } else if (download_mode == 1) {

        selectFileQuery.prepare("SELECT vorname, nachname, position, telefon, email_glr FROM mitglieder");
        selectFileQuery.exec();
        while(selectFileQuery.next()) {
            QString phone = "";
            if (!selectFileQuery.value(3).toString().isEmpty()) {
                phone = "<a href='tel:" + selectFileQuery.value(3).toString() + "'>" + selectFileQuery.value(3).toString() + "</a><br>";
            }

            QString mail = "";
            if (!selectFileQuery.value(4).toString().isEmpty()) {
                mail = "<a href='mailto:" + selectFileQuery.value(4).toString() + "'>" + selectFileQuery.value(4).toString() + "</a><br>";
            }

            fileContent.push_back("Mit freundlichen Grüßen<br><br><table><tr><th style='text-align: left;'><b>" + selectFileQuery.value(0).toString() + " " + selectFileQuery.value(1).toString() +
                                  "<br>" + selectFileQuery.value(2).toString() +
                                  "<br><span style='color:#99cc00;'>Green</span> Lion Racing</b></th><th style='padding-left: 50px;'><img src='https://glracing.de/wp-content/uploads/2024/03/black_inline_transparent.png' alt='' style='height:53px;'></th></tr></table><br>Bergische Universität Wuppertal<br>Raum W.08.40<br>Gaußstraße 20, 42119 Wuppertal, Deutschland<br><br>" +
                                  phone +
                                  mail +
                                  "<a href='https://glracing.de/'>glracing.de</a>");
            fileName.push_back("Signatur " + selectFileQuery.value(0).toByteArray() + " " + selectFileQuery.value(1).toByteArray() + ".html");
        }

        for (int i = 0; i < fileName.length(); i++) {
            file.setFileName(filePath + "/" + fileName[i]);
            file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
            file.write(fileContent[i].toUtf8());
        }
    }
}

void displayTables::on_pb_save_clicked()
{

}
