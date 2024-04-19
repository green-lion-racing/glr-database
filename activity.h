#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class Activity;
}

class Activity : public QDialog
{
    Q_OBJECT

public:
    explicit Activity(QWidget *parent = nullptr, bool editMode = false);
    ~Activity();

private slots:

    void on_cb_activity_currentTextChanged();

    void on_cb_company_currentTextChanged();

    void on_cw_calender_selectionChanged();

    void on_pb_okay_clicked();

private:
    Ui::Activity *ui;

    bool editMode;

    QString getCompanyId();

    void set_cb_company(QString company = "");

    void set_cb_person(QString person = "");
};

#endif // ACTIVITY_H
