#ifndef CREATECOMMUNICATION_H
#define CREATECOMMUNICATION_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class createCommunication;
}

class createCommunication : public QDialog
{
    Q_OBJECT

public:
    explicit createCommunication(QWidget *parent = nullptr, bool editMode = false);
    ~createCommunication();

private slots:
    void on_cb_communication_currentTextChanged();

    void on_cb_company_currentTextChanged();

    void on_cw_calender_selectionChanged();

    void on_pb_okay_clicked();

private:
    Ui::createCommunication *ui;

    bool editMode;

    QString getCompanyId();

    void set_cb_company(QString company = "");

    void set_cb_person(QString person = "");
};

#endif // CREATECOMMUNICATION_H
