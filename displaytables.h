#ifndef SEETABLES_H
#define SEETABLES_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class displayTables;
}

class displayTables : public QMainWindow
{
    Q_OBJECT

public:
    explicit displayTables(QWidget *parent = nullptr);
    ~displayTables();

private slots:
    void on_cb_table_currentTextChanged(const QString &arg1);

    void on_pb_download_clicked();

    void on_cb_gold_stateChanged(int arg1);

    void on_cb_silver_stateChanged(int arg1);

    void on_cb_bronze_stateChanged(int arg1);

    void on_cb_companyName_currentTextChanged(const QString &arg1);

    void on_cb_supporter_stateChanged(int arg1);

    void on_tv_table_clicked(const QModelIndex &index);

    void on_pb_save_clicked();

    void on_pb_signature_clicked();

private:
    Ui::displayTables *ui;
    QSqlTableModel *modal;
    int id;
    QString selectedTable;

    void checkBoxGold(QString otherCheckedCheckBoxes = "nothing");
    void checkBoxSilver(QString otherCheckedCheckBoxes = "nothing");
    void checkBoxBronze(QString otherCheckedCheckBoxes = "nothing");
    void checkBoxSupporter(QString otherCheckedCheckBoxes = "nothing");
    QString getCompanyId();
};

#endif // SEETABLES_H
