#ifndef CREATEACTIVITY_H
#define CREATEACTIVITY_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class createActivity;
}

class createActivity : public QDialog
{
    Q_OBJECT

public:
    explicit createActivity(QWidget *parent = nullptr, bool editMode = false);
    ~createActivity();

private slots:

    void on_cb_activity_currentTextChanged();

    void on_cb_company_currentTextChanged();

    void on_cw_calender_selectionChanged();

    void on_pb_okay_clicked();

private:
    Ui::createActivity *ui;

    bool editMode;

    QString getCompanyId();

    void set_cb_company(QString company = "");

    void set_cb_person(QString person = "");
};

#endif // CREATEACTIVITY_H
