#ifndef OBJECTSPARSER_H
#define OBJECTSPARSER_H


#include "log.h"
#include "Object.h"
#include "tinyxml2.h"

#include "ObjectPropertiesParser.h"
#include "ObjectEffectsParser.h"
#include "TransformParser.h"
#include "MaterialParser.h"

#include "Sphere.h"
#include "Cube.h"
#include "Cylinder.h"

#include <vector>


class ObjectsParser
{
    public:

        ObjectsParser() {}
        ~ObjectsParser() {}

        ObjectsParser(const ObjectsParser& other)
            : objects(other.objects)
        {}

        ObjectsParser& operator= (const ObjectsParser& other)
        {
            if (this != &other)
            {
                objects = other.objects;
            }

            return *this;
        }


        std::vector<Object*> parse(tinyxml2::XMLNode* parent);


    private:

        std::vector<Object*> objects;


        Object* parseObject(tinyxml2::XMLElement* objectElement);
};


#endif // OBJECTSPARSER_H
