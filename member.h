#ifndef MEMBER_H
#define MEMBER_H

#include <QDialog>
#include <QListWidgetItem>
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

    void on_cb_member_currentIndexChanged();

    void on_tb_add_clicked();

    void on_tb_remove_clicked();

    void selectionChanged();

private:
    Ui::Member *ui;

    bool editMode;

    QListWidgetItem *selected = NULL;
};

#endif // MEMBER_H
