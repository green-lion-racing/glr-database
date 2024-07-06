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
    void on_cb_communication_currentIndexChanged();

    void on_cb_company_currentIndexChanged();

    void on_cw_calender_selectionChanged();

    void on_pb_okay_clicked();

    void on_tb_add_clicked();

    void on_tb_remove_clicked();

    void on_tb_download_clicked();

    void selectionChanged();

private:
    Ui::Communication *ui;

    bool editMode;

    void set_cb_company(int id = -1);

    void set_cb_person(int id = -1);
};

#endif // COMMUNICATION_H
