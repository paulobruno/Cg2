#include "LightsParser.h"


std::vector<LightSource*> LightsParser::parse(tinyxml2::XMLNode *lightsNode)
{
    tinyxml2::XMLElement* lightsGroup = lightsNode->FirstChildElement("Lights");

    if (!lightsGroup)
    {
        LOG("Lights not defined");
    }
    else
    {
        tinyxml2::XMLElement* lightElement = lightsGroup->FirstChildElement("Light");

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

    return lights;
}


LightSource* LightsParser::parseLight(tinyxml2::XMLElement *lightElement)
{
    LightSourceParser* lightParser = new LightSourceParser();

    LightSource* light = lightParser->parse(lightElement);

    if (light->getType() == "LIGHT_AMBIENT")
    {
        return NULL;
    }

    return light;
}
