#include "MaterialParser.h"


Material MaterialParser::parse(tinyxml2::XMLNode *materialNode)
{
    tinyxml2::XMLElement* materialElement = materialNode->FirstChildElement("Material");

    if (!materialElement)
    {
        LOGwar("Object.Material not defined");
    }
    else
    {
        parseMaterialGlossyResflection(materialElement);
        parseMaterialReflection(materialElement);
        parseMaterialShininess(materialElement);
        parseMaterialGlossyRefraction(materialElement);
        parseMaterialRefraction(materialElement);
        parseMaterialAmbient(materialElement);
        parseMaterialSpecular(materialElement);
        parseMaterialDiffuse(materialElement);
    }

    return material;
}


void MaterialParser::parseMaterialReflection(tinyxml2::XMLElement* materialElement)
{
    float reflection = 0.0f;

    XMLCheckAttribution(materialElement->QueryFloatAttribute("Reflection", &reflection));

    material.updateReflection(reflection);
}


void MaterialParser::parseMaterialGlossyResflection(tinyxml2::XMLElement* materialElement)
{
    float glossyReflection = 0.0f;

    XMLCheckAttribution(materialElement->QueryFloatAttribute("GLossyReflection", &glossyReflection));

    material.updateGlossyReflection(glossyReflection);
}


void MaterialParser::parseMaterialShininess(tinyxml2::XMLElement* materialElement)
{
    float shininess = 0.4f;

    XMLCheckAttribution(materialElement->QueryFloatAttribute("Shininess", &shininess));

    material.updateShininess(shininess * 128.0f);
}


void MaterialParser::parseMaterialRefraction(tinyxml2::XMLElement* materialElement)
{
    float refraction = 0.0f;

    XMLCheckAttribution(materialElement->QueryFloatAttribute("Refraction", &refraction));

    material.updateRefraction(refraction);
}


void MaterialParser::parseMaterialGlossyRefraction(tinyxml2::XMLElement* materialElement)
{
    float glossyRefraction = 0.0f;

    XMLCheckAttribution(materialElement->QueryFloatAttribute("GLossyRefraction", &glossyRefraction));

    material.updateGlossyRefraction(glossyRefraction);
}


void MaterialParser::parseMaterialAmbient(tinyxml2::XMLElement* materialElement)
{
   tinyxml2::XMLElement* subListElement = materialElement->FirstChildElement("Ambient");

   if (!subListElement)
   {
       LOGwar("Material.Ambient not defined");
       return;
   }

   float ka_r, ka_g, ka_b;

   XMLCheckAttribution(subListElement->QueryFloatAttribute("r", &ka_r));
   XMLCheckAttribution(subListElement->QueryFloatAttribute("g", &ka_g));
   XMLCheckAttribution(subListElement->QueryFloatAttribute("b", &ka_b));

   material.updateKa(ColorRgba(ka_r, ka_g, ka_b));
}


void MaterialParser::parseMaterialSpecular(tinyxml2::XMLElement* materialElement)
{
    tinyxml2::XMLElement* subListElement = materialElement->FirstChildElement("Specular");

    if (!subListElement)
    {
        LOGwar("Material.Specular not defined");
        return;
    }

    float ks_r, ks_g, ks_b;

    XMLCheckAttribution(subListElement->QueryFloatAttribute("r", &ks_r));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("g", &ks_g));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("b", &ks_b));

    material.updateKs(ColorRgba(ks_r, ks_g, ks_b));
}


void MaterialParser::parseMaterialDiffuse(tinyxml2::XMLElement* materialElement)
{
    tinyxml2::XMLElement* subListElement = materialElement->FirstChildElement("Diffuse");

    if (!subListElement)
    {
        LOGwar("Material.Diffuse not defined");
        return;
    }

    float kd_r, kd_g, kd_b;

    XMLCheckAttribution(subListElement->QueryFloatAttribute("r", &kd_r));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("g", &kd_g));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("b", &kd_b));

    material.updateKd(ColorRgba(kd_r, kd_g, kd_b));
}
