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
                          selectFileQuery.value(2).toString() + "</b><br>"
                          "<br>"
                          "<b><img alt='Green Lion Racing' src='data:image/png;base64,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'/></b><br>" +
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
