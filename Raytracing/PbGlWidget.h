#ifndef PBGLWIDGET_H
#define PBGLWIDGET_H


#include <QGLWidget>

#ifdef __APPLE__
    #include "glu.h"
#else
    #include "GL/glu.h"
#endif

#include "pb_log.h"


class PbGlWidget : public QGLWidget
{
    Q_OBJECT

    public:

        explicit PbGlWidget(QWidget *parent = 0);
        ~PbGlWidget();


    protected:

        virtual void initializeGL();
        virtual void resizeGL(int w, int h);
        virtual void paintGL();


    private:

        void drawObjects();
};

#endif // PBGLWIDGET_H
