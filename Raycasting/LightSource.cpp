// 2013, PAULO BRUNO DE SOUSA SERAFIM, Fortaleza - CE, Brasil


#include "LightSource.h"


//#include <iostream>
/*
#ifdef __APPLE__
    #include "gl.h"
#else
    #include "GL/gl.h"
#endif
*/

unsigned int LightSource :: lightId = 0;


LightSource :: LightSource()
{
    ambient[0] = 0.0f;
    ambient[1] = 0.0f;
    ambient[2] = 0.0f;
    ambient[3] = 1.0f;

    diffuse[0] = 1.0f;
    diffuse[1] = 1.0f;
    diffuse[2] = 1.0f;
    diffuse[3] = 1.0f;

    specular[0] = 1.0f;
    specular[1] = 1.0f;
    specular[2] = 1.0f;
    specular[3] = 1.0f;

    position.set_pos(0.0f, 0.0f, 1.0f);

    constantAttenuation = 1.0f;
    linearAttenuation = 0.0f;
    quadraticAttenuation = 0.0f;
}


LightSource :: ~LightSource()
{
    --lightId;
}

/*
void LightSource :: enableLight()
{
    if (lightId > 7)
    {
        std::cout << "Cannot create more than 8 light sources.\n";
    }
    else
    {
        glEnable(GL_LIGHT0 + lightId);

        glLightfv(GL_LIGHT0 + lightId, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0 + lightId, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0 + lightId, GL_SPECULAR, specular);
        glLightfv(GL_LIGHT0 + lightId, GL_POSITION, position);

        glLightf(GL_LIGHT0 + lightId, GL_CONSTANT_ATTENUATION, constantAttenuation);
        glLightf(GL_LIGHT0 + lightId, GL_LINEAR_ATTENUATION, linearAttenuation);
        glLightf(GL_LIGHT0 + lightId, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);

        ++lightId;
    }
}
*/

void LightSource :: setAmbient(float *ambientComponent)
{
    ambient[0] = *(ambientComponent);
    ambient[1] = *(ambientComponent + 1);
    ambient[2] = *(ambientComponent + 2);
    ambient[3] = *(ambientComponent + 3);
}


void LightSource :: setDiffuse(float *diffuseComponent)
{
    diffuse[0] = *(diffuseComponent);
    diffuse[1] = *(diffuseComponent + 1);
    diffuse[2] = *(diffuseComponent + 2);
    diffuse[3] = *(diffuseComponent + 3);
}


void LightSource :: setSpecular(float *specularComponent)
{
    specular[0] = *(specularComponent);
    specular[1] = *(specularComponent + 1);
    specular[2] = *(specularComponent + 2);
    specular[3] = *(specularComponent + 3);
}


void LightSource :: setPosition(float *positionComponent)
{
    position.set_pos(*(positionComponent),
                     *(positionComponent) + 1,
                     *(positionComponent) + 2);
}


void LightSource :: setDirection(float *directionComponent)
{
    direction[0] = *(directionComponent);
    direction[1] = *(directionComponent + 1);
    direction[2] = *(directionComponent + 2);
    direction[3] = *(directionComponent + 3);
}


void LightSource::setVecA(float *vecAComponent)
{
    vecA[0] = *(vecAComponent);
    vecA[1] = *(vecAComponent + 1);
    vecA[2] = *(vecAComponent + 2);
    vecA[3] = *(vecAComponent + 3);
}


void LightSource::setVecB(float *vecBComponent)
{
    vecB[0] = *(vecBComponent);
    vecB[1] = *(vecBComponent + 1);
    vecB[2] = *(vecBComponent + 2);
    vecB[3] = *(vecBComponent + 3);
}


void LightSource :: setAmbient(float r, float g, float b, float a)
{
    ambient[0] = r;
    ambient[1] = g;
    ambient[2] = b;
    ambient[3] = a;
}


void LightSource :: setDiffuse(float r, float g, float b, float a)
{
    diffuse[0] = r;
    diffuse[1] = g;
    diffuse[2] = b;
    diffuse[3] = a;
}


void LightSource :: setSpecular(float r, float g, float b, float a)
{
    specular[0] = r;
    specular[1] = g;
    specular[2] = b;
    specular[3] = a;
}


void LightSource :: setPosition(float x, float y, float z, float w)
{
    position.set_pos(x, y, z);
}


void LightSource::setDirection(float x, float y, float z, float w)
{
    direction[0] = x;
    direction[1] = y;
    direction[2] = z;
    direction[3] = w;
}


void LightSource::setVecA(float x, float y, float z, float w)
{
    vecA[0] = x;
    vecA[1] = y;
    vecA[2] = z;
    vecA[3] = w;
}


void LightSource::setVecB(float x, float y, float z, float w)
{
    vecB[0] = x;
    vecB[1] = y;
    vecB[2] = z;
    vecB[3] = w;
}
