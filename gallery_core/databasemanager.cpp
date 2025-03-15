#include "databasemanager.h"
#include <QSqlDatabase>
#include <QString>

DatabaseManager &DatabaseManager::instance()
{
    static DatabaseManager singleton;
    return singleton;
}

DatabaseManager::DatabaseManager(const QString& path) : mDatabase(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))),albomDao(*mDatabase)
{
    mDatabase->setDatabaseName(path);
    mDatabase->open();

    albomDao.init();
}
DatabaseManager::~DatabaseManager()
{
    mDatabase->close();
    delete mDatabase;
}
