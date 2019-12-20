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
    void on_pB_createCompany_clicked();

    void on_pb_createPerson_clicked();

    void on_pB_createActivity_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pb_saveFile_clicked();

    void on_pb_modifyCompany_clicked();

    void on_pb_modifyPerson_clicked();

    void on_pb_modifyActivity_clicked();

    void on_pb_modifyCommunication_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
