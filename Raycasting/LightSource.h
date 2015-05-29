#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H


#include "Position3d.h"
#include "Transform.h"


class LightSource
{
    public:

        LightSource();
        virtual ~LightSource();


        void enableLight(); // creates a light using OpenGL


        void setAmbient(float *ambientComponent);
        void setDiffuse(float *diffuseComponent);
        void setSpecular(float *specularComponent);
        void setPosition(float *positionComponent);
        void setDirection(float *directionComponent);
        void setVecA(float *vecAComponent);
        void setVecB(float *vecBComponent);

        void setAmbient(float r, float g, float b, float a = 1.0f);
        void setDiffuse(float r, float g, float b, float a = 1.0f);
        void setSpecular(float r, float g, float b, float a = 1.0f);
        void setPosition(float x, float y, float z, float w = 0.0f);
        void setDirection(float x, float y, float z, float w = 1.0f);
        void setVecA(float x, float y, float z, float w = 1.0f);
        void setVecB(float x, float y, float z, float w = 1.0f);

        void setConstantAttenuation(float constAtt) {constantAttenuation = constAtt;}
        void setLinearAttenuation(float linearAtt) {linearAttenuation = linearAtt;}
        void setQuadraticAttenuation(float quadAtt) {quadraticAttenuation = quadAtt;}


        float* getAmbient() {return ambient;}
        float* getDiffuse() {return diffuse;}
        float* getSpecular() {return specular;}
        Position3d getPosition() {return position;}

        float getConstantAttenuation() {return constantAttenuation;}
        float getLinearAttenuation() {return linearAttenuation;}
        float getQuadraticAttenuation() {return quadraticAttenuation;}


    protected:

        Transform transform;
        float ambient[4], diffuse[4], specular[4], direction[4], vecA[4], vecB[4];
        Position3d position;
        float constantAttenuation, linearAttenuation, quadraticAttenuation;
        static unsigned int lightId; // starts 0
};


#endif // LIGHTSOURCE_H
