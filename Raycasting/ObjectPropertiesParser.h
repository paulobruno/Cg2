#ifndef OBJECTPROPERTIESPARSER_H
#define OBJECTPROPERTIESPARSER_H


#include "log.h"
#include "tinyxml2.h"
#include "ObjectProperties.h"


class ObjectPropertiesParser
{
    public:

        ObjectPropertiesParser() {}
        ~ObjectPropertiesParser() {}

        ObjectPropertiesParser(const ObjectPropertiesParser& other)
            : properties(other.properties)
        {}

        ObjectPropertiesParser& operator= (const ObjectPropertiesParser& other)
        {
            if (this != &other)
            {
                properties = other.properties;
            }

            return *this;
        }


        ObjectProperties parse(tinyxml2::XMLElement* parent);


    private:

        ObjectProperties properties;


        void parseObjectPropertiesType(tinyxml2::XMLElement* objectPropertiesElement);
        void parseObjectPropertiesEnabled(tinyxml2::XMLElement* objectPropertiesElement);
        void parseObjectPropertiesName(tinyxml2::XMLElement* objectPropertiesElement);
        void parseObjectPropertiesTexture(tinyxml2::XMLElement* objectPropertiesElement);
        void parseObjectPropertiesBump(tinyxml2::XMLElement* objectPropertiesElement);
};


#endif // OBJECTPROPERTIESPARSER_H
