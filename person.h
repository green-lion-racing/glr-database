#ifndef PERSON_H
#define PERSON_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class Person;
}

class Person : public QDialog
{
    Q_OBJECT

public:
    explicit Person(QWidget *parent = nullptr, bool editMode = false);
    ~Person();

private slots:
    void on_pb_okay_clicked();

    void on_cb_person_currentIndexChanged();

private:
    Ui::Person *ui;

    bool editMode;
};

#endif // PERSON_H
