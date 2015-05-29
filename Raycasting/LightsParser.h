#ifndef LIGHTSPARSER_H
#define LIGHTSPARSER_H


#include "LightSource.h"
#include "LightSourceParser.h"
#include "tinyxml2.h"
#include <vector>


class LightsParser
{
    public:

        LightsParser() {}
        ~LightsParser() {}

        LightsParser(const LightsParser& other)
            : lights(other.lights)
        {}

        LightsParser& operator= (const LightsParser& other)
        {
            if (this != &other)
            {
                lights = other.lights;
            }

            return *this;
        }


        std::vector<LightSource> parse(tinyxml2::XMLNode* lightsNode);


    private:

        std::vector<LightSource> lights;


        LightSource parseAmbientLight(tinyxml2::XMLElement* lightElement);
        LightSource parseLight(tinyxml2::XMLElement* lightElement);
};


#endif // LIGHTSPARSER_H
