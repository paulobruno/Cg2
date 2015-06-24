#include "LightsParser.h"


std::vector<LightSource*> LightsParser::parse(tinyxml2::XMLNode *lightsNode)
{
    tinyxml2::XMLElement* lightsGroup = lightsNode->FirstChildElement("Lights");

    if (!lightsGroup)
    {
        LOGwar("Light.Material not defined");
    }
    else
    {
        tinyxml2::XMLElement* lightElement = lightsGroup->FirstChildElement("Light");

        if (!lightElement)
        {
            LOGwar("Ambient light not defined");
        }
        else
        {
            LightSource* ambientLight = parseAmbientLight(lightElement);

            if (ambientLight)
            {
                lights.push_back(ambientLight);
            }


            lightElement = lightsGroup->FirstChildElement("Light");

            while (lightElement)
            {
                LightSource* light = parseLight(lightElement);

                if (light)
                {
                    lights.push_back(light);
                }

                lightElement = lightElement->NextSiblingElement("Light");
            }
        }
    }

    return lights;
}


LightSource* LightsParser::parseAmbientLight(tinyxml2::XMLElement* lightElement)
{
    LightSource* ambientLight = new LightSource();
    ambientLight->setName("Ambient Light");
    ambientLight->setType("LIGHT_AMBIENT");

    const char* lightType = nullptr;

    lightType = lightElement->Attribute("Type");

    if (strcmp(lightType, "LIGHT_AMBIENT"))
    {
        LOGerr("First light must be ambient");
    }

    return ambientLight;
}


LightSource* LightsParser::parseLight(tinyxml2::XMLElement *lightElement)
{
    LightSourceParser* lightParser = new LightSourceParser();

    LightSource* light = lightParser->parse(lightElement);

    return light;
}
