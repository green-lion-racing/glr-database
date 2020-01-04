#include "addfile.h"
#include "ui_addfile.h"
#include <QFileDialog>

static QString fileName;
static QFile file;

addFile::addFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addFile)
{
    ui->setupUi(this);
}

addFile::~addFile()
{
    delete ui;
}

void addFile::on_pb_selectFile_clicked()
{
    //QString fileName = QFileDialog::getOpenFileName(this, "Datei öffnen", "C://");
    fileName = QFileDialog::getOpenFileName(this, "Datei öffnen", "C://");
    //qDebug() << fileName;
    //QFile file(fileName);
    file.setFileName(fileName);
    //file.setFileName(fileName);
    if(file.open(QIODevice::ReadOnly))
       qDebug() << "erfolgreich";

    ui->l_fileName->setText(fileName);
}

void addFile::saveFileToDatabase() {
    //aktuelles Datum
    //time_t now = time(0);
    //tm *ltm = localtime(&now);
    //QString date = QString::number(1900 + ltm->tm_year) + "-" + QString::number(1 + ltm->tm_mon) + "-" + QString::number(ltm->tm_mday);

    QSqlQuery selectId, selectDate;
    selectId.prepare("SELECT id FROM kommunikationen ORDER BY id DESC LIMIT 1");
    selectId.exec();
    int communicationId = 0;
    while(selectId.next())
        communicationId = selectId.value(0).toInt();

    selectDate.prepare("SELECT wann FROM kommunikationen WHERE id = :communicationId");
    selectDate.bindValue(":communicationId", communicationId);
    selectDate.exec();
    QString date;
    while(selectDate.next())
        date = selectDate.value(0).toString();

    QByteArray fileContent = file.readAll();

    QFileInfo onlyFileName(fileName);
    QString fileNameWithoutPath = onlyFileName.fileName();  //Dateiname ohne Pfad

    QSqlQuery createCommunicationFileQuery("CREATE TABLE IF NOT EXISTS kommunikation_dateien (id INTEGER PRIMARY KEY, kommunikation_id INTEGER, datei BLOB, dateiname TEXT, FOREIGN KEY (kommunikation_id) REFERENCES kommunikationen(id))");
    QSqlQuery insertCommunicationFileQuery;
    insertCommunicationFileQuery.prepare("INSERT INTO kommunikation_dateien(kommunikation_id, datei, dateiname) VALUES (:communicationId, :fileContent, :fileNameWithoutPath)");
    insertCommunicationFileQuery.bindValue(":communicationId", communicationId);
    insertCommunicationFileQuery.bindValue(":fileContent", fileContent);
    insertCommunicationFileQuery.bindValue(":fileNameWithoutPath", date + "-" + fileNameWithoutPath);
    insertCommunicationFileQuery.exec();

    if (insertCommunicationFileQuery.next())
    {
    } else {
        qDebug() << "SqLite error:" << insertCommunicationFileQuery.lastError().text() << ", SqLite error code:" << insertCommunicationFileQuery.lastError().number();
    }
}

void addFile::on_buttonBox_accepted()
{
    saveFileToDatabase();
}

void addFile::on_pb_next_clicked()
{
    saveFileToDatabase();
    ui->l_fileName->clear();
}
