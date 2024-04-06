#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    QFile file(":stylesheet/stylesheet.qss");
    file.open(QFile::ReadOnly);
    QString stylesheet = QLatin1String(file.readAll());

    application.setStyleSheet(stylesheet);
    application.setQuitOnLastWindowClosed(false);

    MainWindow window;
    window.show();
    window.setAttribute(Qt::WA_QuitOnClose, false);
    return application.exec();
}

// TODOs
// dont load files in full size in table kommunikation_dateien, programm hangs
// combine/create creating and modifying of objects
// adjust filtering in table view
// add password/cypher mode, changing, adding, removing
// add nice way to log changes in sponsors/members/persons
// Use QStyle instead of Qt Style Sheets https://www.kdab.com/say-no-to-qt-style-sheets/
// how to have nice dropdown while using custom qss Qt Style Sheet problem?
