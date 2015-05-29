#include "PbGlWidget.h"


PbGlWidget::PbGlWidget(QWidget *parent) : QGLWidget(parent)
{

}


PbGlWidget::~PbGlWidget()
{

}


void PbGlWidget::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glFrontFace(GL_CCW);
    glShadeModel(GL_SMOOTH);
/*
    glEnable(GL_LIGHTING);

    light0->setAmbient(0.1f, 0.1f, 0.1f);
    light0->setDiffuse(0.1f, 0.1f, 0.1f);
    light0->setSpecular(1.0f, 1.0f, 1.0f);
    light0->setPosition(-2.0f, 0.0f, 2.0f, 0.0f);
    light0->enableLight();*/

    LOG("ok");
}


void PbGlWidget::resizeGL(int w, int h)
{
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);

    float aspect = (GLfloat)w / (GLfloat)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45, aspect, 0.1f, 500.0f);
}


void PbGlWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0, 0, 20, 0, 0, 0, 0, 1, 0);

    drawObjects();
}


void PbGlWidget::drawObjects()
{
    glBegin(GL_LINES);
        glVertex3f(-1.0,1.0,1.0);
        glVertex3f(-1.0,-1.0,-1.0);
    glEnd();
}
