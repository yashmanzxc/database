QT += sql
QT -= gui

TARGET = gallery-core
TEMPLATE = lib
CONFIG += lib c++11


DEFINES += GALLERYCORE_LIBRARY



# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    album.cpp \
    albumdao.cpp \
    databasemanager.cpp \
    picture.cpp \
    picturedao.cpp

HEADERS += \
    albumdao.h \
    databasemanager.h \
    gallery_core_global.h \
    album.h \
    picture.h \
    picturedao.h

# Default rules for deployment.
#//unix {
#//    target.path = /usr/lib
#///}
#//!isEmpty(target.path): INSTALLS += target
