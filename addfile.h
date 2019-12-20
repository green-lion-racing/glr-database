#ifndef ADDFILE_H
#define ADDFILE_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class addFile;
}

class addFile : public QDialog
{
    Q_OBJECT

public:
    explicit addFile(QWidget *parent = nullptr);
    ~addFile();

private slots:
    void on_pb_selectFile_clicked();

    void on_buttonBox_accepted();

    void on_pb_next_clicked();

private:
    Ui::addFile *ui;

    void saveFileToDatabase();
};

#endif // ADDFILE_H
