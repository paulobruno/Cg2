#ifndef MATERIALPARSER_H
#define MATERIALPARSER_H


#include "Material.h"
#include "ColorRgba.h"
#include "tinyxml2.h"


class MaterialParser
{
    public:

        MaterialParser() {}
        ~MaterialParser() {}

        MaterialParser(const MaterialParser& other)
            : material(other.material)
        {}

        MaterialParser& operator= (const MaterialParser& other)
        {
            if (this != &other)
            {
                material = other.material;
            }

            return *this;
        }

        Material parse(tinyxml2::XMLNode* materialNode);


    private:

        Material material;


        void parseMaterialReflection(tinyxml2::XMLElement* materialElement);
        void parseMaterialGlossyResflection(tinyxml2::XMLElement* materialElement);
        void parseMaterialShininess(tinyxml2::XMLElement* materialElement);
        void parseMaterialRefraction(tinyxml2::XMLElement* materialElement);
        void parseMaterialGlossyRefraction(tinyxml2::XMLElement* materialElement);
        void parseMaterialAmbient(tinyxml2::XMLElement* materialElement);
        void parseMaterialSpecular(tinyxml2::XMLElement* materialElement);
        void parseMaterialDiffuse(tinyxml2::XMLElement* materialElement);
};


#endif // MATERIALPARSER_H
