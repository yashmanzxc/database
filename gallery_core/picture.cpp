#include "picture.h"



Picture::Picture(const QString& filePath): Picture(QUrl::fromLocalFile(filePath))
  //QUrl::fromLocalFile,  вызвана для предоставления QUrl объект для другого конструктора,  который принимает параметр QUrl.
{

}

Picture::Picture(const QUrl& fileUrl) : mId(-1),mAlbumId(-1),mFileUrl(fileUrl)
{
}

QUrl Picture::fileUrl() const
{
    return mFileUrl;
}

void Picture::setFileUrl(const QUrl& fileUrl)
{
    mFileUrl = fileUrl;
}
int Picture::id() const
{
    return mId;
}

void Picture::setId(int id)
{
    mId=id;
}

int Picture::albumId() const
{
    return mAlbumId;
}

void Picture::setAlbumId(int albumId)
{
    mAlbumId=albumId;
}
