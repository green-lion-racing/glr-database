#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class saveFile;
}

class saveFile : public QDialog
{
    Q_OBJECT

public:
    explicit saveFile(QWidget *parent = nullptr);
    ~saveFile();

private slots:
    void on_pb_save_clicked();

private:
    Ui::saveFile *ui;
};

#endif // SAVEFILE_H
