#ifndef MEMBER_H
#define MEMBER_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class Member;
}

class Member : public QDialog
{
    Q_OBJECT

public:
    explicit Member(QWidget *parent = nullptr, bool editMode = false);
    ~Member();

private slots:
    void on_pb_okay_clicked();

    void on_cb_member_currentTextChanged();

private:
    Ui::Member *ui;

    bool editMode;
};

#endif // MEMBER_H
