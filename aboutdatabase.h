#ifndef ABOUTDATABASE_H
#define ABOUTDATABASE_H

#include <QDialog>

namespace Ui {
class aboutDatabase;
}

class aboutDatabase : public QDialog
{
    Q_OBJECT

public:
    explicit aboutDatabase(QWidget *parent = nullptr);
    ~aboutDatabase();

private:
    Ui::aboutDatabase *ui;
};

#endif // ABOUTDATABASE_H
