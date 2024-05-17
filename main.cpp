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
// use ids not names to reference between tables, tidy up database structure
// write port file from old db to new db
// add nice way to log changes in sponsors/members/persons
// add password/cypher mode, changing, adding, removing
// remove filtering in table view?
// Use QStyle instead of Qt Style Sheets https://www.kdab.com/say-no-to-qt-style-sheets/
