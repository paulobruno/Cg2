#include "ObjectsParser.h"


std::vector<Object> ObjectsParser::parse(tinyxml2::XMLNode* parent)
{
    tinyxml2::XMLElement* objectsGroup = parent->FirstChildElement("Objects");

    if (!objectsGroup)
    {
        LOGwar("Object.Material not defined");
    }
    else
    {
        tinyxml2::XMLElement* objectElement = objectsGroup->FirstChildElement("Object");

        while (objectElement)
        {
            Object object = parseObject(objectElement);

            objects.push_back(object);

            objectElement = objectElement->NextSiblingElement("Object");
        }
    }


    return objects;
}


Object ObjectsParser::parseObject(tinyxml2::XMLElement* objectElement)
{
    ObjectPropertiesParser objPropertiesParser;
    TransformParser transformParser;
    MaterialParser materialParser;
    ObjectEffectsParser objEffectsParser;

    ObjectProperties properties = objPropertiesParser.parse(objectElement);
    Transform transform = transformParser.parse(objectElement);
    Material material = materialParser.parse(objectElement);
    ObjectEffects effects = objEffectsParser.parse(objectElement);

    Object object = Object(transform, material, properties, effects);

    return object;
}


