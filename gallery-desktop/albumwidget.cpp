#include "albumwidget.h"
#include "ui_albumwidget.h"

#include <QInputDialog>
#include <QFileDialog>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QStringList>
#include <albummodel.h>
#include "picturemodel.h"
#include "thumbnailproxymodel.h"

AlbumWidget::AlbumWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlbumWidget),
    mAlbumModel(nullptr),
    mAlbumSelestionModel(nullptr),
    mPictureModel(nullptr),
    mPictureSelectionModel(nullptr)
{
    ui->setupUi(this);
    clearUi();

    ui->thumbnailListView->setSpacing(5);// параметре по умолчанию элементы приклеиваются друг к другу.	Вы можете добавить расстояние между ними.
    ui->thumbnailListView->setResizeMode(QListView::Adjust);//Этот параметр динамически размещает элементы при изменении размера представления.
    ui->thumbnailListView->setFlow(QListView::LeftToRight);//	Этот параметр задает направление списка. Здесь мы хотим отображать элементы слева направо.
    ui->thumbnailListView->setWrapping(true);//Этот параметр позволяет обернуть элемент, когда не хватает места для его отображения в видимой области.

    connect(ui->thumbnailListView, &QListView::doubleClicked,this, &AlbumWidget::pictureActivated);
    connect(ui->deleteButton,&QPushButton::clicked,this,&AlbumWidget::deleteAlbum);
    connect(ui->editButton,&QPushButton::clicked,this,&AlbumWidget::editAlbum);
    connect(ui->addPicturesButton,&QPushButton::clicked,this,&AlbumWidget::addPictures);

}

AlbumWidget::~AlbumWidget()
{
    delete ui;
}

void AlbumWidget::setAlbumModel(AlbumModel *albumModel)
{
    mAlbumModel= albumModel;
    connect(mAlbumModel,&QAbstractItemModel::dataChanged,
        [this](const QModelIndex &topLeft){
        if(topLeft == mAlbumSelestionModel->currentIndex()) {
         loadAlbum(topLeft);//обновить пользовательский интерфейс с помощью функции
        }
    });
}

void AlbumWidget::setAlbumSelectionModel(QItemSelectionModel *albumSelectionmodel)
{
    mAlbumSelestionModel = albumSelectionmodel;
    connect(mAlbumSelestionModel,&QItemSelectionModel::selectionChanged,
            [this](const QItemSelection &selected){
        if(selected.isEmpty()){
            clearUi();
            return;
        }
        loadAlbum(selected.indexes().first());//обновить пользовательский интерфейс с помощью функции
    });
}

void AlbumWidget::setPictureModel(ThumbnailProxyModel *pictureModel)
{
    mPictureModel = pictureModel;
    ui->thumbnailListView->setModel(mPictureModel);
}

void AlbumWidget::setPictureSelectionModel(QItemSelectionModel *selectionModel)
{
    //задаем модель и модель выбора thumbnailListView,
    //нашего QListView, который будет отображать миниатюры выбранного альбома.
    ui->thumbnailListView->setSelectionModel(selectionModel);
}

void AlbumWidget::deleteAlbum()
{
    //Самая важная задача в функции deleteAlbum() - получить индекс текущей строки
    // из mAlbumSelectionModel.	Затем мы можем запросить mAlbumModel удалить этот ряд.	Остальная часть
     //функция будет пытаться автоматически выбрать предыдущий или следующий альбом.

    if(mAlbumSelestionModel->selectedIndexes().isEmpty()){
        return;
    }
    int row = mAlbumSelestionModel->currentIndex().row();
    mAlbumModel->removeRow(row);

    //Попробуем выбрать предыдущий альбом
    QModelIndex previousModelIndex = mAlbumModel->index(row-1,0);
    if(previousModelIndex.isValid()){
        mAlbumSelestionModel->setCurrentIndex(previousModelIndex,QItemSelectionModel::SelectCurrent);
        return;
    }
    // Попробуем выбрать следующий альбом
    QModelIndex nextModelIndex = mAlbumModel->index(row,0);
    if(nextModelIndex.isValid()){
        mAlbumSelestionModel->setCurrentIndex(nextModelIndex,QItemSelectionModel::SelectCurrent);
        return;
    }
}

void AlbumWidget::editAlbum()
{
    if(mAlbumSelestionModel->selectedIndexes().isEmpty())
        return;
    QModelIndex	currentAlbumIndex =	mAlbumSelestionModel->selectedIndexes().first();
    QString	oldAlbumName	=	mAlbumModel->data(currentAlbumIndex,
    AlbumModel::Roles::NameRole).toString();
    bool ok;

    // 1.	Получает текущее имя из модели альбома.
    //2.	Генерирует большой диалог ввода.
    //3.	Запросите модель альбома обновить название.


    QString	newName	=	QInputDialog::getText(this,	"Album's	name","Change	Album	name",QLineEdit::Normal,oldAlbumName,&ok);
       if	(ok	&&	!newName.isEmpty())	{
            mAlbumModel->setData(currentAlbumIndex,	newName,AlbumModel::Roles::NameRole);
       }
}

void AlbumWidget::addPictures()
{
    QStringList filenames = QFileDialog::getOpenFileName((this,	"Add	pictures",QDir::homePath(),	"Picture	files	(*.jpg	*.png)");

            if (!filenames.isEmpty()) {
                    QModelIndex lastModelIndex;
                    for (auto filename : filenames) {
                        Picture picture(filename);
                        lastModelIndex = mPictureModel->pictureModel()->addPicture(picture);
                    }
                    //lastModelIndex = mPictureModel->index(lastModelIndex.row(), 0);
                    ui->thumbnailListView->setCurrentIndex(lastModelIndex);
                }
}

void AlbumWidget::clearUi()
{       ui->label->setText("");
        ui->deleteButton->setVisible(false);
        ui->editButton->setVisible(false);
        ui->addPicturesButton->setVisible(false);
}

void AlbumWidget::loadAlbum(const QModelIndex &albumIndex)
{
    mPictureModel->pictureModel()->setAlbumId(mAlbumModel->data(albumIndex, AlbumModel::Roles::IdRole).toInt());
        ui->label->setText(mAlbumModel->data(albumIndex, Qt::DisplayRole).toString());
        ui->deleteButton->setVisible(true);
        ui->editButton->setVisible(true);
        ui->addPicturesButton->setVisible(true);
}

































