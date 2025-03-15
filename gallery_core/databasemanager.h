#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include "albumdao.h"

class QSqlDatabase;

const QString DATABASE_FILENAME = "gallery.db";

class DatabaseManager
{
public:
    static DatabaseManager& instance();
    ~DatabaseManager();
protected:
    DatabaseManager(const QString& path = DATABASE_FILENAME);
    DatabaseManager& operator =(const DatabaseManager& rhs);
private:
    QSqlDatabase* mDatabase;
public:
    const AlbumDao albomDao;//предназначена для предоставления доступа клиентам DatabaseManager к полю albumDao
};

#endif // DATABASEMANAGER_H
