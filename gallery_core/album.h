#ifndef ALBUM_H
#define ALBUM_H
#include <QString>

#include "gallery_core_global.h"

class GALLERYCORESHARED_EXPORT Album
{
public:
    explicit Album(const QString& name = "");

    int id()const;// Геттер для ID

    void setId(int id); // Сеттер для ID

    QString name()const; // Геттер для имени

    void setName(const QString& name);// Сеттер для имени

private:
    int mId;
    QString mName;
};

#endif // ALBUM_H
