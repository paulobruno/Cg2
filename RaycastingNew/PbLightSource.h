// 2013, PAULO BRUNO DE SOUSA SERAFIM, Fortaleza - CE, Brasil


#ifndef PB_LIGHT_SOURCE_H
#define PB_LIGHT_SOURCE_H


#include "PbPosition3d.h"
#include "PbTransform.h"


class PbLightSource
{
    public:
    
        PbLightSource();
        virtual ~PbLightSource();


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
        PbPosition3d getPosition() {return position;}

        float getConstantAttenuation() {return constantAttenuation;}
        float getLinearAttenuation() {return linearAttenuation;}
        float getQuadraticAttenuation() {return quadraticAttenuation;}


    protected:
    
        PbTransform transform;
        float ambient[4], diffuse[4], specular[4], direction[4], vecA[4], vecB[4];
        PbPosition3d position;
        float constantAttenuation, linearAttenuation, quadraticAttenuation;
        static unsigned int lightId; // starts 0
};


#endif // PB_LIGHT_SOURCE_H
