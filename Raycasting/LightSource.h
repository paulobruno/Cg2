#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H


#include "Position3d.h"
#include "Transform.h"
#include "Material.h"

#include <string>


class LightSource
{
    public:

        LightSource();
        virtual ~LightSource();


        void enableLight(); // creates a light using OpenGL

        void setName(std::string name);
        void setType(std::string type);
        void setEnable(bool isEnabled);

        void setExponent(float exponent);
        void setAngle(float angle);
        void setAngleInner(float angleInner);

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

        //void setMaterial(Material mat) {material = mat;}

        float* getAmbient() {return ambient;}
        float* getDiffuse() {return diffuse;}
        float* getSpecular() {return specular;}
        Position3d getPosition() {return position;}

        float getConstantAttenuation() {return constantAttenuation;}
        float getLinearAttenuation() {return linearAttenuation;}
        float getQuadraticAttenuation() {return quadraticAttenuation;}

        std::string getType() {return type;}
        std::string getName() {return name;}


    protected:

        bool enable;
        std::string type, name;
        float ambient[4], diffuse[4], specular[4], vecA[4], vecB[4];
        Position3d position, direction;
        float constantAttenuation, linearAttenuation, quadraticAttenuation;
        float exponent, angleInner, angle;
        static unsigned int lightId; // starts 0
        //Material material;
};


#endif // LIGHTSOURCE_H
