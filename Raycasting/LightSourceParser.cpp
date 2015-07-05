#include "LightSourceParser.h"


LightSource* LightSourceParser::parse(tinyxml2::XMLElement *lightElement)
{
    setLightEnable(lightElement);
    setLightName(lightElement);
    setLightAngleInner(lightElement);
    setLightExponent(lightElement);
    setLightType(lightElement);
    setLightAngle(lightElement);
    setLightPosition(lightElement);
    setLightDirection(lightElement);
    setLightVecA(lightElement);
    setLightVecB(lightElement);
    setLightAttenuation(lightElement);
    setLightMaterialAttributes(lightElement);


    return light;
}


void LightSourceParser::setLightType(tinyxml2::XMLElement* lightElement)
{
    const char* lightType = nullptr;
    lightType = lightElement->Attribute("Type");

    if (!lightType)
    {
        LOGerr("light->Type string error");
        return;
    }

    light->setType(std::string(lightType));
}


void LightSourceParser::setLightExponent(tinyxml2::XMLElement* lightElement)
{
    float lightExponent = 0.0f;

    XMLCheckAttribution(lightElement->QueryFloatAttribute("Exponent", &lightExponent));

    light->setExponent(lightExponent);
}


void LightSourceParser::setLightEnable(tinyxml2::XMLElement* lightElement)
{
    bool lightEnable = true;

    XMLCheckAttribution(lightElement->QueryBoolAttribute("Enable", &lightEnable));

    light->setEnable(lightEnable);
}


void LightSourceParser::setLightName(tinyxml2::XMLElement* lightElement)
{
    const char* lightName = nullptr;
    lightName = lightElement->Attribute("Name");

    if (!lightName)
    {
        LOGerr("light->Name string error");
        return;
    }

    light->setName(lightName);
}


void LightSourceParser::setLightAngleInner(tinyxml2::XMLElement* lightElement)
{
    float lightAngleInner = 0.0f;

    XMLCheckAttribution(lightElement->QueryFloatAttribute("AngleInner", &lightAngleInner));

    light->setAngleInner(lightAngleInner);
}


void LightSourceParser::setLightAngle(tinyxml2::XMLElement* lightElement)
{
    float lightAngle = 0.0f;

    XMLCheckAttribution(lightElement->QueryFloatAttribute("Angle", &lightAngle));

    light->setAngle(lightAngle);
}


void LightSourceParser::setLightPosition(tinyxml2::XMLElement* lightElement)
{

    tinyxml2::XMLElement* subListElement = lightElement->FirstChildElement("Position");

    if (!subListElement)
    {
        LOGwar("light->Position of ambient light defined");
        return;
    }

    float pos_x, pos_y, pos_z;

    XMLCheckAttribution(subListElement->QueryFloatAttribute("x", &pos_x));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("y", &pos_y));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("z", &pos_z));

    light->setPosition(pos_x, pos_y, pos_z);
}


void LightSourceParser::setLightDirection(tinyxml2::XMLElement* lightElement)
{
    tinyxml2::XMLElement* subListElement = lightElement->FirstChildElement("Direction");

    if (!subListElement)
    {
        LOGwar("light->Direction of ambient light defined");
        return;
    }

    float dir_x, dir_y, dir_z;

    XMLCheckAttribution(subListElement->QueryFloatAttribute("x", &dir_x));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("y", &dir_y));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("z", &dir_z));

    light->setDirection(dir_x, dir_y, dir_z);
}


void LightSourceParser::setLightVecA(tinyxml2::XMLElement* lightElement)
{
    tinyxml2::XMLElement* subListElement = lightElement->FirstChildElement("VecA");

    if (!subListElement)
    {
        LOGwar("light->VecA of ambient light defined");
        return;
    }

    float vecA_x, vecA_y, vecA_z;

    XMLCheckAttribution(subListElement->QueryFloatAttribute("x", &vecA_x));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("y", &vecA_y));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("z", &vecA_z));

    light->setVecA(vecA_x, vecA_y, vecA_z);
}


void LightSourceParser::setLightVecB(tinyxml2::XMLElement* lightElement)
{
    tinyxml2::XMLElement* subListElement = lightElement->FirstChildElement("VecB");

    if (!subListElement)
    {
        LOGwar("light->VecB of ambient light defined");
        return;
    }

    float vecB_x, vecB_y, vecB_z;

    XMLCheckAttribution(subListElement->QueryFloatAttribute("x", &vecB_x));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("y", &vecB_y));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("z", &vecB_z));

    light->setVecB(vecB_x, vecB_y, vecB_z);
}


void LightSourceParser::setLightAttenuation(tinyxml2::XMLElement* lightElement)
{
    tinyxml2::XMLElement* subListElement = lightElement->FirstChildElement("Attenuation");

    if (!subListElement)
    {
        LOGwar("light->Attenuation of ambient light defined");
        return;
    }

    float constantAtt, linearAtt, quadraticAtt;

    XMLCheckAttribution(subListElement->QueryFloatAttribute("x", &constantAtt));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("y", &linearAtt));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("z", &quadraticAtt));

    light->setConstantAttenuation(constantAtt);
    light->setLinearAttenuation(linearAtt);
    light->setQuadraticAttenuation(quadraticAtt);
}


void LightSourceParser::setLightMaterialAttributes(tinyxml2::XMLElement* lightElement)
{
    tinyxml2::XMLElement* subListElement = lightElement->FirstChildElement("Material");

    if (!subListElement)
    {
        LOGwar("Light.Material not defined");
        return;
    }

    setLightAmbient(subListElement);
    setLightSpecular(subListElement);
    setLightDiffuse(subListElement);
}


void LightSourceParser::setLightAmbient(tinyxml2::XMLElement* lightElement)
{
    tinyxml2::XMLElement* subListElement = lightElement->FirstChildElement("Ambient");

    if (!subListElement)
    {
        LOGwar("Light.Ambient not defined");
        return;
    }

    float ka_r, ka_g, ka_b;

    XMLCheckAttribution(subListElement->QueryFloatAttribute("r", &ka_r));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("g", &ka_g));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("b", &ka_b));

    light->setAmbient(ka_r, ka_g, ka_b);
}


void LightSourceParser::setLightSpecular(tinyxml2::XMLElement* lightElement)
{
    tinyxml2::XMLElement* subListElement = lightElement->FirstChildElement("Specular");

    if (!subListElement)
    {
        LOGwar("Light.Specular not defined");
        return;
    }

    float ks_r, ks_g, ks_b;

    XMLCheckAttribution(subListElement->QueryFloatAttribute("r", &ks_r));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("g", &ks_g));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("b", &ks_b));

    light->setSpecular(ks_r, ks_g, ks_b);
}


void LightSourceParser::setLightDiffuse(tinyxml2::XMLElement* lightElement)
{
    tinyxml2::XMLElement* subListElement = lightElement->FirstChildElement("Diffuse");

    if (!subListElement)
    {
        LOGwar("Light.Diffuse not defined");
        return;
    }

    float kd_r, kd_g, kd_b;

    XMLCheckAttribution(subListElement->QueryFloatAttribute("r", &kd_r));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("g", &kd_g));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("b", &kd_b));

    light->setDiffuse(kd_r, kd_g, kd_b);
}
