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
    void on_tv_table_clicked(const QModelIndex &index);

    void on_cb_table_currentTextChanged();

    void on_cb_filter_currentTextChanged();

    void on_cb_filter_gold_stateChanged();

    void on_cb_filter_silver_stateChanged();

    void on_cb_filter_bronze_stateChanged();

    void on_cb_filter_supporter_stateChanged();

    void update_cb_filter();

    void on_pb_download_clicked();

    void on_pb_download_all_clicked();

    void on_cb_editMode_stateChanged();

    void on_pb_save_clicked();

    void unsaved_changes();

    // void closeEvent();

private:
    Ui::displayTables *ui;

    QSqlTableModel *tableModel;

    int id;

    QString selectedTable;

    int download_mode;

    QString getCompanyId();
};

#endif // SEETABLES_H
