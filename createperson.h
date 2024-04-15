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
    explicit createPerson(QWidget *parent = nullptr, bool editMode = false);
    ~createPerson();

private slots:
    void on_pb_okay_clicked();

    void on_cb_person_currentTextChanged();

private:
    Ui::createPerson *ui;

    bool editMode;
};

#endif // CREATEPERSON_H
