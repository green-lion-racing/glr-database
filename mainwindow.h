#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QLabel>
#include "tables.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setFilePath(const QString &newFilePath);

private slots:

    void on_actionOpenDatabase_triggered();

    void on_actionCloseDatabase_triggered();

    void on_actionPasswordAdd_triggered();

    void on_actionPasswordRemove_triggered();

    void on_actionPasswordChange_triggered();

    void on_actionAbout_triggered();

    void on_tb_createMember_clicked();

    void on_tb_modifyMember_clicked();

    void on_tb_createPerson_clicked();

    void on_tb_modifyPerson_clicked();

    void on_tb_createCompany_clicked();

    void on_tb_modifyCompany_clicked();

    void on_tb_createCommunication_clicked();

    void on_tb_modifyCommunication_clicked();

    void on_tb_createActivity_clicked();

    void on_tb_modifyActivity_clicked();

    void on_tb_modifyTables_clicked();

    void on_tb_displayTables_clicked();

    void on_getSizeTest_clicked();

private:
    Ui::MainWindow *ui;

    Tables *tablesWindow = NULL;

    void keyPressEvent(QKeyEvent * event);

    void closeEvent(QCloseEvent * event);

    void openDatabase(bool first_try = false);

    QString currentFile;

    QLabel *status_label = new QLabel(this);

    QSqlDatabase dbconn = QSqlDatabase::addDatabase("QSQLITE");
};
#endif // MAINWINDOW_H
