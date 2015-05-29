#include "PbGlWidget.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif


PbGlWidget::PbGlWidget(QWidget *parent) :
    QGLWidget(parent)
{
    sphere.loadObject("sphere.obj");
}


void PbGlWidget::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glFrontFace(GL_CCW);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);

    float ambient[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float diffuse[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    float specular[4] = {0.0f, 0.0f, 0.0f, 0.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
}


void PbGlWidget::resizeGL(int w, int h)
{
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45, 1.5, 0.01, 120000);
    gluLookAt(0.0f, 0.0f, -10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, -10.0f);
    //glOrtho(-2.0, 2.0, -2.0, 2.0, -1.0, 1.0);
}


void PbGlWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawObjects();
}


void PbGlWidget::drawObjects()
{
    sphere.draw();
}
