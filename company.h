#ifndef COMPANY_H
#define COMPANY_H

#include <QDialog>
#include <QListWidgetItem>
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

    void on_cb_company_currentIndexChanged();

    void on_tb_add_clicked();

    void on_tb_remove_clicked();

    void selectionChanged();

private:
    Ui::Company *ui;

    bool editMode;

    QListWidgetItem *selected = NULL;
};

#endif // COMPANY_H
