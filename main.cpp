#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    QFile file(":stylesheet/stylesheet.qss");
    file.open(QFile::ReadOnly);
    QString stylesheet = QLatin1String(file.readAll());

    qApp->setStyleSheet(stylesheet);

    MainWindow window;
    window.show();
    return application.exec();
}

// TODOs
// menubar disable currently not usable buttons
// add password/cypher mode, changing, adding, removing
// adjust filtering in table view and table edit
// how to get nice scrollbar and nice dropdown while using custom qss
// combine/create creating and modifying of objects
// add nice way to log changes in sponsors/members/persons
// add column shirt size, vdi number to member
