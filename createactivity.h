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

    void on_cb_company_currentTextChanged(const QString &arg1);

    void on_cw_calender_selectionChanged();

    void on_pb_okay_clicked();

private:
    Ui::createActivity *ui;
    QString when;
    QString getCompanyId();
};

#endif // CREATEACTIVITY_H
