#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "mainwindow.h"

namespace Ui {
class logIn;
}

class logIn : public QMainWindow
{
    Q_OBJECT

public:
    explicit logIn(QWidget *parent = nullptr);
    ~logIn();

private slots:
    void on_icon_clicked();

private:
    Ui::logIn *ui;
    MainWindow mainWindow;
};

#endif // LOGIN_H
