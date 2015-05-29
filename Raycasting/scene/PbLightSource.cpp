// 2013, PAULO BRUNO DE SOUSA SERAFIM, Fortaleza - CE, Brasil


#include "PbLightSource.h"


//#include <iostream>
/*
#ifdef __APPLE__
    #include "gl.h"
#else
    #include "GL/gl.h"
#endif
*/
unsigned int PbLightSource :: lightId = 0;


PbLightSource :: PbLightSource()
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


PbLightSource :: ~PbLightSource()
{
    --lightId;
}

/*
void PbLightSource :: enableLight()
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

void PbLightSource :: setAmbient(float *ambientComponent)
{
    ambient[0] = *(ambientComponent);
    ambient[1] = *(ambientComponent + 1);
    ambient[2] = *(ambientComponent + 2);
    ambient[3] = *(ambientComponent + 3);
}


void PbLightSource :: setDiffuse(float *diffuseComponent)
{
    diffuse[0] = *(diffuseComponent);
    diffuse[1] = *(diffuseComponent + 1);
    diffuse[2] = *(diffuseComponent + 2);
    diffuse[3] = *(diffuseComponent + 3);
}


void PbLightSource :: setSpecular(float *specularComponent)
{
    specular[0] = *(specularComponent);
    specular[1] = *(specularComponent + 1);
    specular[2] = *(specularComponent + 2);
    specular[3] = *(specularComponent + 3);
}


void PbLightSource :: setPosition(float *positionComponent)
{
    position.set_pos(*(positionComponent),
                     *(positionComponent) + 1,
                     *(positionComponent) + 2);
}


void PbLightSource :: setAmbient(float r, float g, float b, float a)
{
    ambient[0] = r;
    ambient[1] = g;
    ambient[2] = b;
    ambient[3] = a;
}


void PbLightSource :: setDiffuse(float r, float g, float b, float a)
{
    diffuse[0] = r;
    diffuse[1] = g;
    diffuse[2] = b;
    diffuse[3] = a;
}


void PbLightSource :: setSpecular(float r, float g, float b, float a)
{
    specular[0] = r;
    specular[1] = g;
    specular[2] = b;
    specular[3] = a;
}


void PbLightSource :: setPosition(float x, float y, float z, float w)
{
    position.set_pos(x, y, z);
}
