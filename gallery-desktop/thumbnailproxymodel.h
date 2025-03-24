#ifndef THUMBNAILPROXYMODEL_H
#define THUMBNAILPROXYMODEL_H
// Цель этого класса - обрабатывать данные из базовой модели QAbstractItemModel (сортировка, фильтрация,
//добавление данных и так далее) и представлять их в представлении, проксируя исходную модель.
//класс mThumbnails хранит миниатюры QPixmap* с использованием путь к файлу в качестве ключа.
#include <QIdentityProxyModel>
#include <QHash>
#include <QPixmap>
#include <QVariant>
#include <QString>

class PictureModel;

class ThumbnailProxyModel : public QIdentityProxyModel
{
public:
    ThumbnailProxyModel(QObject* parent = 0);

    QVariant data(const QModelIndex& index,int role)const override;
    void setSourceModel(QAbstractItemModel* sourceModel)override;
    PictureModel* pictureModel() const;//это вспомогательная функция, которая приводит исходную модель к PictureModel*

private:
    void generatrThumbnails(const QModelIndex& startIndex,int count);//заботится о генерации миниатюр QPixmap для заданного набора изображений
    void reloadThumbnails();//является вспомогательной функцией, которая очищает сохраненные эскизы перед вызова generateThumbnails()
private:
    QHash<QString,QPixmap*>mThumbnails;
};

#endif // THUMBNAILPROXYMODEL_H
