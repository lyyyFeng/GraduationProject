#-------------------------------------------------
#
# Project created by QtCreator 2019-01-20T15:59:31
#
#-------------------------------------------------
QT += svg
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IMSG
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    loginwindow.cpp \
    titlebar.cpp \
    mylineedit.cpp \
    talkwindow.cpp \
    stackdlg.cpp \
    message.cpp

HEADERS += \
        mainwindow.h \
    loginwindow.h \
    titlebar.h \
    mylineedit.h \
    talkwindow.h \
    stackdlg.h \
    message.h

FORMS += \
        mainwindow.ui \
    loginwindow.ui \
    talkwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Resources/新建文件夹 (2)/min_hover.bmp \
    Resources/新建文件夹 (2)/min_press.bmp \
    Resources/新建文件夹 (2)/arrow.png \
    Resources/新建文件夹 (2)/arrow_hover.png \
    Resources/新建文件夹 (2)/arrow_press.png \
    Resources/新建文件夹 (2)/close.png \
    Resources/新建文件夹 (2)/close_hover.png \
    Resources/新建文件夹 (2)/close_press.png \
    Resources/新建文件夹 (2)/min_.png \
    Resources/新建文件夹 (2)/min_hover.bmp \
    Resources/新建文件夹 (2)/min_press.bmp \
    Resources/新建文件夹 (2)/arrow.png \
    Resources/新建文件夹 (2)/arrow_hover.png \
    Resources/新建文件夹 (2)/arrow_press.png \
    Resources/新建文件夹 (2)/close.png \
    Resources/新建文件夹 (2)/close_hover.png \
    Resources/新建文件夹 (2)/close_press.png \
    Resources/新建文件夹 (2)/min_.png

RESOURCES += \
    resources.qrc
