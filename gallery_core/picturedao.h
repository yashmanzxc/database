#ifndef PICTUREDAO_H
#define PICTUREDAO_H

#include <QVector>
#include <memory>

class QSqlDatabase;
class Picture;

class PictureDao
{
public:
   explicit PictureDao(QSqlDatabase& database);
    void init()const;
    void addPictureAlbum(int albumId,Picture& pictture)const;
    void removePicture(int id)const;
    void removePictureAlbum(int albumId)const;

    std::unique_ptr<std::vector<std::unique_ptr<Picture>>>pictureAlbum(int albumId)const;
private:
    QSqlDatabase& mDatabase;
};

#endif // PICTUREDAO_H
