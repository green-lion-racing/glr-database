#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_icon_clicked();

    void on_pb_createCompany_clicked();

    void on_pb_createPerson_clicked();

    void on_pb_createActivity_clicked();

    void on_pb_createCommunication_clicked();

    void on_pb_saveFile_clicked();

    void on_pb_modifyTables_clicked();

    void on_pb_seeTables_clicked();

    void on_openDatabase_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
