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

    selectedTable = ui->cb_table->currentText();
    tableModel = new QSqlTableModel();
    tableModel->setTable(selectedTable);

    // hiding files because it creates massive lags
    // there is probably a better solution, creating a new view and only use what needed
    if (selectedTable == "kommunikationen_dateien") {
        ui->tv_table->setColumnHidden(3, true);
    } else {
        ui->tv_table->setColumnHidden(3, false);
    }

    tableModel->select();
    tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tv_table->setModel(tableModel);
}

void Tables::on_cb_editMode_stateChanged() {
    if (ui->cb_editMode->isChecked()) {
        QWidget::setWindowTitle("GLR Datenbank - Einträge bearbeiten");
        ui->l_dialogTitle->setText("Tabellen bearbeiten");
        ui->tv_table->setEditTriggers(QAbstractItemView::AllEditTriggers);
        ui->pb_save->setVisible(true);
        ui->pb_save->setEnabled(false);
        connect(ui->tv_table->model(), SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(unsaved_changes()));
    } else {
        QWidget::setWindowTitle("GLR Datenbank - Einträge ansehen");
        ui->l_dialogTitle->setText("Tabellen ansehen");
        ui->tv_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->pb_save->setVisible(false);
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
