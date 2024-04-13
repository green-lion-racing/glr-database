#ifndef CREATECOMPANY_H
#define CREATECOMPANY_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class createCompany;
}

class createCompany : public QDialog
{
    Q_OBJECT

public:
    explicit createCompany(QWidget *parent = nullptr, bool editMode = false);
    ~createCompany();

private slots:
    void on_pb_okay_clicked();

    void on_cb_company_currentTextChanged();

private:
    Ui::createCompany *ui;

    bool editMode;
};

#endif // CREATECOMPANY_H
