#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    QFile file(":stylesheet/stylesheet.qss");
    file.open(QFile::ReadOnly);
    QString stylesheet = QLatin1String(file.readAll());
    file.close();

    application.setStyleSheet(stylesheet);
    application.setQuitOnLastWindowClosed(false);

    MainWindow window;
    window.show();
    window.setAttribute(Qt::WA_QuitOnClose, false);
    return application.exec();
}

// TODOs
// check on edit/insert if values valid/not null
// add sql exception catch
// add nice way to log changes in sponsors/members
// add password/cypher mode, changing, adding, removing
// remove filtering in table view?
// Use QStyle instead of Qt Style Sheets https://www.kdab.com/say-no-to-qt-style-sheets/
