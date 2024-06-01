#include "databaseporting.h"
#include <QSqlQuery>
#include <QSqlError>


DatabasePorting::DatabasePorting() {

    // here are all changes to the database defined
    // and changes should be automatically applied to convert old database structures to new ones
    // check in step if end result of step is already applied


    // ******* begin of database porting *******

    QSqlQuery CompanyQquery("CREATE TABLE IF NOT EXISTS firmen (id INTEGER PRIMARY KEY, name TEXT, aktiv BOOL, seit TEXT, bis TEXT, Rang TEXT, Leistungstyp TEXT, Str TEXT, Hausnummer TEXT, Ort TEXT, PLZ INTEGER, Land TEXT, Infos TEXT)");
    QSqlQuery PersonQuery("CREATE TABLE IF NOT EXISTS personen (id INTEGER PRIMARY KEY, titel TEXT, vorname TEXT, nachname TEXT, telefon TEXT, fax TEXT, email TEXT, Position TEXT, du_sie TEXT, sprache TEXT, aktiv BOOL, FirmenID INTEGER, FOREIGN KEY (FirmenID) REFERENCES firmen(id))");
    QSqlQuery CommunicationQuery("CREATE TABLE IF NOT EXISTS kommunikationen (id INTEGER PRIMARY KEY, firma TEXT, ansprechpartner TEXT, wann TEXT, was TEXT, FirmenID INTEGER, PersonenID INTEGER, FOREIGN KEY (FirmenID) REFERENCES firmen(id), FOREIGN KEY(PersonenID) REFERENCES personen(id))");
    QSqlQuery CommunicationFileQuery("CREATE TABLE IF NOT EXISTS kommunikation_dateien (id INTEGER PRIMARY KEY, kommunikation_id INTEGER, datei BLOB, dateiname TEXT, FOREIGN KEY (kommunikation_id) REFERENCES kommunikationen(id))");
    QSqlQuery ActivityQquery("CREATE TABLE IF NOT EXISTS leistungen (id INTEGER PRIMARY KEY, firma TEXT, ansprechpartner TEXT, wann TEXT, wert TEXT, was TEXT, infos TEXT, FOREIGN KEY (firma) REFERENCES firmen(name))");
    QSqlQuery MemberQuery("CREATE TABLE IF NOT EXISTS mitglieder (id INTEGER PRIMARY KEY, vorname TEXT, nachname TEXT, position TEXT, matrikelnummer TEXT, email_glr TEXT, email_privat TEXT, telefon TEXT, anschrift TEXT, hemdgroesse TEXT, vdi_nummer TEXT, sprache TEXT, aktiv BOOL)");


    // ******* changes to database format after 2024-05-18, commit 8a0072a *******

    // rename table kommunikation_dateien to kommunikationen_dateien
    // rename column kommunikation_id to kommunikationen_id in kommunikationen_dateien
    // reorder columns from id, kommunikation_id, datei, dateiname to id, kommunikationen_id, dateiname, datei in kommunikationen_dateien
    bool current = checkTable("kommunikationen_dateien", "id INTEGER, kommunikationen_id INTEGER, dateiname TEXT, datei BLOB");
    if (!current) {
        QSqlQuery Query1("CREATE TABLE kommunikationen_dateien ("
                         "id INTEGER,"
                         "kommunikationen_id INTEGER,"
                         "dateiname TEXT,"
                         "datei BLOB,"
                         "PRIMARY KEY('id'),"
                         "FOREIGN KEY('kommunikationen_id') REFERENCES 'kommunikationen'('id'))");
        QSqlQuery Query2("INSERT INTO kommunikationen_dateien SELECT id, kommunikation_id, dateiname, datei FROM kommunikation_dateien");
        QSqlQuery Query3("DROP TABLE kommunikation_dateien");

        qDebug() << "1  " + Query1.lastError().text();
        qDebug() << "2  " + Query2.lastError().text();
        qDebug() << "3  " + Query3.lastError().text();
    }
    current = checkTable("kommunikation_dateien", "id INTEGER, kommunikation_id INTEGER, datei BLOB, dateiname TEXT");
    if (current) {
        QSqlQuery Query3("DROP TABLE kommunikation_dateien");
        //qDebug() << "3  " + Query3.lastError().text();
    }


    // remove column firma from kommunikationen
    // remove column ansprechpartner from kommunikationen
    // rename column FirmenID to firmen_id in kommunikationen
    // rename column PersonenID to personen_id in kommunikationen
    // reorder columns from id, wann, was, firmen_id, personen_id to id, firmen_id, personen_id, wann, was in kommunikationen
    current = checkTable("kommunikationen", "id INTEGER, firmen_id INTEGER, personen_id INTEGER, wann TEXT, was TEXT");
    if (!current) {
        QSqlQuery Query4("CREATE TABLE kommunikationen_temp ("
                         "id INTEGER,"
                         "firmen_id INTEGER,"
                         "personen_id INTEGER,"
                         "wann TEXT,"
                         "was TEXT,"
                         "PRIMARY KEY('id'),"
                         "FOREIGN KEY('firmen_id') REFERENCES 'firmen'('id'),"
                         "FOREIGN KEY('personen_id') REFERENCES 'personen'('id'))");
        QSqlQuery Query5("INSERT INTO kommunikationen_temp SELECT id, FirmenID, PersonenID, wann, was FROM kommunikationen");

        QSqlQuery Query26("SELECT id, firma, ansprechpartner FROM kommunikationen");
        QSqlQuery Query27("SELECT id, vorname, nachname FROM personen");
        QSqlQuery Query28;

        while (Query26.next()) {
            Query27.exec();
            while (Query27.next()) {
                if (Query26.value(2) == Query27.value(1).toString() + " " + Query27.value(2).toString()) {
                    Query28.prepare("UPDATE kommunikationen_temp SET personen_id = :personen_id WHERE id = :id");
                    Query28.bindValue(":id", Query26.value(0));
                    Query28.bindValue(":personen_id", Query27.value(0));
                    Query28.exec();
                }
            }
        }

        QSqlQuery Query6("DROP TABLE kommunikationen");
        QSqlQuery Query7("ALTER TABLE kommunikationen_temp RENAME TO kommunikationen");

        qDebug() << "4  " + Query4.lastError().text();
        qDebug() << "5  " + Query5.lastError().text();
        qDebug() << "6  " + Query6.lastError().text();
        qDebug() << "7  " + Query7.lastError().text();
        qDebug() << "26  " + Query26.lastError().text();
        qDebug() << "27  " + Query27.lastError().text();
        qDebug() << "28  " + Query28.lastError().text();
    }


    // remove column firma from personen
    // remove column fax from personen
    // rename column FirmenID to firmen_id in personen
    // rename column Position to position in personen
    // reorder columns from id, titel, vorname, nachname, telefon, email, position, du_sie, sprache, aktiv, firmen_id
    //                   to id, firmen_id, titel, vorname, nachname, position, telefon, email, du_sie, sprache, aktiv in personen
    current = checkTable("personen", "id INTEGER, firmen_id INTEGER, titel TEXT, vorname TEXT, nachname TEXT, position TEXT, telefon TEXT, email TEXT, du_sie TEXT, sprache TEXT, aktiv BOOLEAN");
    if (!current) {
        QSqlQuery Query8("CREATE TABLE personen_temp ("
                         "id INTEGER,"
                         "firmen_id INTEGER,"
                         "titel TEXT,"
                         "vorname TEXT,"
                         "nachname TEXT,"
                         "position TEXT,"
                         "telefon TEXT,"
                         "email TEXT,"
                         "du_sie TEXT,"
                         "sprache TEXT,"
                         "aktiv BOOLEAN,"
                         "PRIMARY KEY('id'),"
                         "FOREIGN KEY('firmen_id') REFERENCES 'firmen'('id'))");
        QSqlQuery Query9("INSERT INTO personen_temp SELECT id, FirmenID, titel, vorname, nachname, Position, telefon, email, du_sie, sprache, aktiv FROM personen");
        QSqlQuery Query10("DROP TABLE personen");
        QSqlQuery Query11("ALTER TABLE personen_temp RENAME TO personen");

        qDebug() << "8  " + Query8.lastError().text();
        qDebug() << "9  " + Query9.lastError().text();
        qDebug() << "10 " + Query10.lastError().text();
        qDebug() << "11 " + Query11.lastError().text();
    }


    // change column firma (with company names) to firmen_id (with company ids) in leistungen
    // change column anprechpartner (with person names) to personen_id (with person ids) with foreign key in leistungen
    // reorder columns  from id, firmen_id, personen_id, wann, wert, was, infos to id, firmen_id, personen_id, wann, was, wert, infos in leistungen
    current = checkTable("leistungen", "id INTEGER, firmen_id INTEGER, personen_id INTEGER, wann TEXT, was TEXT, wert TEXT, infos TEXT");
    if (!current) {
        QSqlQuery Query12("CREATE TABLE leistungen_temp ("
                          "id INTEGER,"
                          "firmen_id INTEGER,"
                          "personen_id INTEGER,"
                          "wann TEXT,"
                          "was TEXT,"
                          "wert TEXT,"
                          "infos TEXT,"
                          "PRIMARY KEY('id'),"
                          "FOREIGN KEY('firmen_id') REFERENCES 'firmen'('id'),"
                          "FOREIGN KEY('personen_id') REFERENCES 'personen'('id'))");
        QSqlQuery Query13("INSERT INTO leistungen_temp SELECT id, firma, ansprechpartner, wann, was, wert, infos FROM leistungen");

        QSqlQuery Query14("SELECT id, firma, ansprechpartner FROM leistungen");
        QSqlQuery Query15("SELECT id, name FROM firmen");
        QSqlQuery Query16("SELECT id, vorname, nachname FROM personen");
        QSqlQuery Query17;

        while (Query14.next()) {
            Query15.exec();
            while (Query15.next()) {
                if (Query14.value(1) == Query15.value(1)) {
                    Query17.prepare("UPDATE leistungen_temp SET firmen_id = :firmen_id WHERE id = :id");
                    Query17.bindValue(":id", Query14.value(0));
                    Query17.bindValue(":firmen_id", Query15.value(0));
                    Query17.exec();
                }
            }
            Query16.exec();
            while (Query16.next()) {
                if (Query14.value(2) == Query16.value(1).toString() + " " + Query16.value(2).toString()) {
                    Query17.prepare("UPDATE leistungen_temp SET personen_id = :personen_id WHERE id = :id");
                    Query17.bindValue(":id", Query14.value(0));
                    Query17.bindValue(":personen_id", Query16.value(0));
                    Query17.exec();
                }
            }
        }

        QSqlQuery Query18("DROP TABLE leistungen");
        QSqlQuery Query19("ALTER TABLE leistungen_temp RENAME TO leistungen");

        qDebug() << "12 " + Query12.lastError().text();
        qDebug() << "13 " + Query13.lastError().text();
        qDebug() << "14 " + Query14.lastError().text();
        qDebug() << "15 " + Query15.lastError().text();
        qDebug() << "16 " + Query16.lastError().text();
        qDebug() << "17 " + Query17.lastError().text();
        qDebug() << "18 " + Query18.lastError().text();
        qDebug() << "19 " + Query19.lastError().text();
    }


    // remove columns Str, Hausnummer, Ort, PLZ, Land and merge in anschrift in firmen
    // rename column Rang to rang in firmen
    // rename column Leistungstyp to leistungstyp in firmen
    // rename column Infos to infos in firmen
    // reorder columns from id, name, aktiv, seit, bis, rang, leistungstyp, anschrift, infos to id, name, seit, bis, rang, leistungstyp, infos, anschrift, aktiv in firmen
    current = checkTable("firmen", "id INTEGER, name TEXT, seit TEXT, bis TEXT, rang TEXT, leistungstyp TEXT, infos TEXT, anschrift TEXT, aktiv BOOLEAN");
    if (!current) {
        QSqlQuery Query20("CREATE TABLE firmen_temp ("
                          "id INTEGER,"
                          "name TEXT,"
                          "seit TEXT,"
                          "bis TEXT,"
                          "rang TEXT,"
                          "leistungstyp TEXT,"
                          "infos TEXT,"
                          "anschrift TEXT,"
                          "aktiv BOOLEAN,"
                          "PRIMARY KEY('id'))");
        QSqlQuery Query21("INSERT INTO firmen_temp SELECT id, name, seit, bis, Rang, Leistungstyp, Infos, Land, aktiv FROM firmen");

        QSqlQuery Query22("SELECT id, Str, Hausnummer, Ort, PLZ, Land FROM firmen");
        QSqlQuery Query23;

        while (Query22.next()) {
            Query23.prepare("UPDATE firmen_temp SET anschrift = :anschrift WHERE id = :id");
            Query23.bindValue(":id", Query22.value(0));
            Query23.bindValue(":anschrift", Query22.value(5).toString()+ ", " + Query22.value(3).toString() + ", " + Query22.value(4).toString()+ ", " + Query22.value(1).toString() + " " + Query22.value(2).toString());
            Query23.exec();
        }

        QSqlQuery Query24("DROP TABLE firmen");
        QSqlQuery Query25("ALTER TABLE firmen_temp RENAME TO firmen");

        qDebug() << "20 " + Query20.lastError().text();
        qDebug() << "21 " + Query21.lastError().text();
        qDebug() << "22 " + Query22.lastError().text();
        qDebug() << "23 " + Query23.lastError().text();
        qDebug() << "24 " + Query24.lastError().text();
        qDebug() << "25 " + Query25.lastError().text();
    }

    // ******* changes to database format after , commit  *******
}

bool DatabasePorting::checkTable(QString tableName, QString tableStructure) {
    QSqlQuery Query0;
    Query0.prepare("PRAGMA table_info(" + tableName + ")");
    Query0.exec();
    QString buildTableStructure = "";
    while (Query0.next()) {
        if (buildTableStructure != "") {
            buildTableStructure += ", ";
        }
        buildTableStructure += Query0.value(1).toString() + " " + Query0.value(2).toString();
    }
    return buildTableStructure == tableStructure;
}
