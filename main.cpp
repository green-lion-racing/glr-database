#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":/stylesheets/stylesheet.qss");
    file.open(QFile::ReadOnly);
    QString stylesheet = QLatin1String(file.readAll());

    qApp->setStyleSheet(stylesheet);

    MainWindow w;
    w.show();
    return a.exec();

    //logIn logInWindow;
    //logInWindow.show();
    //return  a.exec();
}
