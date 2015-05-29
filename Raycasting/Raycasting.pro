#-------------------------------------------------
#
# Project created by QtCreator 2015-05-08T09:09:15
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Raycasting
TEMPLATE = app

CONFIG  += c++11

LIBS    += -lm -lGLU -lglut

SOURCES += main.cpp\
        mainwindow.cpp \
    OpenGlWidget.cpp \
    Position3d.cpp \
    Camera.cpp \
    ImageHandlerQt.cpp \
    tinyxml2.cpp \
    Transform.cpp \
    Material.cpp \
    Scene.cpp \
    LightSource.cpp \
    Object.cpp \
    RaycastingScene.cpp \
    OpenGlScene.cpp \
    FlatButton.cpp

HEADERS  += mainwindow.h \
    OpenGlWidget.h \
    Position3d.h \
    ColorRgba.h \
    Camera.h \
    log.h \
    ImageHandler.h \
    ImageHandlerQt.h \
    tinyxml2.h \
    Transform.h \
    Material.h \
    Scene.h \
    LightSource.h \
    Object.h \
    RaycastingScene.h \
    OpenGlScene.h \
    FlatButton.h

FORMS    += mainwindow.ui
