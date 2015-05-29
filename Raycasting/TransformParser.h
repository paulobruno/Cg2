#ifndef TRANSFORMPARSER_H
#define TRANSFORMPARSER_H


#include "log.h"
#include "tinyxml2.h"
#include "Transform.h"
#include "Position3d.h"


class TransformParser
{
    public:

        TransformParser() {}
        ~TransformParser() {}

        TransformParser(const TransformParser& other)
            : transform(other.transform)
        {}

        TransformParser& operator= (const TransformParser& other)
        {
            if (this != &other)
            {
                transform = other.transform;
            }

            return *this;
        }


        Transform parse(tinyxml2::XMLElement* parent);


    private:

        Transform transform;


        void parseTransformPosition(tinyxml2::XMLElement* transformElement);
        void parseTransformRotation(tinyxml2::XMLElement* transformElement);
        void parseTransformScale(tinyxml2::XMLElement* transformElement);
};


#endif // TRANSFORMPARSER_H
