#include "album.h"



Album::Album(const QString &name): mId(-1), mName(name)
//чтобы быть уверенным что по умолчанию  используется неверный ID
{
}

int Album::id() const
{
    return mId;
}

void Album::setId(int id)
{
    this->mId=id;
}

QString Album::name() const
{
    return mName;
}

void Album::setName(const QString &name)
{
    this->mName=name;
}
