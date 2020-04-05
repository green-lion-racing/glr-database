#ifndef CREATEPERSON_H
#define CREATEPERSON_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class createPerson;
}

class createPerson : public QDialog
{
    Q_OBJECT

public:
    explicit createPerson(QWidget *parent = nullptr);
    ~createPerson();

private slots:
    void on_pb_okay_clicked();

    void on_pb_close_clicked();

private:
    Ui::createPerson *ui;
};

#endif // CREATEPERSON_H
