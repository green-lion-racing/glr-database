#ifndef CREATECOMPANY_H
#define CREATECOMPANY_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class createCompany;
}

class createCompany : public QDialog
{
    Q_OBJECT

public:
    explicit createCompany(QWidget *parent = nullptr);
    ~createCompany();

private slots:
    void on_buttonBox_accepted();
private:
    Ui::createCompany *ui;
};

#endif // CREATECOMPANY_H
