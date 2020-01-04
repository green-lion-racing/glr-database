#ifndef SEETABLES_H
#define SEETABLES_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class seeTables;
}

class seeTables : public QDialog
{
    Q_OBJECT

public:
    explicit seeTables(QWidget *parent = nullptr);
    ~seeTables();

private slots:
    void on_cb_table_currentTextChanged(const QString &arg1);

    void on_pb_download_clicked();

    void on_cb_gold_stateChanged(int arg1);

    void on_cb_silver_stateChanged(int arg1);

    void on_cb_bronze_stateChanged(int arg1);

private:
    Ui::seeTables *ui;
    QSqlTableModel *modal;

    void checkBoxGold(QString otherCheckedCheckBoxes = "nothing");
    void checkBoxSilver(QString otherCheckedCheckBoxes = "nothing");
    void checkBoxBronze(QString otherCheckedCheckBoxes = "nothing");
};

#endif // SEETABLES_H
