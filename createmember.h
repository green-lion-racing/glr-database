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
    explicit createMember(QWidget *parent = nullptr, bool editMode = false);
    ~createMember();

private slots:
    void on_pb_okay_clicked();

    void on_cb_member_currentTextChanged();

private:
    Ui::createMember *ui;

    bool editMode;
};

#endif // CREATEMEMBER_H
