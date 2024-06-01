#ifndef DATABASEPORTING_H
#define DATABASEPORTING_H

#include "QString"

class DatabasePorting
{
public:
    DatabasePorting();

private:
    bool checkTable(QString tableName, QString tableStructure);
};

#endif // DATABASEPORTING_H
