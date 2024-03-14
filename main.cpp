#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    QFile file(":/stylesheets/stylesheet.qss");
    file.open(QFile::ReadOnly);
    QString stylesheet = QLatin1String(file.readAll());

    qApp->setStyleSheet(stylesheet);

    MainWindow window;
    window.show();
    return application.exec();
}
