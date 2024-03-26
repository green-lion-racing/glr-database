#ifndef MODIFYTABLES_H
#define MODIFYTABLES_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class modifyTables;
}

class modifyTables : public QMainWindow
{
    Q_OBJECT

public:
    explicit modifyTables(QWidget *parent = nullptr);
    ~modifyTables();

private slots:
    void on_pb_save_clicked();

    void on_cb_table_currentTextChanged(const QString &arg1);

    void on_cb_gold_stateChanged(int arg1);

    void on_cb_silver_stateChanged(int arg1);

    void on_cb_bronze_stateChanged(int arg1);

    void on_cb_supporter_stateChanged(int arg1);

    void on_cb_companyName_currentTextChanged(const QString &arg1);

private:
    Ui::modifyTables *ui;
    QSqlTableModel *modal;

    void checkBoxGold(QString otherCheckedCheckBoxes = "nothing");
    void checkBoxSilver(QString otherCheckedCheckBoxes = "nothing");
    void checkBoxBronze(QString otherCheckedCheckBoxes = "nothing");
    void checkBoxSupporter(QString otherCheckedCheckBoxes = "nothing");
    QString getCompanyId();
};

#endif // MODIFYTABLES_H
