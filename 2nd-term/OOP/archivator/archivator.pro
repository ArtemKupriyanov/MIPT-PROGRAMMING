#-------------------------------------------------
#
# Project created by QtCreator 2016-03-12T00:53:51
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = archivator
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    decode.cpp \
    encode.cpp \
    read.cpp \
    write.cpp

HEADERS += \
    decode.h \
    encode.h \
    read.h \
    write.h
