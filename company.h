#ifndef COMPANY_H
#define COMPANY_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class Company;
}

class Company : public QDialog
{
    Q_OBJECT

public:
    explicit Company(QWidget *parent = nullptr, bool editMode = false);
    ~Company();

private slots:
    void on_pb_okay_clicked();

    void on_cb_company_currentTextChanged();

private:
    Ui::Company *ui;

    bool editMode;
};

#endif // COMPANY_H
