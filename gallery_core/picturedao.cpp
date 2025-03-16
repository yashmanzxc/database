#include "picturedao.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <memory>
#include <QVector>
#include <QString>
#include <algorithm>

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

void PictureDao::addPictureAlbum(int albumId, Picture &pictture) const
{
    QSqlQuery query(mDatabase);
    query.prepare(QString("INSERT INTO pictures")
            + " (album_id, url)"
            + " VALUES ("
            + ":album_id, "
            + ":url"
            + ")");
    query.bindValue(":album_Id",albumId);
    query.bindValue(":url",pictture.fileUrl());
    query.exec();
    //pictture.setId(query.lastInsertId().toInt());
    //pictture.setAlbumId(albumId);
}

void PictureDao::removePicture(int id) const
{
    QSqlQuery query(mDatabase);
    query.prepare("DELETE FROM pictures WHERE id = (:id)");
    query.bindValue("id",id);
    query.exec();

}

void PictureDao::removePictureAlbum(int albumId) const
{
    QSqlQuery query(mDatabase);
    query.prepare("SELECT * FROM pictures WHERE album_id = (:album_id)");
    query.bindValue(":album_id", albumId);
    query.exec();
}

std::unique_ptr<std::vector<std::unique_ptr<Picture> > > PictureDao::pictureAlbum(int albumId) const
{
    QSqlQuery query(mDatabase);
    query.prepare("SELECT * FROM pictures WHERE album_id = (:album_id)");
    query.bindValue(":albun_id",albumId);
    query.exec();
    std::unique_ptr<std::vector<std::unique_ptr<Picture>>>list(new std::vector<std::unique_ptr<Picture>>());
    while(query.next()){
        std::unique_ptr<Picture>picture(new Picture());
        picture->setId(query.value("id").toInt());
        picture->setAlbumId(query.value("album_id").toInt());
        picture->setFileUrl(query.value("url").toString());
        list->push_back(std::move(picture));

    }
    return list;


}


































