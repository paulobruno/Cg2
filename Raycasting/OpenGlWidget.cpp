#include "OpenGlWidget.h"


#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif


OpenGlWidget::OpenGlWidget(QWidget *parent) :
    QGLWidget(parent)
{
}


void OpenGlWidget::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glFrontFace(GL_CCW);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
}


void OpenGlWidget::resizeGL(int w, int h)
{
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //gluPerspective(45, 1.5, 0.01, 120000);
    glOrtho(-2.0, 2.0, -2.0, 2.0, -1.0, 1.0);
}


void OpenGlWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawObjects();
}


void OpenGlWidget::drawObjects()
{
    glBegin(GL_LINES);
        glVertex3f(1.0f, 1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
    glEnd();
}
