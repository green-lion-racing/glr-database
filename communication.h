#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class Communication;
}

class Communication : public QDialog
{
    Q_OBJECT

public:
    explicit Communication(QWidget *parent = nullptr, bool editMode = false);
    ~Communication();

private slots:
    void on_cb_communication_currentTextChanged();

    void on_cb_company_currentTextChanged();

    void on_cw_calender_selectionChanged();

    void on_pb_okay_clicked();

private:
    Ui::Communication *ui;

    bool editMode;

    QString getCompanyId();

    void set_cb_company(QString company = "");

    void set_cb_person(QString person = "");
};

#endif // COMMUNICATION_H
