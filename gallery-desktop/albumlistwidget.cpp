#include "albumlistwidget.h"
#include "ui_albumlistwidget.h"

#include <QInputDialog>
#include <QString>
#include "albummodel.h"


AlbumListWidget::AlbumListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlbumListWidget),
    mAlbumModel(nullptr)
{
    ui->setupUi(this);

    connect(ui->createAlbunButton,&QPushButton::clicked,this, &AlbumListWidget::createAlbum);
}

AlbumListWidget::~AlbumListWidget()
{
    delete ui;
}

void AlbumListWidget::setModel(AlbumModel *model)
{
    mAlbumModel = model;
    ui->albumList->setModel(mAlbumModel);
}

void AlbumListWidget::setSelectionModel(QItemSelectionModel *selectionModel)
{
    ui->albumList->setSelectionModel(selectionModel);
}

void AlbumListWidget::createAlbum()
{
    if(!mAlbumModel){return;}

    bool ok;
    QString albumName =QInputDialog::getText(this,
                                             "Create a new Album",
                                             "Choose an name",
                                             QLineEdit::Normal,
                                             "New album",
                                             &ok);
    if(ok && !albumName.isEmpty()){
        Album album(albumName);
        QModelIndex createdIndex = mAlbumModel->addAlbum(album);
        ui->albumList->setCurrentIndex(createdIndex);
    }
}
//QInputDialog На этот раз мы используем его, чтобы попросить пользователя ввести название альбома.
//Затем мы создадим класс Album с запрашиваемым названием.	Этот объект является лишь «держателем данных»;
//addAlbum() будет использовать его для создания и
//хранения реального объекта с уникальным идентификатором.
//Функция addAlbum() возвращает нам значение QModelIndex, соответствующее созданному альбому.
//Отсюда мы можем запросить представление списка, чтобы выбрать этот новый альбом.
