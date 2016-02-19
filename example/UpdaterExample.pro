#-------------------------------------------------
#
# Project created by QtCreator 2016-02-19T20:51:53
#
#-------------------------------------------------
include($$_PRO_FILE_PWD_/qt_updater/updater.pri)

QT       += core gui webkitwidgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UpdaterExample
TEMPLATE = app


SOURCES += main.cpp

FORMS    += mainwindow.ui

CONFIG += c++11
