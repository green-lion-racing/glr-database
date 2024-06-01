#include "tables.h"
#include "ui_tables.h"
#include <QFileDialog>
#include <QCloseEvent>
#include <QMessageBox>
#include "error.h"

Tables::Tables(QWidget *parent, bool editMode) :
    QMainWindow(parent),
    ui(new Ui::Tables)
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
    ui->tv_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tv_table->setSortingEnabled(true);

    ui->pb_save->setVisible(false);

    on_cb_table_currentIndexChanged();

    if (editMode) {
        ui->cb_editMode->setCheckState(Qt::CheckState(2));
        on_cb_editMode_stateChanged();
    }
}

Tables::~Tables()
{
    delete ui;
    this->destroy();
}

void Tables::closeEvent(QCloseEvent *event) {
    if (tableModel->isDirty()) {
        QMessageBox::StandardButton box = unsaved_changes_notify();

        if (box != QMessageBox::Yes) {
            event->ignore();
        } else
            event->accept();
    } else {
        event->accept();
    }
}

QString Tables::getCompanyId () {
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

void Tables::on_cb_table_currentIndexChanged()
{
    if (tableModel != NULL && tableModel->isDirty()) {
        if (ui->cb_table->currentText() == tableModel->tableName())
            return;
        QMessageBox::StandardButton box = unsaved_changes_notify();
        if (box != QMessageBox::Yes) {
            ui->cb_table->setCurrentText(tableModel->tableName());
            return;
        }
    }
    ui->pb_download->setVisible(false);
    // ui->pb_download_all->setVisible(false);

    // Are filters even needed? But they look nice... and make everthing complex
    ui->cb_filter->setVisible(false); // TODO
    ui->le_search->setVisible(false); // TODO https://www.google.com/search?client=firefox-b-d&q=sql+search+value+in+all+table

    // Checkboxes
    ui->cb_filter_gold->setVisible(false);
    ui->cb_filter_silver->setVisible(false);
    ui->cb_filter_bronze->setVisible(false);
    ui->cb_filter_supporter->setVisible(false);

    selectedTable = ui->cb_table->currentText();
    tableModel = new QSqlTableModel();
    tableModel->setTable(selectedTable);

    // undo potenial hidden
    ui->tv_table->setColumnHidden(2, false);

    if (selectedTable == "kommunikation_dateien") {
        download_mode = 0;
        ui->pb_download->setText("Ausgewählte Kommunikationen speichern");
        ui->pb_download->setVisible(true);
        ui->pb_download->setDisabled(true);
        // hiding files because it creates massive lags
        // there is probably a better solution, but I dont know it
        ui->tv_table->setColumnHidden(2, true);
    } else if (selectedTable == "firmen") {
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

        //ui->cb_filter->setVisible(true);

        // companyName = ui->cb_filter->currentText();
        // QString companyId = getCompanyId();
        // tableModel->setQuery("SELECT * FROM " + selectedTable + " WHERE FirmenId = '" + companyId + "'");
        // tableModel->setQuery("SELECT k.id, k.firma, k.ansprechpartner, k.wann, k.was, count(*) FROM kommunikationen k, kommunikation_dateien d  WHERE k.FirmenID = '" + companyId + "' AND k.id = d.kommunikation_id GROUP BY kommunikation_id");

    } else if (selectedTable == "mitglieder") {
        download_mode = 1;
        ui->pb_download->setText("Ausgewählte Signaturen speichern");
        ui->pb_download->setVisible(true);
        ui->pb_download->setDisabled(true);
    }

    tableModel->select();
    tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tv_table->setModel(tableModel);

    // Selction changed signal only works if QTableView got already a model set!!!!
    connect(ui->tv_table->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)), this, SLOT(selection_changed()));
}

void Tables::on_cb_filter_currentIndexChanged()
{
    ui->cb_filter->setVisible(true);
    QString companyName = ui->cb_filter->currentText();
    QString companyId = getCompanyId();
    // if (selectedTable == "kommunikationen")
    //     tableModel->setQuery("SELECT k.id, k.firma, k.ansprechpartner, k.wann, k.was, count(*) FROM kommunikationen k, kommunikation_dateien d  WHERE k.FirmenID = '" + companyId + "' AND k.id = d.kommunikation_id GROUP BY kommunikation_id");
    // else
    //     tableModel->setQuery("SELECT * FROM " + selectedTable + " WHERE firma = '" + companyName  + "'");

    //tableModel->filter()
    /*QString filter = "firma = '" + companyName + "'";

    //modal->select();
    ui->tv_table->setModel(modal);
    //modal->setFilter(filter);
    //modal->setFilter(filter);
    //modal->select();
    ui->tv_table->setModel(modal);
    */
}

void Tables::on_cb_filter_gold_stateChanged() {
    update_cb_filter();
}

void Tables::on_cb_filter_silver_stateChanged() {
    update_cb_filter();
}

void Tables::on_cb_filter_bronze_stateChanged() {
    update_cb_filter();
}

void Tables::on_cb_filter_supporter_stateChanged() {
    update_cb_filter();
}

void Tables::update_cb_filter() {
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

    tableModel->setTable("firmen");
    tableModel->setFilter(filter);
    tableModel->select();
    ui->tv_table->setModel(tableModel);
}

void Tables::on_pb_download_clicked() {
    QString fileName;
    QString fileContent;
    QString filePath;
    QFile file;
    QSqlQuery selectFileQuery;

    QModelIndexList rows = ui->tv_table->selectionModel()->selectedRows();

    for (int i = 0; i < rows.size(); i++){
        qDebug() << rows[i].data().toString();
    }

    if (rows.length() > 1) {
        filePath = QFileDialog::getExistingDirectory(this, tr("Ordner benutzen"));
        if (filePath == "")
            return;
    }

    if (download_mode == 0) {
        for (int i = 0; i < rows.length(); i++) {
            selectFileQuery.prepare("SELECT datei, dateiname FROM kommunikation_dateien WHERE id = :id");
            selectFileQuery.bindValue(":id", rows[i].data().toInt());
            selectFileQuery.exec();
            selectFileQuery.next();

            if (rows.length() > 1) {
                file.setFileName(filePath + "/" + selectFileQuery.value(1).toString());
            }
            else {
                fileName = QFileDialog::getSaveFileName(this, tr("Kommunikation speichern"), selectFileQuery.value(1).toString());
                if (fileName == "")
                    return;
                file.setFileName(fileName);
            }

            fileContent = selectFileQuery.value(0).toByteArray();
            file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
            file.write(fileContent.toUtf8());
            file.close();
        }
    } else if (download_mode == 1) {
        for (int i = 0; i < rows.length(); i++) {

            selectFileQuery.prepare("SELECT vorname, nachname, position, telefon, email_glr FROM mitglieder WHERE id = :id");
            selectFileQuery.bindValue(":id", rows[i].data().toInt());
            selectFileQuery.exec();
            selectFileQuery.next();

            if (rows.length() > 1) {
                file.setFileName(filePath + "/Signatur " + selectFileQuery.value(0).toByteArray() + " " + selectFileQuery.value(1).toByteArray() + ".txt");
            }
            else {
                QString filter = "TXT Files (*.txt)";
                fileName = QFileDialog::getSaveFileName(this, tr("Signatur speichern"), "Signatur " + selectFileQuery.value(0).toByteArray() + " " + selectFileQuery.value(1).toByteArray() + ".txt", filter, &filter);
                if (fileName == "")
                    return;
                file.setFileName(fileName);
            }

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
                          "<br><span style='color:#99cc00;'>Green</span> Lion Racing</b></th><th style='padding-left: 50px;'><img style='height:53px;' alt='' src='data:image/png;base64,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' /></th></tr></table><br>Bergische Universität Wuppertal<br>Raum W.08.40<br>Gaußstraße 20, 42119 Wuppertal, Deutschland<br><br>" +
                          phone +
                          mail +
                          "<a href='https://glracing.de/'>glracing.de</a>";

            file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
            file.write(fileContent.toUtf8());
            file.close();
        }
    }
}

void Tables::on_cb_editMode_stateChanged() {
    if (ui->cb_editMode->isChecked()) {
        QWidget::setWindowTitle("GLR Datenbank - Einträge bearbeiten");
        ui->l_dialogTitle->setText("Tabellen bearbeiten");
        ui->tv_table->setEditTriggers(QAbstractItemView::AllEditTriggers);
        ui->pb_save->setVisible(true);
        ui->le_search->setEnabled(false);
        ui->cb_filter->setEnabled(false);
        ui->cb_filter_gold->setEnabled(false);
        ui->cb_filter_silver->setEnabled(false);
        ui->cb_filter_bronze->setEnabled(false);
        ui->cb_filter_supporter->setEnabled(false);
        ui->pb_save->setEnabled(false);
        connect(ui->tv_table->model(), SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(unsaved_changes()));
    } else {
        QWidget::setWindowTitle("GLR Datenbank - Einträge ansehen");
        ui->l_dialogTitle->setText("Tabellen ansehen");
        ui->tv_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->pb_save->setVisible(false);
        ui->le_search->setEnabled(true);
        ui->cb_filter->setEnabled(true);
        ui->cb_filter_gold->setEnabled(true);
        ui->cb_filter_silver->setEnabled(true);
        ui->cb_filter_bronze->setEnabled(true);
        ui->cb_filter_supporter->setEnabled(true);
    }
}

void Tables::selection_changed() {
    QItemSelectionModel *select = ui->tv_table->selectionModel();

    QString object = "";
    if (download_mode == 0)
        object = "Kommunikation";
    else if (download_mode == 1)
        object = "Signatur";

    int count = select->selectedRows().length();

    if (count == 0) {
        ui->pb_download->setText("Ausgewählte " + object + " speichern");
        ui->pb_download->setDisabled(true);
    } else if (count == 1) {
        ui->pb_download->setText("Ausgewählte " + object + " speichern");
        ui->pb_download->setDisabled(false);
    } else {
        ui->pb_download->setText(QString::number(count) + " ausgewählte " + object + "en speichern");
        ui->pb_download->setDisabled(false);
    }
}

void Tables::unsaved_changes() {
    ui->cb_editMode->setEnabled(false);
    ui->pb_save->setEnabled(true);
}

QMessageBox::StandardButton Tables::unsaved_changes_notify() {
    QMessageBox::StandardButton box = QMessageBox::Yes;
    box = QMessageBox::warning(this, "Ungespeicherte Änderungen",
                         tr("Noch ungespeicherte Änderungen.\n Sollen diese verworfen werden?"),
                         QMessageBox::No | QMessageBox::Yes,
                         QMessageBox::Yes);
    return box;
}

void Tables::on_pb_save_clicked() {
    bool status = tableModel->submitAll();
    if (!status) {
        QString lastError = tableModel->lastError().text();

        Error errorWindow;
        errorWindow.setText(lastError);
        errorWindow.setModal(true);
        errorWindow.exec();
        return;
    }
    ui->cb_editMode->setEnabled(true);
    ui->pb_save->setEnabled(false);
}
