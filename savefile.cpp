#include "savefile.h"
#include "ui_savefile.h"
#include <QDir>
#include <QFileDialog>

saveFile::saveFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::saveFile)
{
    ui->setupUi(this);
}

saveFile::~saveFile()
{
    delete ui;
}

void saveFile::on_pb_save_clicked()
{
    QString name = "C:\\Users\\Tobias\\Downloads\\text.pdf";
    QByteArray fileContent;

    QSqlQuery selectFileQuery("SELECT datei, dateiname FROM kommunikation_dateien WHERE id = 1");
    while(selectFileQuery.next()) {
        fileContent = selectFileQuery.value(0).toByteArray();
        name = selectFileQuery.value(1).toString();
    }

    QString filename =  QFileDialog::getSaveFileName(this, tr("Save Document"), name);
    QFile file(filename);
    file.open(QIODevice::ReadWrite);

    file.write(fileContent);

    //selectFileQuery.exec();
    //modal->setQuery(selectQuery);
    //ui->tv_request->setModel(modal);

}
