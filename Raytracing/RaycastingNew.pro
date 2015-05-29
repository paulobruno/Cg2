#-------------------------------------------------
#
# Project created by QtCreator 2015-04-30T14:42:06
#
#-------------------------------------------------

QT       += core gui opengl

LIBS	+=  -lm -lGL -lGLU

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RaycastingNew
TEMPLATE = app

UI_DIR  =   temp
RCC_DIR =   temp
MOC_DIR =   temp

SOURCES += main.cpp\
    mainwindow.cpp \
    main_controller.cpp \
    PbCamera.cpp \
    PbLightSource.cpp \
    PbQt.cpp \
    tinyxml2.cpp \
    PbGlWidget.cpp

HEADERS  += mainwindow.h \
    main_controler.h \
    PbCamera.h \
    PbColor4.h \
    PbGraphics.h \
    PbLightSource.h \
    pb_log.h \
    PbPosition4d.h \
    PbQt.h \
    tinyxml2.h \
    PbPosition3d.h \
    PbGlWidget.h

FORMS    += mainwindow.ui
