#include "albumdao.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include "databasemanager.h"
#include <QString>
#include <QVariant>
#include <QVector>
#include "album.h"
#include <memory>
#include <algorithm>

using namespace std;

AlbumDao::AlbumDao(QSqlDatabase& database):mDatabase(database)
{
}

void AlbumDao::init()const
{
    if(!mDatabase.tables().contains("albums")){
        QSqlQuery query(mDatabase);
        query.exec("CREATE	TABLE	albums(id INTEGER PRIMARY	KEY	AUTOINCREMENT,	name TEXT)");
        //query.exec способ выполнения запроса
    }
}

void AlbumDao::addAlbum(Album& album) const
{
    QSqlQuery query(mDatabase);
    query.prepare("INSERT	INTO	albums	(name)	VALUES	(:name)");
    query.bindValue(":name",album.name());//связываем значения QVariant
    query.exec();//связанные значения будут правильно заменены.
    album.setId(query.lastInsertId().toInt());

    //query.lastInsertId(), которая возвращает значение QVariant, содержащее идентификатор только что вставленной строки альбома.
}

void AlbumDao::updateAlbum(const Album &album) const
{
    QSqlQuery query(mDatabase);
    query.prepare("UPDATE albums SET name = (:name) WHERE id = (:id)");
    query.bindValue(":name", album.name());
    query.bindValue(":id", album.id());
    query.exec();
}

void AlbumDao::removeAlbum(int id) const
{
    QSqlQuery query(mDatabase);
    query.prepare("DELETE FROM albums WHERE id = (:id)");
    query.bindValue(":id", id);
    query.exec();
}

std::unique_ptr<std::vector<std::unique_ptr<Album> > > AlbumDao::albums() const
{
    //возвращает вектор на Album
    //Этот вектор является владельцем содержащихся в нем элементов Album
    QSqlQuery query("SELECT * FROM albums",mDatabase);
    query.exec();
    unique_ptr<vector<unique_ptr<Album>>> list(new vector<unique_ptr<Album>>());
    while(query.next()) {
            unique_ptr<Album> album(new Album());
            album->setId(query.value("id").toInt());
            album->setName(query.value("name").toString());
            list->push_back(move(album));
        }
        return list;
}


