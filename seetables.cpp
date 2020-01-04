#include "seetables.h"
#include "ui_seetables.h"
#include <QFileDialog>

static int showCompanyName = 0;
static bool tableCompanyActiv = 0;

seeTables::seeTables(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::seeTables)
{
    ui->setupUi(this);

    QSqlQuery selectTable;
    selectTable.prepare("SELECT name FROM (SELECT * FROM sqlite_master UNION ALL SELECT * FROM sqlite_temp_master)WHERE type='table' ORDER BY name");
    selectTable.exec();
    QSqlQueryModel * modalComboBox = new QSqlQueryModel();
    modalComboBox->setQuery(selectTable);
    ui->cb_table->setModel(modalComboBox);
}

seeTables::~seeTables()
{
    delete ui;
}

void seeTables::on_cb_table_currentTextChanged(const QString &arg1)
{
    ui->pb_download->setVisible(false);     //Button "pb_download" (alle herunterladen) nicht sichtbar
    ui->cb_companyName->setVisible(false);
   //Checkboxes
    ui->cb_gold->setVisible(false);
    ui->cb_silver->setVisible(false);
    ui->cb_bronze->setVisible(false);

    QString selectedTable = ui->cb_table->currentText();
    modal = new QSqlTableModel();
    modal->setTable(selectedTable);

    QString companyName;
    QString rank;
    QString filter;

    showCompanyName = 0;

    //Alle Firmennamen
    QSqlQuery selectName;
    selectName.prepare("SELECT name FROM firmen");
    selectName.exec();
    QSqlQueryModel * modalComboBox = new QSqlQueryModel();
    modalComboBox->setQuery(selectName);
    ui->cb_companyName->setModel(modalComboBox);

    if (selectedTable == "kommunikation_dateien")   //Button "pb_download" (alle herunterladen) nur bei dieser Tabelle sichtbar
        ui->pb_download->setVisible(true);
    else if (selectedTable == "firmen") {
        //ui->cb_rank->setVisible(true);
        //rank = ui->cb_rank->currentText();
        //filter = "firma = '" + rank + "'";

        modal->setFilter(filter);
        ui->cb_gold->setVisible(true);
        ui->cb_silver->setVisible(true);
        ui->cb_bronze->setVisible(true);

        tableCompanyActiv = 1;
    }
    else if (selectedTable == "personen") {
        ui->cb_companyName->setVisible(true);
        companyName = ui->cb_companyName->currentText();
        filter = "firma = '" + companyName + "'";

        modal->setFilter(filter);
        showCompanyName = 1;
    }

    modal->select();
    ui->tv_tables->setSortingEnabled(true);
    modal->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tv_tables->setModel(modal);
    ui->tv_tables->setColumnHidden(0, true);
}

void seeTables::on_pb_download_clicked()
{
    QString name;
    QByteArray fileContent;
    QVector<int> ids;
    QString fileName;
    QString filePath;
    QFile file;

    // Alle IDs der Einträge
    QSqlQuery selectIdsQuery("SELECT id FROM kommunikation_dateien");
    while(selectIdsQuery.next()) {
        ids.push_back(selectIdsQuery.value(0).toInt());
    }

    //fileName = QFileDialog::getSaveFileName(this, tr("Save Document"), name);
    filePath = QFileDialog::getExistingDirectory(this, tr("Open Directory"));

    QSqlQuery selectFileQuery;
    for (int i = 0; i < ids.length(); i++) {
        selectFileQuery.prepare("SELECT datei, dateiname FROM kommunikation_dateien WHERE id = :id");
        selectFileQuery.bindValue(":id", ids[i]);
        selectFileQuery.exec();
        while(selectFileQuery.next()) {
            fileContent = selectFileQuery.value(0).toByteArray();
            name = selectFileQuery.value(1).toString();
        }
        fileName = filePath + "\\" + name;
        file.setFileName(fileName);
        file.open(QIODevice::ReadWrite);

        file.write(fileContent);
    }
}

void seeTables::on_cb_gold_stateChanged(int arg1)
{

}

void seeTables::on_cb_silver_stateChanged(int arg1)
{

}

void seeTables::on_cb_bronze_stateChanged(int arg1)
{

}

void seeTables::checkBoxGold(QString otherCheckedCheckBoxes) {
    QString filter;
    if (ui->cb_gold->isChecked()) {
        //QString filter;
        modal->setTable("firmen");

        if (otherCheckedCheckBoxes == "silver")
            filter = "rang = 'Gold' OR rang = 'Silber'";
        else if (otherCheckedCheckBoxes == "bronze")
            filter = "rang = 'Gold' OR rang = 'Bronze'";
        else if (otherCheckedCheckBoxes == "silver_bronze")
            filter = "rang = 'Gold' OR rang = 'Silber' OR rang = 'Bronze'";
        else
            filter = "rang = 'Gold'";

        modal->setFilter(filter);
        modal->select();
        ui->tv_tables->setModel(modal);
    }
    else if (otherCheckedCheckBoxes == "silver") {
        modal->clear();
        filter = "rang = 'Silber'";
    }
    else if (otherCheckedCheckBoxes == "bronze") {
        modal->clear();
        filter = "rang = 'Bronze'";
    }
    else if (otherCheckedCheckBoxes == "silver_bronze") {
        modal->clear();
        filter = "rang = 'Silber' OR rang = 'Bronze'";
    }
    else {
        modal->clear();
        filter = "";
    }
    //modal->clear();
    modal->setTable("firmen");
    modal->setFilter(filter);
    modal->select();
    ui->tv_tables->setModel(modal);
}

void seeTables::checkBoxSilver(QString otherCheckedCheckBoxes) {
    QString filter;
    if (ui->cb_silver->isChecked()) {
        modal->setTable("firmen");

        if (otherCheckedCheckBoxes == "gold")
            filter = "rang = 'Silber' OR rang = 'Gold'";
        else if (otherCheckedCheckBoxes == "bronze")
            filter = "rang = 'Silber' OR rang = 'Bronze'";
        else if (otherCheckedCheckBoxes == "gold_bronze")
            filter = "rang = 'Silber' OR rang = 'Gold' OR rang = 'Bronze'";
        else
            filter = "rang = 'Silber'";

        modal->setFilter(filter);
        modal->select();
        ui->tv_tables->setModel(modal);
    }
    else if (otherCheckedCheckBoxes == "gold") {
        modal->clear();
        filter = "rang = 'Gold'";
    }
    else if (otherCheckedCheckBoxes == "bronze") {
        modal->clear();
        filter = "rang = 'Bronze'";
    }
    else if (otherCheckedCheckBoxes == "gold_bronze") {
        modal->clear();
        filter = "rang = 'Gold' OR rang = 'Bronze'";
    }
    else {
        modal->clear();
        filter = "";
    }
   // modal->clear();
    modal->setTable("firmen");
    modal->select();
    modal->setFilter(filter);
    ui->tv_tables->setModel(modal);
}

void seeTables::checkBoxBronze(QString otherCheckedCheckBoxes) {
    QString filter;
    if (ui->cb_bronze->isChecked()) {

        modal->setTable("firmen");

        if (otherCheckedCheckBoxes == "gold")
            filter = "rang = 'Bronze' OR rang = 'Gold'";
        else if (otherCheckedCheckBoxes == "silver")
            filter = "rang = 'Bronze' OR rang = 'Silber'";
        else if (otherCheckedCheckBoxes == "gold_silver")
            filter = "rang = 'Bronze' OR rang = 'Gold' OR rang = 'Silber'";
        else
            filter = "rang = 'Bronze'";

        modal->setFilter(filter);
        modal->select();
        ui->tv_tables->setModel(modal);
    }
    else if (otherCheckedCheckBoxes == "gold") {
        modal->clear();
        filter = "rang = 'Gold'";
    }
    else if (otherCheckedCheckBoxes == "silver") {
        modal->clear();
        filter = "rang = 'Silver'";
    }
    else if (otherCheckedCheckBoxes == "gold_silver") {
        modal->clear();
        filter = "rang = 'Gold' OR rang = 'Silber'";
    }
    else {
        modal->clear();
        filter = "";
    }
    //modal->clear();
    modal->setTable("firmen");
    modal->setFilter(filter);
    modal->select();
    ui->tv_tables->setModel(modal);
}
