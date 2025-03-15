#ifndef PICTUREDAO_H
#define PICTUREDAO_H

#include <QVector>
class QSqlDatabase;
class Picture;

class PictureDao
{
public:
   explicit PictureDao(QSqlDatabase& database);
    void init()const;
    void addPictureAlbum(int albumId,Picture& pictture)const;
    void removePicture(int id)const;
    void removePictureAlbum(int aldumId)const;
    QVector<Picture*>pictureAlbum(int albumId)const;
private:
    QSqlDatabase& mDatabase;
};

#endif // PICTUREDAO_H
