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
    void on_cb_table_currentIndexChanged();

    void on_pb_download_clicked();

    void on_cb_editMode_stateChanged();

    void on_pb_save_clicked();

    void selection_changed();

    void unsaved_changes();

private:
    Ui::Tables *ui;

    void closeEvent(QCloseEvent *event);

    QSqlTableModel *tableModel;

    QString selectedTable;

    int download_mode;

    QMessageBox::StandardButton unsaved_changes_notify();
};

#endif // SEETABLES_H
