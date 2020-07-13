#-------------------------------------------------
#
# Project created by QtCreator 2020-01-16T19:07:01
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PlaneWar
TEMPLATE = app


SOURCES += main.cpp\
    enemybullet.cpp \
        mainscene.cpp \
    map.cpp \
    heroplane.cpp \
    bullet.cpp \
    enemyplane.cpp \
    bomb.cpp

HEADERS  += mainscene.h \
    config.h \
    enemybullet.h \
    map.h \
    heroplane.h \
    bullet.h \
    enemyplane.h \
    bomb.h


CONFIG += resources_big

DISTFILES += \
    res/Axero - Trip.mp3

RESOURCES += \
    res.qrc
