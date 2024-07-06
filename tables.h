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

    void on_cb_editMode_stateChanged();

    void on_pb_save_clicked();

    void unsaved_changes();

private:
    Ui::Tables *ui;

    void closeEvent(QCloseEvent *event);

    QString selectedTable;

    QMessageBox::StandardButton unsaved_changes_notify();
};

#endif // SEETABLES_H
