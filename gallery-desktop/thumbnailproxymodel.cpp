#include "thumbnailproxymodel.h"
#include "PictureModel.h"
#include <QString>

const unsigned int THUMBNAIL_SIZE = 350;

ThumbnailProxyModel::ThumbnailProxyModel(QObject* parent): QIdentityProxyModel(parent),mThumbnails()
{  
}

void ThumbnailProxyModel::setSourceModel(QAbstractItemModel *sourceModel)
{
    QIdentityProxyModel::setSourceModel(sourceModel);
    if(!sourceModel){return;}
    // Сигнал modelReset срабатывает, когда необходимо загрузить изображения для данного альбома.
    connect(sourceModel, &QAbstractItemModel::modelReset,[this]{reloadThumbnails();

    });
    //Сигнал rowsInserted срабатывает каждый раз, когда добавляются новые изображения.
    connect(sourceModel, &QAbstractItemModel::rowsInserted,[this](const QModelIndex* parent, int first, int last){
        generatrThumbnails(index(first,0),last - first +1 );
    });
}

void ThumbnailProxyModel::generatrThumbnails(const QModelIndex &startIndex, int count)
{
    if(!startIndex.isValid()){return;}

    const QAbstractItemModel* model = startIndex.model();
    int lastIndex = startIndex.row()+count;
    for(int row = startIndex.row(); row<lastIndex; row++){
        QString filepath = model->data(model->index(row,0),
        PictureModel::PictureRole::FilePathRole).toString();
        QPixmap pixmap(filepath);
        auto thumbnail = new QPixmap(pixmap.scaled(THUMBNAIL_SIZE,THUMBNAIL_SIZE,
                                                   Qt::KeepAspectRatio,
                                                   Qt::SmoothTransformation));
        mThumbnails.insert(filepath,thumbnail);
    }

    //Эта функция генерирует миниатюры для заданного диапазона, указанного параметрами
    //(startIndex и count).	Для каждой картинки мы получаем путь к файлу из исходной модели,
    //используя model->data(), и генерируем уменьшенное QPixmap, которое вставляется в QHash mThumbnails.
}

void ThumbnailProxyModel::reloadThumbnails()
{
    qDeleteAll(mThumbnails);
    mThumbnails.clear();
    generatrThumbnails(index(0,0),rowCount());
}
