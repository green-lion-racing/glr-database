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
// add password/cypher mode, changing, adding, removing
// adjust filtering in table view and table edit
// combine/create creating and modifying of objects
// add nice way to log changes in sponsors/members/persons
// dont load files in full size in table kommunikation_dateien, programm hangs
// Use QStyle instead of Qt Style Sheets https://www.kdab.com/say-no-to-qt-style-sheets/
// how to nice dropdown while using custom qss Qt Style Sheet problem?
