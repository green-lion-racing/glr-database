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
    ui->cb_filter->setVisible(false); // maybe TODO
    ui->le_search->setVisible(false); // maybe TODO https://www.google.com/search?client=firefox-b-d&q=sql+search+value+in+all+table

    // Checkboxes
    ui->cb_filter_gold->setVisible(false);
    ui->cb_filter_silver->setVisible(false);
    ui->cb_filter_bronze->setVisible(false);
    ui->cb_filter_supporter->setVisible(false);

    selectedTable = ui->cb_table->currentText();
    tableModel = new QSqlTableModel();
    tableModel->setTable(selectedTable);

    // undo potenial hidden
    ui->tv_table->setColumnHidden(3, false);

    if (selectedTable == "kommunikationen_dateien") {
        download_mode = 0;
        ui->pb_download->setText("Ausgewählte Kommunikationen speichern");
        ui->pb_download->setVisible(true);
        ui->pb_download->setDisabled(true);
        // hiding files because it creates massive lags
        // there is probably a better solution, creating a new view and only use what needed
        ui->tv_table->setColumnHidden(3, true);
    } else if (selectedTable == "firmen") {
        // Are filters really needed?
        // ui->cb_filter_gold->setVisible(true);
        // ui->cb_filter_silver->setVisible(true);
        // ui->cb_filter_bronze->setVisible(true);
        // ui->cb_filter_supporter->setVisible(true);
    } else if (selectedTable == "personen" || selectedTable=="kommunikationen") {
        // Are filters really needed?
        //QSqlQuery selectName;
        //selectName.prepare("SELECT name FROM firmen");
        //selectName.exec();
        //QSqlQueryModel * modalComboBox = new QSqlQueryModel();
        //modalComboBox->setQuery(selectName);
        //ui->cb_filter->setModel(modalComboBox);
        //ui->cb_filter->setVisible(true);
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
    // Are filters really needed?
    // ui->cb_filter->setVisible(true);
    // QString companyName = ui->cb_filter->currentText();
    // QString companyId = getCompanyId();
    // if (selectedTable == "kommunikationen")
    //     tableModel->setQuery("SELECT k.id, k.firma, k.ansprechpartner, k.wann, k.was, count(*) FROM kommunikationen k, kommunikationen_dateien d  WHERE k.FirmenID = '" + companyId + "' AND k.id = d.kommunikation_id GROUP BY kommunikation_id");
    // else
    //     tableModel->setQuery("SELECT * FROM " + selectedTable + " WHERE firma = '" + companyName  + "'");

    // tableModel->filter()
    // QString filter = "firma = '" + companyName + "'";

    // modal->select();
    // ui->tv_table->setModel(modal);
    // modal->setFilter(filter);
    // modal->setFilter(filter);
    // modal->select();
    // ui->tv_table->setModel(modal);

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
    // Are filters really needed?
    // QVector<QString> checks;
    // QString filter = "";

    // if (ui->cb_filter_gold->isChecked()) {
    //     checks.push_back("rang = 'Gold'");
    // }

    // if (ui->cb_filter_silver->isChecked()) {
    //     checks.push_back("rang = 'Silber'");
    // }

    // if (ui->cb_filter_bronze->isChecked()) {
    //     checks.push_back("rang = 'Bronze'");
    // }

    // if (ui->cb_filter_supporter->isChecked()) {
    //     checks.push_back("rang = 'Supporter'");
    // }

    // for (int i = 0; i < checks.length() - 1; i++) {
    //     filter += checks[i] + " OR ";
    // }
    // if (!checks.isEmpty())
    //     filter += checks.constLast();

    // tableModel->setTable("firmen");
    // tableModel->setFilter(filter);
    // tableModel->select();
    // ui->tv_table->setModel(tableModel);
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
            selectFileQuery.prepare("SELECT dateiname, datei FROM kommunikationen_dateien WHERE id = :id");
            selectFileQuery.bindValue(":id", rows[i].data().toInt());
            selectFileQuery.exec();
            selectFileQuery.next();

            if (rows.length() > 1) {
                file.setFileName(filePath + "/" + selectFileQuery.value(0).toString());
            }
            else {
                fileName = QFileDialog::getSaveFileName(this, tr("Kommunikation speichern"), selectFileQuery.value(0).toString());
                if (fileName == "")
                    return;
                file.setFileName(fileName);
            }

            fileContent = selectFileQuery.value(1).toByteArray();
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

            fileContent = "Mit freundlichen Grüßen<br>"
                          "<br>"
                          "<b>" + selectFileQuery.value(0).toString() + " " + selectFileQuery.value(1).toString() + "<br>" +
                          selectFileQuery.value(2).toString() + "<br>"
                          "<br>"
                          "<img alt='Green Lion Racing' src='data:image/png;base64,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'/></b><br>" +
                          "<br>"
                          "Bergische Universität Wuppertal<br>"
                          "Raum W.08.40<br>"
                          "Gaußstraße 20, 42119 Wuppertal, Deutschland<br>"
                          "<br>" +
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
