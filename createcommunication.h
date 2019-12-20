#ifndef CREATECOMMUNICATION_H
#define CREATECOMMUNICATION_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class createCommunication;
}

class createCommunication : public QDialog
{
    Q_OBJECT

public:
    explicit createCommunication(QWidget *parent = nullptr);
    ~createCommunication();

private slots:
    void on_buttonBox_accepted();

    void on_pb_file_clicked();

    void on_cb_company_currentTextChanged(const QString &arg1);

private:
    Ui::createCommunication *ui;
};

#endif // CREATECOMMUNICATION_H
