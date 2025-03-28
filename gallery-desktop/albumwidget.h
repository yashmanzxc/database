#ifndef ALBUMWIDGET_H
#define ALBUMWIDGET_H

#include <QWidget>
#include <QModelIndex>

//отображает данные о выбранном альбоме
namespace Ui {
class AlbumWidget;
}

class AlbumModel;
class PictureModel;
class QItemSelectionModel;
class ThumbnailProxyModel;

class AlbumWidget : public QWidget
{
    Q_OBJECT

public:

    explicit AlbumWidget(QWidget *parent = nullptr);
    ~AlbumWidget();

    void setAlbumModel(AlbumModel* albumModel);
    void setAlbumSelectionModel(QItemSelectionModel* albumSelectionmodel);
    void setPictureModel(ThumbnailProxyModel* pictureModel);
    void setPictureSelectionModel(QItemSelectionModel* selectionModel);

signals:
    void pictureActivated(const QModelIndex& index);

private slots:
    void deleteAlbum();
    void editAlbum();
    void addPictures();
private:
    void clearUi();//для очистки всей информации, отображаемой в пользовательском интерфейсе этого виджета.
    void loadAlbum(const QModelIndex& albumIndex);//для обновления пользовательского интерфейса для конкретного альбома.
private:
    Ui::AlbumWidget *ui;
    AlbumModel* mAlbumModel;
    QItemSelectionModel* mAlbumSelestionModel;

    ThumbnailProxyModel* mPictureModel;
    QItemSelectionModel* mPictureSelectionModel;

};

#endif // ALBUMWIDGET_H
