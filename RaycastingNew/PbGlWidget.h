#ifndef PBGLWIDGET_H
#define PBGLWIDGET_H


#include <QGLWidget>

#include "PbScene.h"


class PbGlWidget : public QGLWidget
{
    Q_OBJECT


    public:

        explicit PbGlWidget(QWidget *parent = 0);


    protected:

        void initializeGL();
        void resizeGL(int w, int h);
        void paintGL();


    private:

        PbScene scene;
        PbObject sphere;


        void drawObjects();

};

#endif // PBGLWIDGET_H
