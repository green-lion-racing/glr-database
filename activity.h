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

    void on_cb_activity_currentIndexChanged();

    void on_cb_company_currentIndexChanged();

    void on_cw_calender_selectionChanged();

    void on_pb_okay_clicked();

private:
    Ui::Activity *ui;

    bool editMode;

    void set_cb_company(int id = -1);

    void set_cb_person(int id = -1);
};

#endif // ACTIVITY_H
