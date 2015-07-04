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
    Material.cpp \
    Scene.cpp \
    LightSource.cpp \
    Object.cpp \
    RaycastingScene.cpp \
    OpenGlScene.cpp \
    ObjectFactory.cpp \
    CameraParser.cpp \
    EffectsParser.cpp \
    PerspectiveParser.cpp \
    MaterialParser.cpp \
    LightsParser.cpp \
    ObjectsParser.cpp \
    Effects.cpp \
    Perspective.cpp \
    SceneXmlLoader.cpp \
    ObjectProperties.cpp \
    ObjectPropertiesParser.cpp \
    TransformParser.cpp \
    ObjectEffectsParser.cpp \
    LightSourceParser.cpp \
    Sphere.cpp \
    Transform.cpp \
    Matrix4.cpp \
    Cylinder.cpp \
    Cube.cpp

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
    BaseCreator.h \
    ObjectFactory.h \
    CameraCreator.h \
    SphereCreator.h \
    CameraParser.h \
    EffectsParser.h \
    PerspectiveParser.h \
    MaterialParser.h \
    ObjectsParser.h \
    LightsParser.h \
    Effects.h \
    Perspective.h \
    SceneXmlLoader.h \
    ObjectProperties.h \
    ObjectPropertiesParser.h \
    TransformParser.h \
    ObjectEffects.h \
    ObjectEffectsParser.h \
    LightSourceParser.h \
    Sphere.h \
    Matrix4.h \
    Cylinder.h \
    Cube.h

FORMS    += mainwindow.ui
