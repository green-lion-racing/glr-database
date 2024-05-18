#include "databaseporting.h"
#include <QSqlQuery>
#include <QSqlDatabase>


DatabasePorting::DatabasePorting(QString currentFile, QString enteredPassword) {

    // here are all changes to the database defined
    // and changes should be automatically applied to convert old database structures to new ones
    // check in step if end result of step is already applied

    QSqlDatabase db;
    db.setDatabaseName(currentFile);
    db.setPassword(enteredPassword);
    db.open();

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

    // reorder columns from id, kommunikationen_id, datei, dateiname to id, kommunikationen_id, dateiname, datei in kommunikationen_dateien

    // remove column firma from kommunikationen

    // remove column ansprechpartner from kommunikationen

    // rename column FirmenID to firmen_id in kommunikationen

    // rename column PersonenID to personen_id in kommunikationen

    // reorder columns from id, wann, was, firmen_id, personen_id to id, firmen_id, personen_id, wann, was in kommunikationen

    // remove column firma from personen

    // remove column fax from personen

    // rename column FirmenID to firmen_id in personen

    // reanme column Position to position in personen

    // reorder columns from id, titel, vorname, nachname, telefon, email, position, du_sie, sprache, aktiv, firmen_id to id, firmen_id, titel, vorname, nachname, position, telefon, email, du_sie, sprache, aktiv in personen

    // change column firma (with company names) to firmen_id (with company ids) in leistungen

    // change column anprechpartner (with person names) to personen_id (with person ids) with foreign key in leistungen

    // reorder columns  from id, firmen_id, personen_id, wann, wert, was, infos to id, firmen_id, personen_id, wann, was, wert, infos in leistungen

    // remove columns Str, Hausnummer, Ort, PLZ, Land and merge in anschrift in firmen

    // rename column Rang to rang in firmen

    // rename column Leistungstyp to leistungstyp in firmen

    // rename column Infos to infos in firmen

    // reorder columns from id, name, aktiv, seit, bis, rang, leistungstyp, anschrift, infos to id, name, seit, bis, rang, leistungstyp, infos, anschrift, aktiv in firmen

    //

    // ******* changes to database format after , commit  *******

    db.close();
}
