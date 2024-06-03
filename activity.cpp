#include "activity.h"
#include "ui_activity.h"
#include "error.h"

Activity::Activity(QWidget *parent, bool editMode):
    QDialog(parent),
    ui(new Ui::Activity)
{
    ui->setupUi(this);

    Activity::editMode = editMode;

    if (editMode) {
        QWidget::setWindowTitle("GLR Datenbank - Leistung bearbeiten");
        ui->l_dialogTitle->setText("GLR Datenbank - Leistung bearbeiten");

        QSqlQuery selectActivity;
        selectActivity.prepare("SELECT leistungen.id, firmen.name, personen.vorname, personen.nachname, wann FROM leistungen JOIN firmen ON leistungen.firmen_id = firmen.id JOIN personen ON leistungen.personen_id = personen.id");
        selectActivity.exec();

        while(selectActivity.next()) {
            ui->cb_activity->addItem(selectActivity.value(1).toString() + " - " +
                                     selectActivity.value(2).toString() + " " + selectActivity.value(3).toString() + " - " +
                                     selectActivity.value(4).toString(),
                                     selectActivity.value(0).toInt());
        }

        if (ui->cb_activity->count() < 1) {
            ui->cb_activity->setDisabled(true);
        }

        ui->cb_company->setDisabled(true);
        ui->cb_person->setDisabled(true);
        ui->cw_calender->setDisabled(true);
        ui->le_when->setDisabled(true);
        ui->le_what->setDisabled(true);
        ui->le_value->setDisabled(true);
        ui->te_info->setDisabled(true);
        ui->pb_okay->setDisabled(true);

    } else {
        QWidget::setWindowTitle("GLR Datenbank - Leistung hinzufügen");
        ui->l_dialogTitle->setText("GLR Datenbank - Leistung hinzufügen");
        ui->cb_activity->setVisible(false);
        ui->label_7->setVisible(false);
        ui->cb_person->setDisabled(true);

        set_cb_company();
    }

    // Do not display week numbers
    ui->cw_calender->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

    // print initially selected date (today)
    ui->le_when->setText(ui->cw_calender->selectedDate().toString("yyyy-MM-dd"));
}

Activity::~Activity()
{
    delete ui;
}

void Activity::on_cb_activity_currentIndexChanged()
{
    QSqlQuery selectActivity;
    selectActivity.prepare("SELECT id, firmen_id, personen_id, wann, was, wert, infos FROM leistungen WHERE id = :activityID");
    selectActivity.bindValue(":activityID", ui->cb_activity->currentData().toInt());
    selectActivity.exec();
    selectActivity.next();

    ui->cb_company->setDisabled(false);
    ui->cb_person->setDisabled(false);
    ui->cw_calender->setDisabled(false);
    ui->le_when->setDisabled(false);
    ui->le_what->setDisabled(false);
    ui->le_value->setDisabled(false);
    ui->te_info->setDisabled(false);
    ui->pb_okay->setDisabled(false);

    set_cb_company(selectActivity.value(1).toInt());
    set_cb_person(selectActivity.value(2).toInt());
    ui->le_when->setText(selectActivity.value(3).toString());
    ui->cw_calender->setSelectedDate(selectActivity.value(3).toDate());
    ui->le_what->setText(selectActivity.value(4).toString());
    ui->le_value->setText(selectActivity.value(5).toString());
    ui->te_info->setText(selectActivity.value(6).toString());
}

void Activity::on_cb_company_currentIndexChanged()
{
    set_cb_person();
}

void Activity::on_cw_calender_selectionChanged()
{
    ui->le_when->setText(ui->cw_calender->selectedDate().toString("yyyy-MM-dd"));
}

void Activity::on_pb_okay_clicked()
{
    int activityID = ui->cb_activity->currentData().toInt();
    int companyID = ui->cb_company->currentData().toInt();
    int personID = ui->cb_person->currentData().toInt();
    QString when = ui->le_when->text();
    QString what = ui->le_what->text();
    QString value = ui->le_value->text();
    QString info = ui->te_info->toPlainText();

    QSqlQuery insertActivityQuery;
    if (editMode) {
        insertActivityQuery.prepare("UPDATE leistungen SET firmen_id = :companyID, personen_id = :personID, wann = :when, was = :what, wert = :value, infos = :info WHERE id = :activityID");
        insertActivityQuery.bindValue(":activityID", activityID);
    } else {
        insertActivityQuery.prepare("INSERT INTO leistungen(firmen_id, personen_id, wann, was, wert, infos) VALUES (:companyID, :personID, :when, :what, :value, :info)");
    }

    insertActivityQuery.bindValue(":companyID", companyID);
    insertActivityQuery.bindValue(":personID", personID);
    insertActivityQuery.bindValue(":when", when);
    insertActivityQuery.bindValue(":what", what);
    insertActivityQuery.bindValue(":value", value);
    insertActivityQuery.bindValue(":info", info);

    insertActivityQuery.exec();

    if (insertActivityQuery.next()) {
        Error errorWindow;
        errorWindow.setText("QSQLITE error: " + insertActivityQuery.lastError().text() + ",\nQSQLITE error code: " + insertActivityQuery.lastError().nativeErrorCode());
        errorWindow.setModal(true);
        errorWindow.exec();
    } else {
        this->accept();
    }
}

void Activity::set_cb_company(int id) {
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

void Activity::set_cb_person(int id) {
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
