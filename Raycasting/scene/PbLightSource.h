// 2013, PAULO BRUNO DE SOUSA SERAFIM, Fortaleza - CE, Brasil


#ifndef PB_LIGHT_SOURCE_H
#define PB_LIGHT_SOURCE_H


#include "../utils/PbPosition3d.h"


class PbLightSource
{
    public:
    
        PbLightSource();
        virtual ~PbLightSource();


        //virtual void enableLight(); // creates a light using OpenGL


        void setAmbient(float *ambientComponent);
        void setDiffuse(float *diffuseComponent);
        void setSpecular(float *specularComponent);
        void setPosition(float *positionComponent);

        void setAmbient(float r, float g, float b, float a = 1.0f);
        void setDiffuse(float r, float g, float b, float a = 1.0f);
        void setSpecular(float r, float g, float b, float a = 1.0f);
        void setPosition(float x, float y, float z, float w = 0.0f);

        void setConstantAttenuation(float constAtt) {constantAttenuation = constAtt;}
        void setLinearAttenuation(float linearAtt) {linearAttenuation = linearAtt;}
        void setQuadraticAttenuation(float quadAtt) {quadraticAttenuation = quadAtt;}


        float* getAmbient() {return ambient;}
        float* getDiffuse() {return diffuse;}
        float* getSpecular() {return specular;}
        PbPosition3d getPosition() {return position;}

        float get_x() {return position.get_x();}
        float get_y() {return position.get_y();}
        float get_z() {return position.get_z();}

        float getConstantAttenuation() {return constantAttenuation;}
        float getLinearAttenuation() {return linearAttenuation;}
        float getQuadraticAttenuation() {return quadraticAttenuation;}


    protected:
    
        float ambient[4], diffuse[4], specular[4];
        PbPosition3d position;
        float constantAttenuation, linearAttenuation, quadraticAttenuation;
        static unsigned int lightId; // starts 0
};


#endif // PB_LIGHT_SOURCE_H
