#-------------------------------------------------
#
# Project created by QtCreator 2015-05-05T10:15:50
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RaycastingNew
TEMPLATE = app

CONFIG  += c++11

LIBS    += -lm -lGLU -lglut

SOURCES += main.cpp\
        mainwindow.cpp \
    PbGlWidget.cpp \
    tinyxml2.cpp \
    PbCamera.cpp \
    PbLightSource.cpp \
    PbQt.cpp \
    PbScene.cpp \
    PbObject.cpp \
    PbTransform.cpp \
    PbMaterial.cpp \
    PbFace.cpp \
    PbVertex.cpp \
    PbAffineSpace.cpp

HEADERS  += mainwindow.h \
    PbGlWidget.h \
    PbPosition4d.h \
    PbColor4.h \
    PbQt.h \
    tinyxml2.h \
    pb_log.h \
    PbCamera.h \
    PbGraphics.h \
    PbLightSource.h \
    PbPosition3d.h \
    PbScene.h \
    PbObject.h \
    PbMaterial.h \
    PbTransform.h \
    PbFace.h \
    PbVertex.h \
    PbAffineSpace.h

FORMS    += mainwindow.ui
