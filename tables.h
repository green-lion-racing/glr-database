#ifndef SEETABLES_H
#define SEETABLES_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class Tables;
}

class Tables : public QMainWindow
{
    Q_OBJECT

public:

    explicit Tables(QWidget *parent = nullptr, bool editMode = false);

    ~Tables();

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

private:
    Ui::Tables *ui;

    void closeEvent(QCloseEvent *event);

    QSqlTableModel *tableModel;

    int id;

    QString selectedTable;

    int download_mode;

    QString getCompanyId();

    QMessageBox::StandardButton unsaved_changes_notify();
};

#endif // SEETABLES_H
