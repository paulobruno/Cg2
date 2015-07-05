#include "EffectsParser.h"


Effects EffectsParser::parse(tinyxml2::XMLNode* parent)
{
    tinyxml2::XMLElement* effectsElement = parent->FirstChildElement("Effects");

    if (!effectsElement)
    {
        LOGwar("Effects not defined");
    }
    else
    {
        float radius = 0.0f, focalLength = 0.0f, dof = 0.0f;

        XMLCheckAttribution(effectsElement->QueryFloatAttribute("DOF", &dof));
        XMLCheckAttribution(effectsElement->QueryFloatAttribute("FocalLength", &focalLength));
        XMLCheckAttribution(effectsElement->QueryFloatAttribute("Radius", &radius));

        effects = Effects(radius, focalLength, dof);
    }

    return effects;
}
