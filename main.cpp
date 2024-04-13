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
// use ids not names to reference between tables
// combine/create creating and modifying of objects
// add password/cypher mode, changing, adding, removing
// adjust filtering in table view
// add nice way to log changes in sponsors/members/persons
// Use QStyle instead of Qt Style Sheets https://www.kdab.com/say-no-to-qt-style-sheets/
