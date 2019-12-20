#ifndef CREATEACTIVITY_H
#define CREATEACTIVITY_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class createActivity;
}

class createActivity : public QDialog
{
    Q_OBJECT

public:
    explicit createActivity(QWidget *parent = nullptr);
    ~createActivity();

private slots:
    void on_buttonBox_accepted();

    void on_cb_company_currentTextChanged(const QString &arg1);

private:
    Ui::createActivity *ui;
};

#endif // CREATEACTIVITY_H
