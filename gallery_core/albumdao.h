#ifndef ALBUMDAO_H
#define ALBUMDAO_H

#include <QVector>
#include <memory>

class QSqlDatabase;
class Album;

class AlbumDao //объект доступа к данным
{
public:
    AlbumDao(QSqlDatabase& database);
    void init()const;//предназначена для создания таблицы альбомов и должна быть вызвана, когда mDatabase открыта
    void addAlbum(Album& album)const;
    void updateAlbum(const	Album&	album)const;
    void removeAlbum(int id)const;

    std::unique_ptr<std::vector<std::unique_ptr<Album>>>albums()const;

private:
    QSqlDatabase& mDatabase;//Этот параметр является соединение с базой данных для всех SQL запросов
};

#endif // ALBUMDAO_H
