#include "displaytables.h"
#include "ui_displaytables.h"
#include <QFileDialog>

static int showCompanyName = 0;
static bool tableCompanyActiv = 0;

displayTables::displayTables(QWidget *parent) :
    QDialog(parent),
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
}

displayTables::~displayTables()
{
    delete ui;
}

void displayTables::on_cb_table_currentTextChanged(const QString &arg1)
{
    ui->pb_download->setVisible(false);     //Button "pb_download" (alle herunterladen) nicht sichtbar
    ui->pb_save->setVisible(false);
    ui->pb_signature->setVisible(false);
    ui->cb_companyName->setVisible(false);
   //Checkboxes
    ui->cb_gold->setVisible(false);
    ui->cb_silver->setVisible(false);
    ui->cb_bronze->setVisible(false);
    ui->cb_supporter->setVisible(false);

    selectedTable = ui->cb_table->currentText();
    modal = new QSqlTableModel();
    modal->setQuery("SELECT * FROM " + selectedTable);

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
    ui->cb_companyName->setVisible(false);

    if (selectedTable == "kommunikation_dateien")   //Button "pb_download" (alle herunterladen) nur bei dieser Tabelle sichtbar
        ui->pb_download->setVisible(true);
    else if (selectedTable == "firmen") {
        //ui->cb_rank->setVisible(true);
        //rank = ui->cb_rank->currentText();
        //filter = "firma = '" + rank + "'";

        //modal->setFilter(filter);
        modal->setQuery("SELECT * FROM " + selectedTable);
        ui->cb_gold->setVisible(true);
        ui->cb_silver->setVisible(true);
        ui->cb_bronze->setVisible(true);
        ui->cb_supporter->setVisible(true);

        tableCompanyActiv = 1;
    }
    else if (selectedTable == "personen" || selectedTable=="kommunikationen") {
        ui->cb_companyName->setVisible(true);
        companyName = ui->cb_companyName->currentText();
        showCompanyName = 1;

        QString companyId = getCompanyId();
        if (selectedTable == "kommunikationen") {
            ui->pb_save->setVisible(true);

            modal->setQuery("SELECT k.id, k.firma, k.ansprechpartner, k.wann, k.was, count(*) FROM kommunikationen k, kommunikation_dateien d  WHERE k.FirmenID = '" + companyId + "' AND k.id = d.kommunikation_id GROUP BY kommunikation_id");
        }
        else {
            // display filter company name
            //ui->cb_companyName->setVisible(true);
            //companyName = ui->cb_companyName->currentText();
            //filter = "firma = '" + companyName + "'";
            modal->setQuery("SELECT * FROM " + selectedTable + " WHERE FirmenId = '" + companyId + "'");
            //showCompanyName = 1;
        }
    } else if (selectedTable == "mitglieder") {
        ui->pb_signature->setVisible(true);
    }

    //modal->select();
    ui->tv_table->setSortingEnabled(true);
    //modal->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tv_table->setModel(modal);
    // Hide ID-coulmn
    ui->tv_table->setColumnHidden(0, true);
}

void displayTables::on_pb_download_clicked()
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

void displayTables::on_cb_gold_stateChanged(int arg1)
{
    if (ui->cb_silver->isChecked() && ui->cb_bronze->isChecked() && ui->cb_supporter->isChecked())
        checkBoxGold("silver_bronze_supporter");
    else if (ui->cb_silver->isChecked() && ui->cb_bronze->isChecked())
        checkBoxGold("silver_bronze");
    else if (ui->cb_silver->isChecked() && ui->cb_supporter->isChecked())
        checkBoxGold("silver_supporter");
    else if (ui->cb_bronze->isChecked() && ui->cb_supporter->isChecked())
        checkBoxGold("bronze_supporter");
    else if (ui->cb_silver->isChecked())
        checkBoxGold("silver");
    else if (ui->cb_bronze->isChecked())
        checkBoxGold("bronze");
    else if (ui->cb_supporter->isChecked())
        checkBoxGold("supporter");
    else
        checkBoxGold();
}

void displayTables::on_cb_silver_stateChanged(int arg1)
{
    if (ui->cb_silver->isChecked() && ui->cb_bronze->isChecked() && ui->cb_supporter->isChecked())
        checkBoxSilver("gold_bronze_supporter");
    else if (ui->cb_gold->isChecked() && ui->cb_bronze->isChecked())
        checkBoxSilver("gold_bronze");
    else if (ui->cb_gold->isChecked() && ui->cb_supporter->isChecked())
        checkBoxSilver("gold_supporter");
    else if (ui->cb_bronze->isChecked() && ui->cb_supporter->isChecked())
        checkBoxSilver("bronze_supporter");
    else if (ui->cb_gold->isChecked())
        checkBoxSilver("gold");
    else if (ui->cb_bronze->isChecked())
        checkBoxSilver("bronze");
    else if (ui->cb_supporter->isChecked())
        checkBoxSilver("supporter");
    else
        checkBoxSilver();
}

void displayTables::on_cb_bronze_stateChanged(int arg1)
{
    if (ui->cb_gold->isChecked() && ui->cb_silver->isChecked() && ui->cb_supporter->isChecked())
        checkBoxBronze("gold_silver_supporter");
    else if (ui->cb_gold->isChecked() && ui->cb_silver->isChecked())
        checkBoxBronze("gold_silver");
    else if (ui->cb_gold->isChecked() && ui->cb_supporter->isChecked())
        checkBoxBronze("gold_supporter");
    else if (ui->cb_silver->isChecked() && ui->cb_supporter->isChecked())
        checkBoxBronze("silver_supporter");
    else if (ui->cb_gold->isChecked())
        checkBoxBronze("gold");
    else if (ui->cb_silver->isChecked())
        checkBoxBronze("silver");
    else if (ui->cb_supporter->isChecked())
        checkBoxBronze("supporter");
    else
        checkBoxBronze();
}

void displayTables::on_cb_supporter_stateChanged(int arg1)
{
    if (ui->cb_gold->isChecked() && ui->cb_silver->isChecked() && ui->cb_bronze->isChecked())
        checkBoxSupporter("gold_silver_bronze");
    else if (ui->cb_gold->isChecked() && ui->cb_silver->isChecked())
        checkBoxSupporter("gold_silver");
    else if (ui->cb_gold->isChecked() && ui->cb_bronze->isChecked())
        checkBoxSupporter("gold_bronze");
    else if (ui->cb_silver->isChecked() && ui->cb_bronze->isChecked())
        checkBoxSupporter("silver_bronze");
    else if (ui->cb_gold->isChecked())
        checkBoxSupporter("gold");
    else if (ui->cb_silver->isChecked())
        checkBoxSupporter("silver");
    else if (ui->cb_bronze->isChecked())
        checkBoxSupporter("bronze");
    else
        checkBoxSupporter();
}

void displayTables::checkBoxGold(QString otherCheckedCheckBoxes) {
    QString filter;
    if (ui->cb_gold->isChecked()) {
        //QString filter;
        //modal->setTable("firmen");

        if (otherCheckedCheckBoxes == "silver")
            filter = "rang = 'Gold' OR rang = 'Silber'";
        else if (otherCheckedCheckBoxes == "bronze")
            filter = "rang = 'Gold' OR rang = 'Bronze'";
        else if (otherCheckedCheckBoxes == "supporter")
            filter = "rang = 'Silber' OR = 'Supporter'";
        else if (otherCheckedCheckBoxes == "silver_bronze")
            filter = "rang = 'Gold' OR rang = 'Silber' OR rang = 'Bronze'";
        else if (otherCheckedCheckBoxes == "silver_supporter")
            filter = "rang = 'Gold' OR rang = 'Silver' OR rang = 'Supporter'";
        else if (otherCheckedCheckBoxes == "bronze_supporter")
            filter = "rang = 'Gold' OR rang = 'Bronze' OR rang = 'Supporter'";
        else if (otherCheckedCheckBoxes == "silver_bronze_supporter")
            filter = "rang = 'Gold' OR rang = 'Silver' OR rang = 'Bronze' OR rang = 'Supporter'";
        else
            filter = "rang = 'Gold'";

        //modal->setFilter(filter);
        //modal->select();
        ui->tv_table->setModel(modal);
    }
    else if (otherCheckedCheckBoxes == "silver") {
        modal->clear();
        filter = "rang = 'Silber'";
    }
    else if (otherCheckedCheckBoxes == "bronze") {
        modal->clear();
        filter = "rang = 'Bronze'";
    }
    else if (otherCheckedCheckBoxes == "supporter") {
        modal->clear();
        filter = "rang = 'Supporter'";
    }
    else if (otherCheckedCheckBoxes == "silver_supporter") {
        modal->clear();
        filter = "rang = 'Silver' OR rang = 'Supporter'";
    }
    else if (otherCheckedCheckBoxes == "bronze_supporter") {
        modal->clear();
        filter = "rang = 'Bronze' OR rang = 'Supporter'";
    }
    else if (otherCheckedCheckBoxes == "silver_bronze") {
        modal->clear();
        filter = "rang = 'Silber' OR rang = 'Bronze'";
    }
    else if (otherCheckedCheckBoxes == "silver_bronze_supporter") {
        modal->clear();
        filter = "rang = 'Silber' OR rang = 'Bronze' OR rang = 'Supporter'";
    }
    else {
        modal->clear();
        filter = "";
    }
    //modal->clear();
    //modal->setTable("firmen");
    //modal->setFilter(filter);
    //modal->select();
    ui->tv_table->setModel(modal);
}

void displayTables::checkBoxSilver(QString otherCheckedCheckBoxes) {
    QString filter;
    if (ui->cb_silver->isChecked()) {
        //modal->setTable("firmen");

        if (otherCheckedCheckBoxes == "gold")
            filter = "rang = 'Silber' OR rang = 'Gold'";
        else if (otherCheckedCheckBoxes == "bronze")
            filter = "rang = 'Silber' OR rang = 'Bronze'";
        else if (otherCheckedCheckBoxes == "supporter")
            filter = "rang = 'Silber' OR = 'Supporter'";
        else if (otherCheckedCheckBoxes == "gold_bronze")
            filter = "rang = 'Silber' OR rang = 'Gold' OR rang = 'Bronze'";
        else if (otherCheckedCheckBoxes == "gold_supporter")
            filter = "rang = 'Silber' OR rang = 'Gold' OR rang = 'Supporter'";
        else if (otherCheckedCheckBoxes == "bronze_supporter")
            filter = "rang = 'Silber' OR rang = 'Bronze' OR rang = 'Supporter'";
        else if (otherCheckedCheckBoxes == "gold_bronze_supporter")
            filter = "rang = 'Silber' OR rang = 'Gold' OR rang = 'Bronze' OR rang = 'Supporter'";
        else
            filter = "rang = 'Silber'";

        //modal->setFilter(filter);
        //modal->select();
        ui->tv_table->setModel(modal);
    }
    else if (otherCheckedCheckBoxes == "gold") {
        modal->clear();
        filter = "rang = 'Gold'";
    }
    else if (otherCheckedCheckBoxes == "bronze") {
        modal->clear();
        filter = "rang = 'Bronze'";
    }
    else if (otherCheckedCheckBoxes == "supporter") {
        modal->clear();
        filter = "rang = 'Supporter'";
    }
    else if (otherCheckedCheckBoxes == "gold_supporter") {
        modal->clear();
        filter = "rang = 'Gold' OR rang = 'Supporter'";
    }
    else if (otherCheckedCheckBoxes == "bronze_supporter") {
        modal->clear();
        filter = "rang = 'Bronze' OR rang = 'Supporter'";
    }
    else if (otherCheckedCheckBoxes == "gold_bronze") {
        modal->clear();
        filter = "rang = 'Gold' OR rang = 'Bronze'";
    }
    else if (otherCheckedCheckBoxes == "gold_bronze_supporter") {
        modal->clear();
        filter = "rang = 'Gold' OR rang = 'Bronze' OR rang = 'Supporter'";
    }
    else {
        modal->clear();
        filter = "";
    }
   // modal->clear();
    //modal->setTable("firmen");
    //modal->select();
    //modal->setFilter(filter);
    ui->tv_table->setModel(modal);
}

void displayTables::checkBoxBronze(QString otherCheckedCheckBoxes) {
    QString filter;
    if (ui->cb_bronze->isChecked()) {

        //modal->setTable("firmen");

        if (otherCheckedCheckBoxes == "gold")
            filter = "rang = 'Bronze' OR rang = 'Gold'";
        else if (otherCheckedCheckBoxes == "silver")
            filter = "rang = 'Bronze' OR rang = 'Silber'";
        else if (otherCheckedCheckBoxes == "supporter")
            filter = "rang = 'Silber' OR = 'Supporter'";
        else if (otherCheckedCheckBoxes == "gold_silver")
            filter = "rang = 'Bronze' OR rang = 'Gold' OR rang = 'Silber'";
        else if (otherCheckedCheckBoxes == "gold_supporter")
            filter = "rang = 'Bronze' OR rang = 'Gold' OR rang = 'Supporter'";
        else if (otherCheckedCheckBoxes == "silver_silver")
            filter = "rang = 'Bronze' OR rang = 'Silber' OR rang = 'Supporter'";
        else if (otherCheckedCheckBoxes == "gold_silver_supporter")
            filter = "rang = 'Bronze' OR rang = 'Gold' OR rang = 'Silber' OR rang = 'Supprter'";
        else
            filter = "rang = 'Bronze'";

        //modal->setFilter(filter);
        //modal->select();
        //ui->tv_table->setModel(modal);
    }
    else if (otherCheckedCheckBoxes == "gold") {
        modal->clear();
        filter = "rang = 'Gold'";
    }
    else if (otherCheckedCheckBoxes == "silver") {
        modal->clear();
        filter = "rang = 'Silber'";
    }
    else if (otherCheckedCheckBoxes == "supporter") {
        modal->clear();
        filter = "rang = 'Supporter'";
    }
    else if (otherCheckedCheckBoxes == "gold_supporter") {
        modal->clear();
        filter = "rang = 'Gold' OR rang = 'Supporter'";
    }
    else if (otherCheckedCheckBoxes == "silver_supporter") {
        modal->clear();
        filter = "rang = 'Silber' OR rang = 'Supporter'";
    }
    else if (otherCheckedCheckBoxes == "gold_silver") {
        modal->clear();
        filter = "rang = 'Gold' OR rang = 'Silber'";
    }
    else if (otherCheckedCheckBoxes == "gold_silver_supporter") {
        modal->clear();
        filter = "rang = 'Gold' OR rang = 'Silber' OR rang = 'Supporter'";
    }
    else {
        modal->clear();
        filter = "";
    }
    //modal->clear();
    //modal->setTable("firmen");
    //modal->setFilter(filter);
    //modal->select();
    ui->tv_table->setModel(modal);
}

void displayTables::checkBoxSupporter(QString otherCheckedCheckBoxes) {
    QString filter;
    if (ui->cb_supporter->isChecked()) {

        //modal->setTable("firmen");

        if (otherCheckedCheckBoxes == "gold")
            filter = "rang = 'Supporter' OR rang = 'Gold'";
        else if (otherCheckedCheckBoxes == "silver")
            filter = "rang = 'Supporter' OR rang = 'Silber'";
        else if (otherCheckedCheckBoxes == "bronze")
            filter = "rang = 'Supporter' OR rang = 'Bronze'";
        else if (otherCheckedCheckBoxes == "gold_silver")
            filter = "rang = 'Supporter' OR rang = 'Gold' OR rang = 'Silber'";
        else if (otherCheckedCheckBoxes == "gold_bronze")
            filter = "rang = 'Supporter' OR rang = 'Gold' OR rang = 'Bronze'";
        else if (otherCheckedCheckBoxes == "silver_bronze")
            filter = "rang = 'Supporter' OR rang = 'Silber' OR rang = 'Bronze'";
        else if (otherCheckedCheckBoxes == "gold_silver_bronze")
            filter = "rang = 'Supporter' OR rang = 'Gold' OR rang = 'Silber' OR rang = 'Bronze'";
        else
            filter = "rang = 'Supporter'";

        //modal->setFilter(filter);
        //modal->select();
        ui->tv_table->setModel(modal);
    }
    else if (otherCheckedCheckBoxes == "gold") {
        modal->clear();
        filter = "rang = 'Gold'";
    }
    else if (otherCheckedCheckBoxes == "silver") {
        modal->clear();
        filter = "rang = 'Silver'";
    }
    else if (otherCheckedCheckBoxes == "bronze") {
        modal->clear();
        filter = "rang = 'Bronze'";
    }
    else if (otherCheckedCheckBoxes == "gold_silver") {
        modal->clear();
        filter = "rang = 'Gold' OR rang = 'Silber'";
    }
    else if (otherCheckedCheckBoxes == "silver_Bronze") {
        modal->clear();
        filter = "rang = 'Silber' OR rang = 'Bronze'";
    }
    else if (otherCheckedCheckBoxes == "gold_bronze") {
        modal->clear();
        filter = "rang = 'Gold' OR rang = 'Bronze'";
    }
    else if (otherCheckedCheckBoxes == "gold_silver_bronze") {
        modal->clear();
        filter = "rang = 'Gold' OR rang = 'Silber' OR rang = 'Bronze'";
    }
    else {
        modal->clear();
        filter = "";
    }
    //modal->clear();
    //modal->setTable("firmen");
    //modal->setFilter(filter);
    //modal->select();
    ui->tv_table->setModel(modal);
}

void displayTables::on_cb_companyName_currentTextChanged(const QString &arg1)
{
    ui->cb_companyName->setVisible(true);
    QString companyName = ui->cb_companyName->currentText();
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

void displayTables::on_tv_table_clicked(const QModelIndex &index)
{
    int row = index.row();
    QSqlRecord record = modal->record(row);
    id = record.value(0).toInt();

    /*
    QString name;
    QByteArray fileContent;
    QVector<int> ids;
    QString fileName;
    QString filePath;
    QFile file;

    //fileName = QFileDialog::getSaveFileName(this, tr("Save Document"), name);
    filePath = QFileDialog::getExistingDirectory(this, tr("Open Directory"));

    QSqlQuery selectFileQuery;

    selectFileQuery.prepare("SELECT datei, dateiname FROM kommunikation_dateien WHERE kommunikation_id = :id");
    selectFileQuery.bindValue(":id", id);
    selectFileQuery.exec();
    while(selectFileQuery.next()) {
        fileContent = selectFileQuery.value(0).toByteArray();
        name = selectFileQuery.value(1).toString();
    }
    fileName = filePath + "\\" + name;
    file.setFileName(fileName);
    file.open(QIODevice::ReadWrite);

    file.write(fileContent);
    */
}

void displayTables::on_pb_signature_clicked()
{
    QString fileName;
    QString fileContent;
    QFile file;

    QSqlQuery selectFileQuery;
    selectFileQuery.prepare("SELECT vorname, nachname, position, telefon, email_glr FROM mitglieder WHERE id = :id");
    selectFileQuery.bindValue(":id", id);
    selectFileQuery.exec();
    selectFileQuery.next();

    fileContent = "Mit freundlichen Grüßen<br><br><table><tr><th style='text-align: left;'><b>" + selectFileQuery.value(0).toString() + " " + selectFileQuery.value(1).toString() +
                  "<br>" + selectFileQuery.value(2).toString() +
                  "<br><span style='color:#99cc00;'>Green</span> Lion Racing</b></th><th style='padding-left: 50px;'><img src='https://glracing.de/wp-content/uploads/2024/03/black_inline_transparent.png' alt='' style='height:53px;'></th></tr></table><br>Bergische Universität Wuppertal<br>Raum W.08.40<br>Gaußstraße 20, 42119 Wuppertal, Deutschland<br><br><a href='tel:" +
                  selectFileQuery.value(3).toString() +
                  "'>" +
                  selectFileQuery.value(3).toString() +
                  "</a><br><a href='mailto:" +
                  selectFileQuery.value(4).toString() +
                  "'>" +
                  selectFileQuery.value(4).toString() +
                  "</a><br><a href='https://glracing.de/'>glracing.de</a>";

    QString filter = "HTML Files (*.html)";
    fileName = QFileDialog::getSaveFileName(this, tr("Signatur speichern"), "Signatur " + selectFileQuery.value(0).toByteArray() + " " + selectFileQuery.value(1).toByteArray() + ".html", filter, &filter);

    file.setFileName(fileName);
    file.open(QIODevice::ReadWrite);
    file.write(fileContent.toUtf8());
}

void displayTables::on_pb_save_clicked()
{
    QVector<QString> name;
    QVector<QByteArray> fileContent;
    QString fileName;
    QString filePath;
    QFile file;

    //fileName = QFileDialog::getSaveFileName(this, tr("Save Document"), name);
    filePath = QFileDialog::getExistingDirectory(this, tr("Open Directory"));

    QSqlQuery selectFileQuery;

    selectFileQuery.prepare("SELECT datei, dateiname FROM kommunikation_dateien WHERE kommunikation_id = :id");
    selectFileQuery.bindValue(":id", id);
    selectFileQuery.exec();
    while(selectFileQuery.next()) {
        fileContent.push_back(selectFileQuery.value(0).toByteArray());
        name.push_back(selectFileQuery.value(1).toString());
    }
    for (int i = 0; i < name.length(); i++) {
        //fileName = filePath + "\\" + name[i];
        fileName = filePath + "/" + name[i];
        file.setFileName(fileName);
        file.open(QIODevice::ReadWrite);
        file.write(fileContent[i]);
    }
}

QString displayTables::getCompanyId () {
    QSqlQuery queryCompanyId;
    QString companyName = ui->cb_companyName->currentText();
    queryCompanyId.prepare("SELECT id FROM firmen WHERE name = :companyName");
    queryCompanyId.bindValue(":companyName", companyName);
    queryCompanyId.exec();

    QString companyId;
    while (queryCompanyId.next())
        companyId = queryCompanyId.value(0).toString();

    return companyId;
}

