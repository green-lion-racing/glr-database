#ifndef CREATEMEMBER_H
#define CREATEMEMBER_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class createMember;
}

class createMember : public QDialog
{
    Q_OBJECT

public:
    explicit createMember(QWidget *parent = nullptr);
    ~createMember();

private slots:
    void on_pb_okay_clicked();

private:
    Ui::createMember *ui;
};

#endif // CREATEMEMBER_H
