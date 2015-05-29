#include "TransformParser.h"


Transform TransformParser::parse(tinyxml2::XMLElement* parent)
{
    parseTransformPosition(parent);
    parseTransformRotation(parent);
    parseTransformScale(parent);

    return transform;
}


void TransformParser::parseTransformPosition(tinyxml2::XMLElement* transformElement)
{
    tinyxml2::XMLElement* subListElement = transformElement->FirstChildElement("Position");

    if (!subListElement)
    {
        LOGwar("Transform.Position not defined");
        return;
    }

    float pos_x, pos_y, pos_z;

    XMLCheckAttribution(subListElement->QueryFloatAttribute("x", &pos_x));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("y", &pos_y));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("z", &pos_z));

    Position3d position(pos_x, pos_y, pos_z);

    transform.setPosition(position);
}


void TransformParser::parseTransformRotation(tinyxml2::XMLElement* transformElement)
{
    tinyxml2::XMLElement* subListElement = transformElement->FirstChildElement("Rotation");

    if (!subListElement)
    {
        LOGwar("Transform.Rotation not defined");
        return;
    }

    float rot_x, rot_y, rot_z;

    XMLCheckAttribution(subListElement->QueryFloatAttribute("x", &rot_x));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("y", &rot_y));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("z", &rot_z));

    Position3d rotation(rot_x, rot_y, rot_z);

    transform.setRotation(rotation);
}


void TransformParser::parseTransformScale(tinyxml2::XMLElement* transformElement)
{
    tinyxml2::XMLElement* subListElement = transformElement->FirstChildElement("Scale");

    if (!subListElement)
    {
        LOGwar("Transform.Scale not defined");
        return;
    }

    float scale_x, scale_y, scale_z;

    XMLCheckAttribution(subListElement->QueryFloatAttribute("x", &scale_x));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("y", &scale_y));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("z", &scale_z));

    Position3d scale(scale_x, scale_y, scale_z);

    transform.setScale(scale);
}
