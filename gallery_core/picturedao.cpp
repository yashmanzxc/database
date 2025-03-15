#include "picturedao.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

#include "picture.h"
#include "databasemanager.h"


PictureDao::PictureDao(QSqlDatabase &database):mDatabase(database)
{
}

void PictureDao::init() const
{//устанавливаем связь между изображением и параметром
 //изображения и собственным параметром альбома

   if(!mDatabase.tables().contains("pictures")){
       QSqlDatabase query(mDatabase);
       query.exec(QString("CREATE TABLE pictures")
                  + " (id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  + "album_id INTEGER,"
                  + "url TEXT)");
   }
}
