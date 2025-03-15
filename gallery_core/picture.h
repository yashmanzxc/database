#ifndef PICTURE_H
#define PICTURE_H

#include <QUrl> //предоставляет функциональность для работы с URL-адресами
#include <QString>

#include "gallery_core_global.h"

class GALLERYCORESHARED_EXPORT Picture
{
public:
    Picture(const QString& filePath = "");
    Picture(const QUrl& fileUrl);

    int id() const;
    void setId(int id);

    int albumId()const;
    void setAlbumId(int albumId);

    QUrl fileUrl()const;
    void setFileUrl(const QUrl& fileUrl);

private:
    int mId;
    int mAlbumId;
    QUrl mFileUrl;
};

#endif // PICTURE_H
