#ifndef MODIFYCOMPANY_H
#define MODIFYCOMPANY_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class modifyCompany;
}

class modifyCompany : public QDialog
{
    Q_OBJECT

public:
    explicit modifyCompany(QWidget *parent = nullptr);
    ~modifyCompany();

private slots:
    void on_buttonBox_accepted();

    void on_cb_table_currentTextChanged(const QString &arg1);

    void on_pb_download_clicked();

    void on_cb_companyName_currentTextChanged(const QString &arg1);

    void on_cb_rank_currentTextChanged(const QString &arg1);

    void on_cb_gold_stateChanged(int arg1);

    void on_cb_silver_stateChanged(int arg1);

    void on_cb_bronze_stateChanged(int arg1);

private:
    Ui::modifyCompany *ui;
    QSqlTableModel *modal;

    void checkBoxGold(QString otherCheckedCheckBoxes = "nothing");
    void checkBoxSilver(QString otherCheckedCheckBoxes = "nothing");
    void checkBoxBronze(QString otherCheckedCheckBoxes = "nothing");
};

#endif // MODIFYCOMPANY_H
