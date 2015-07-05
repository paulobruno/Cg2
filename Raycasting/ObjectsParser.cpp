#include "ObjectsParser.h"


std::vector<Object*> ObjectsParser::parse(tinyxml2::XMLNode* parent)
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
            Object* object = parseObject(objectElement);

            if (object)
            {
                objects.push_back(object);
            }

            objectElement = objectElement->NextSiblingElement("Object");
        }
    }


    return objects;
}


Object* ObjectsParser::parseObject(tinyxml2::XMLElement* objectElement)
{
    ObjectPropertiesParser objPropertiesParser;
    TransformParser transformParser;
    MaterialParser materialParser;
    ObjectEffectsParser objEffectsParser;

    ObjectProperties properties = objPropertiesParser.parse(objectElement);
    Transform transform = transformParser.parse(objectElement);
    Material material = materialParser.parse(objectElement);
    ObjectEffects effects = objEffectsParser.parse(objectElement);


    // TODO transform this selection into an AbstractFactory
    if (properties.getType() == "OBJSPHERE")
    {
        return new Sphere(transform, material, properties, effects);
    }
    if (properties.getType() == "OBJCUBE")
    {
        return new Cube(transform, material, properties, effects);

    }
    if (properties.getType() == "OBJCYLINDER")
    {
        return new Cylinder(transform, material, properties, effects);
    }/*
    if (properties.getType() == "OBJCONE")
    {
        return new Cone(transform, material, properties, effects);
    }*/

    return nullptr;
}


