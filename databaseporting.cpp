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

        QSqlQuery Query6("SELECT id, firma, ansprechpartner FROM kommunikationen");
        QSqlQuery Query7("SELECT id, vorname, nachname FROM personen");
        QSqlQuery Query8;

        while (Query6.next()) {
            Query7.exec();
            while (Query7.next()) {
                if (Query6.value(2) == Query7.value(1).toString() + " " + Query7.value(2).toString()) {
                    Query8.prepare("UPDATE kommunikationen_temp SET personen_id = :personen_id WHERE id = :id");
                    Query8.bindValue(":id", Query6.value(0));
                    Query8.bindValue(":personen_id", Query7.value(0));
                    Query8.exec();
                }
            }
        }

        QSqlQuery Query9("DROP TABLE kommunikationen");
        QSqlQuery Query10("ALTER TABLE kommunikationen_temp RENAME TO kommunikationen");

        qDebug() << "4  " + Query4.lastError().text();
        qDebug() << "5  " + Query5.lastError().text();
        qDebug() << "6  " + Query6.lastError().text();
        qDebug() << "7  " + Query7.lastError().text();
        qDebug() << "8  " + Query8.lastError().text();
        qDebug() << "9  " + Query9.lastError().text();
        qDebug() << "10  " + Query10.lastError().text();
    }


    // remove column firma from personen
    // remove column fax from personen
    // rename column FirmenID to firmen_id in personen
    // rename column Position to position in personen
    // reorder columns from id, titel, vorname, nachname, telefon, email, position, du_sie, sprache, aktiv, firmen_id
    //                   to id, firmen_id, titel, vorname, nachname, position, telefon, email, du_sie, sprache, aktiv in personen
    current = checkTable("personen", "id INTEGER, firmen_id INTEGER, titel TEXT, vorname TEXT, nachname TEXT, position TEXT, telefon TEXT, email TEXT, du_sie TEXT, sprache TEXT, aktiv BOOLEAN");
    if (!current) {
        QSqlQuery Query11("CREATE TABLE personen_temp ("
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
        QSqlQuery Query12("INSERT INTO personen_temp SELECT id, FirmenID, titel, vorname, nachname, Position, telefon, email, du_sie, sprache, aktiv FROM personen");
        QSqlQuery Query13("DROP TABLE personen");
        QSqlQuery Query14("ALTER TABLE personen_temp RENAME TO personen");

        qDebug() << "11  " + Query11.lastError().text();
        qDebug() << "12  " + Query12.lastError().text();
        qDebug() << "13 " + Query13.lastError().text();
        qDebug() << "14 " + Query14.lastError().text();
    }


    // change column firma (with company names) to firmen_id (with company ids) in leistungen
    // change column anprechpartner (with person names) to personen_id (with person ids) with foreign key in leistungen
    // reorder columns  from id, firmen_id, personen_id, wann, wert, was, infos to id, firmen_id, personen_id, wann, was, wert, infos in leistungen
    current = checkTable("leistungen", "id INTEGER, firmen_id INTEGER, personen_id INTEGER, wann TEXT, was TEXT, wert TEXT, infos TEXT");
    if (!current) {
        QSqlQuery Query15("CREATE TABLE leistungen_temp ("
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
        QSqlQuery Query16("INSERT INTO leistungen_temp SELECT id, firma, ansprechpartner, wann, was, wert, infos FROM leistungen");

        QSqlQuery Query17("SELECT id, firma, ansprechpartner FROM leistungen");
        QSqlQuery Query18("SELECT id, name FROM firmen");
        QSqlQuery Query19("SELECT id, vorname, nachname FROM personen");
        QSqlQuery Query20;

        while (Query17.next()) {
            Query18.exec();
            while (Query18.next()) {
                if (Query17.value(1) == Query18.value(1)) {
                    Query20.prepare("UPDATE leistungen_temp SET firmen_id = :firmen_id WHERE id = :id");
                    Query20.bindValue(":id", Query17.value(0));
                    Query20.bindValue(":firmen_id", Query18.value(0));
                    Query20.exec();
                }
            }
            Query19.exec();
            while (Query19.next()) {
                if (Query17.value(2) == Query19.value(1).toString() + " " + Query19.value(2).toString()) {
                    Query20.prepare("UPDATE leistungen_temp SET personen_id = :personen_id WHERE id = :id");
                    Query20.bindValue(":id", Query17.value(0));
                    Query20.bindValue(":personen_id", Query19.value(0));
                    Query20.exec();
                }
            }
        }

        QSqlQuery Query21("DROP TABLE leistungen");
        QSqlQuery Query22("ALTER TABLE leistungen_temp RENAME TO leistungen");

        qDebug() << "15 " + Query15.lastError().text();
        qDebug() << "16 " + Query16.lastError().text();
        qDebug() << "17 " + Query17.lastError().text();
        qDebug() << "18 " + Query18.lastError().text();
        qDebug() << "19 " + Query19.lastError().text();
        qDebug() << "20 " + Query20.lastError().text();
        qDebug() << "21 " + Query21.lastError().text();
        qDebug() << "22 " + Query22.lastError().text();
    }


    // remove columns Str, Hausnummer, Ort, PLZ, Land and merge in anschrift in firmen
    // rename column Rang to rang in firmen
    // rename column Leistungstyp to leistungstyp in firmen
    // rename column Infos to infos in firmen
    // reorder columns from id, name, aktiv, seit, bis, rang, leistungstyp, anschrift, infos to id, name, seit, bis, rang, leistungstyp, infos, anschrift, aktiv in firmen
    current = checkTable("firmen", "id INTEGER, name TEXT, seit TEXT, bis TEXT, rang TEXT, leistungstyp TEXT, infos TEXT, anschrift TEXT, aktiv BOOLEAN") ||
        checkTable("firmen", "id INTEGER, name TEXT, infos TEXT, anschrift TEXT, aktiv BOOLEAN");
    if (!current) {
        QSqlQuery Query23("CREATE TABLE firmen_temp ("
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
        QSqlQuery Query24("INSERT INTO firmen_temp SELECT id, name, seit, bis, Rang, Leistungstyp, Infos, Land, aktiv FROM firmen");

        QSqlQuery Query25("SELECT id, Str, Hausnummer, Ort, PLZ, Land FROM firmen");
        QSqlQuery Query26;

        while (Query25.next()) {
            Query26.prepare("UPDATE firmen_temp SET anschrift = :anschrift WHERE id = :id");
            Query26.bindValue(":id", Query25.value(0));
            Query26.bindValue(":anschrift", Query25.value(5).toString()+ ", " + Query25.value(3).toString() + ", " + Query25.value(4).toString()+ ", " + Query25.value(1).toString() + " " + Query25.value(2).toString());
            Query26.exec();
        }

        QSqlQuery Query27("DROP TABLE firmen");
        QSqlQuery Query28("ALTER TABLE firmen_temp RENAME TO firmen");

        qDebug() << "23 " + Query23.lastError().text();
        qDebug() << "24 " + Query24.lastError().text();
        qDebug() << "25 " + Query25.lastError().text();
        qDebug() << "26 " + Query26.lastError().text();
        qDebug() << "27 " + Query27.lastError().text();
        qDebug() << "28 " + Query28.lastError().text();
    }

    // ******* changes to database format after 2024-06-08, commit 0739f09 *******

    // add tables to log changes in members and companys
    QSqlQuery CompanyChangesQquery("CREATE TABLE IF NOT EXISTS firmen_aenderungen (id INTEGER,"
                                   "firmen_id INTEGER,"
                                   "von TEXT,"
                                   "bis TEXT,"
                                   "rang TEXT,"
                                   "leistungstyp TEXT,"
                                   "PRIMARY KEY('id'),"
                                   "FOREIGN KEY('firmen_id') REFERENCES 'firmen'('id'))");
    QSqlQuery MemberChangesQuery("CREATE TABLE IF NOT EXISTS mitglieder_aenderungen (id INTEGER,"
                                 "mitglieder_id INTEGER,"
                                 "von TEXT,"
                                 "bis TEXT,"
                                 "position TEXT,"
                                 "PRIMARY KEY('id'),"
                                 "FOREIGN KEY('mitglieder_id') REFERENCES 'mitglieder'('id'))");

    // remove columns von, bis, rang, leistungstyp from firmen
    // integrate into firmen_aenderungen
    current = checkTable("firmen", "id INTEGER, name TEXT, infos TEXT, anschrift TEXT, aktiv BOOLEAN");
    if (!current) {
        QSqlQuery Query29("CREATE TABLE firmen_temp ("
                          "id INTEGER,"
                          "name TEXT,"
                          "infos TEXT,"
                          "anschrift TEXT,"
                          "aktiv BOOLEAN,"
                          "PRIMARY KEY('id'))");
        QSqlQuery Query30("INSERT INTO firmen_temp SELECT id, name, infos, anschrift, aktiv FROM firmen");

        QSqlQuery Query31("SELECT id, seit, bis, rang, leistungstyp FROM firmen");
        QSqlQuery Query32;

        while (Query31.next()) {
            Query32.prepare("INSERT INTO firmen_aenderungen (firmen_id, von, bis, rang, leistungstyp) VALUES (:company_id, :from, :to, :rank, :type);");
            Query32.bindValue(":company_id", Query31.value(0).toInt());
            Query32.bindValue(":from", Query31.value(1).toString());
            Query32.bindValue(":to", Query31.value(2).toString());
            Query32.bindValue(":rank", Query31.value(3).toString());
            Query32.bindValue(":type", Query31.value(4).toString());
            Query32.exec();
        }

        QSqlQuery Query33("DROP TABLE firmen");
        QSqlQuery Query34("ALTER TABLE firmen_temp RENAME TO firmen");

        qDebug() << "29 " + Query29.lastError().text();
        qDebug() << "30 " + Query30.lastError().text();
        qDebug() << "31 " + Query31.lastError().text();
        qDebug() << "32 " + Query32.lastError().text();
        qDebug() << "33 " + Query33.lastError().text();
        qDebug() << "34 " + Query34.lastError().text();
    }

    // remove columns position from mitglieder
    // integrate into mitglieder_aenderungen
    current = checkTable("mitglieder", "id INTEGER, vorname TEXT, nachname TEXT, matrikelnummer TEXT, email_glr TEXT, email_privat TEXT, telefon TEXT, anschrift TEXT, hemdgroesse TEXT, vdi_nummer TEXT, sprache TEXT, aktiv BOOL");
    if (!current) {
        QSqlQuery Query35("CREATE TABLE IF NOT EXISTS mitglieder_temp ("
                          "id INTEGER PRIMARY KEY, "
                          "vorname TEXT, "
                          "nachname TEXT, "
                          "matrikelnummer TEXT, "
                          "email_glr TEXT, "
                          "email_privat TEXT, "
                          "telefon TEXT, "
                          "anschrift TEXT, "
                          "hemdgroesse TEXT, "
                          "vdi_nummer TEXT, "
                          "sprache TEXT, "
                          "aktiv BOOL)");
        QSqlQuery Query36("INSERT INTO mitglieder_temp SELECT id, vorname, nachname, matrikelnummer, email_glr, email_privat, telefon, anschrift, hemdgroesse, vdi_nummer, sprache, aktiv FROM mitglieder");

        QSqlQuery Query37("SELECT id, position FROM mitglieder");
        QSqlQuery Query38;

        while (Query37.next()) {
            Query38.prepare("INSERT INTO mitglieder_aenderungen (mitglieder_id, von, bis, position) VALUES (:member_id, :from, :to, :position)");
            Query38.bindValue(":member_id", Query37.value(0).toString());
            Query38.bindValue(":from", "");
            Query38.bindValue(":to", "");
            Query38.bindValue(":position", Query37.value(1).toString());
            Query38.exec();
        }

        QSqlQuery Query39("DROP TABLE mitglieder");
        QSqlQuery Query40("ALTER TABLE mitglieder_temp RENAME TO mitglieder");

        qDebug() << "35 " + Query35.lastError().text();
        qDebug() << "36 " + Query36.lastError().text();
        qDebug() << "37 " + Query37.lastError().text();
        qDebug() << "38 " + Query38.lastError().text();
        qDebug() << "39 " + Query39.lastError().text();
        qDebug() << "40 " + Query40.lastError().text();
    }

    // ******* changes to database format after 0000-00-00, commit 000000 *******
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
