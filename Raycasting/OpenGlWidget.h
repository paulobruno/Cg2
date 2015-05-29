#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QGLWidget>

class OpenGlWidget : public QGLWidget
{
    Q_OBJECT


    public:

        explicit OpenGlWidget(QWidget *parent = 0);


    protected:

        void initializeGL();
        void resizeGL(int w, int h);
        void paintGL();


    private:

        void drawObjects();
};

#endif // OPENGLWIDGET_H
