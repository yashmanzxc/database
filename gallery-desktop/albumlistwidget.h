#ifndef ALBUMLISTWIDGET_H
#define ALBUMLISTWIDGET_H

#include <QWidget>
#include <QItemSelectionModel> //который управляет выбором в представлении

class AlbumModel;//класс модели, который обеспечивает доступ к данным

namespace Ui {
class AlbumListWidget;
}

class AlbumListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AlbumListWidget(QWidget *parent = nullptr);
    ~AlbumListWidget();

    void setModel(AlbumModel* model);
    void setSelectionModel(QItemSelectionModel* selectionModel);
    //два сеттера будут использоваться в основном для установки модели и модели выбора albumList.
    //Затем наш класс QListView будет автоматически запрашивать модель (AlbumModel), чтобы получить количество строк
    //и Qt::DisplayRole (название альбома) для каждого из них.

    private slots:
        void createAlbum();


private:
    Ui::AlbumListWidget *ui;
    AlbumModel* mAlbumModel;
};

#endif // ALBUMLISTWIDGET_H
