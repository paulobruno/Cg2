#ifndef LIGHTSOURCEPARSER_H
#define LIGHTSOURCEPARSER_H


#include "tinyxml2.h"
#include "LightSource.h"
#include "Position3d.h"
#include "MaterialParser.h"


class LightSourceParser
{
    public:

        LightSourceParser() {light = new LightSource();}
        ~LightSourceParser() {delete light;}

        LightSourceParser(const LightSourceParser& other)
            : light(other.light)
        {}

        LightSourceParser& operator= (const LightSourceParser& other)
        {
            if (this != &other)
            {
                light = other.light;
            }

            return *this;
        }


        LightSource* parse(tinyxml2::XMLElement* lightElement);


    private:

        LightSource* light;


        void setLightType(tinyxml2::XMLElement* lightElement);
        void setLightExponent(tinyxml2::XMLElement* lightElement);
        void setLightEnable(tinyxml2::XMLElement* lightElement);
        void setLightName(tinyxml2::XMLElement* lightElement);
        void setLightAngleInner(tinyxml2::XMLElement* lightElement);
        void setLightAngle(tinyxml2::XMLElement* lightElement);
        void setLightPosition(tinyxml2::XMLElement* lightElement);
        void setLightDirection(tinyxml2::XMLElement* lightElement);
        void setLightVecA(tinyxml2::XMLElement* lightElement);
        void setLightVecB(tinyxml2::XMLElement* lightElement);
        void setLightAttenuation(tinyxml2::XMLElement* lightElement);
        void setLightMaterialAttributes(tinyxml2::XMLElement* lightElement);
        void setLightAmbient(tinyxml2::XMLElement* lightElement);
        void setLightSpecular(tinyxml2::XMLElement* lightElement);
        void setLightDiffuse(tinyxml2::XMLElement* lightElement);
};

#endif // LIGHTSOURCEPARSER_H
