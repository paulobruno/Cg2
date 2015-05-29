#include "ObjectEffectsParser.h"


ObjectEffects ObjectEffectsParser::parse(tinyxml2::XMLNode* objectEffectsNode)
{
    tinyxml2::XMLElement* objectEffectsElement = objectEffectsNode->FirstChildElement("Effects");

    if (!objectEffectsElement)
    {
        LOGwar("Object.Effects not defined");
    }
    else
    {
        parseEffectsMotion(objectEffectsElement);
        parseEffectsTranslate(objectEffectsElement);
        parseEffectsRotate(objectEffectsElement);
    }

    return effects;
}


void ObjectEffectsParser::parseEffectsMotion(tinyxml2::XMLElement* effectsElement)
{
    bool motion = false;

    XMLCheckAttribution(effectsElement->QueryBoolAttribute("Motion", &motion));

    effects.updateMotion(motion);
}


void ObjectEffectsParser::parseEffectsTranslate(tinyxml2::XMLElement* effectsElement)
{
    tinyxml2::XMLElement* subListElement = effectsElement->FirstChildElement("Translate");

    if (!subListElement)
    {
        LOGwar("Object.Effects.Translate not defined");
        return;
    }

    float translate_x, translate_y, translate_z;

    XMLCheckAttribution(subListElement->QueryFloatAttribute("x", &translate_x));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("y", &translate_y));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("z", &translate_z));

    effects.updateTranslate(Position3d(translate_x, translate_y, translate_z));
}


void ObjectEffectsParser::parseEffectsRotate(tinyxml2::XMLElement* effectsElement)
{
    tinyxml2::XMLElement* subListElement = effectsElement->FirstChildElement("Rotate");

    if (!subListElement)
    {
        LOGwar("Object.Effects.Rotate not defined");
        return;
    }

    float rotate_x, rotate_y, rotate_z;

    XMLCheckAttribution(subListElement->QueryFloatAttribute("x", &rotate_x));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("y", &rotate_y));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("z", &rotate_z));

    effects.updateRotate(Position3d(rotate_x, rotate_y, rotate_z));
}
