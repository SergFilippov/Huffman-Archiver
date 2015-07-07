#-------------------------------------------------
#
# Project created by QtCreator 2015-03-22T21:08:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ArchiveProgram
CONFIG   += c++11
TEMPLATE = app

SOURCES += main.cpp\
        widget.cpp \
    archiver.cpp \
    dearchiver.cpp

HEADERS  += widget.h \
    archiver.h \
    node.h \
    dearchiver.h

FORMS    += widget.ui
