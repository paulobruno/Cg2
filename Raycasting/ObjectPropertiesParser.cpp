#include "ObjectPropertiesParser.h"


ObjectProperties ObjectPropertiesParser::parse(tinyxml2::XMLElement* objectPropertiesElement)
{
    parseObjectPropertiesName(objectPropertiesElement);
    parseObjectPropertiesEnabled(objectPropertiesElement);
    parseObjectPropertiesBump(objectPropertiesElement);
    parseObjectPropertiesTexture(objectPropertiesElement);
    parseObjectPropertiesType(objectPropertiesElement);

    return properties;
}


void ObjectPropertiesParser::parseObjectPropertiesType(tinyxml2::XMLElement* objectPropertiesElement)
{
    const char* objType = nullptr;

    objType = objectPropertiesElement->Attribute("Type");

    if (!objType)
    {
        LOGerr("Object.Type string error");
        return;
    }

    properties.setType(std::string(objType));
}


void ObjectPropertiesParser::parseObjectPropertiesEnabled(tinyxml2::XMLElement* objectPropertiesElement)
{
    bool enabled = false;

    XMLCheckAttribution(objectPropertiesElement->QueryBoolAttribute("Enabled", &enabled));

    properties.setEnabled(enabled);
}


void ObjectPropertiesParser::parseObjectPropertiesName(tinyxml2::XMLElement* objectPropertiesElement)
{
    const char* objName = nullptr;
    objName = objectPropertiesElement->Attribute("Name");

    if (!objName)
    {
        LOGerr("Object.Name string error");
        return;
    }

    properties.setName(std::string(objName));
}


void ObjectPropertiesParser::parseObjectPropertiesTexture(tinyxml2::XMLElement* objectPropertiesElement)
{
    const char* objTexture = nullptr;

    objTexture = objectPropertiesElement->Attribute("Texture");

    if (!objTexture)
    {
        LOGerr("Object.Texture string error");
        return;
    }

    properties.setTexture(std::string(objTexture));
}


void ObjectPropertiesParser::parseObjectPropertiesBump(tinyxml2::XMLElement* objectPropertiesElement)
{
    const char* objBump = nullptr;
    objBump = objectPropertiesElement->Attribute("Bump");

    if (!objBump)
    {
        LOGerr("Object.Bump string error");
        return;
    }

    properties.setBump(std::string(objBump));
}
