#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    QFile file(":stylesheet/stylesheet_login.qss");
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
// check on edit/insert if values valid/not null, unsaved changes
// add sql exception catch
// add password/cypher mode, changing, adding, removing
// Use QStyle instead of Qt Style Sheets https://www.kdab.com/say-no-to-qt-style-sheets/
