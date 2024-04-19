#ifndef ERROR_H
#define ERROR_H

#include <QDialog>

namespace Ui {
class Error;
}

class Error : public QDialog
{
    Q_OBJECT

public:
    explicit Error(QWidget *parent = nullptr);
    void setText(QString error);
    ~Error();

private slots:
    void on_pb_okay_clicked();

private:
    Ui::Error *ui;
};

#endif // ERROR_H
