#ifndef PERSPECTIVEPARSER_H
#define PERSPECTIVEPARSER_H


#include "log.h"
#include "Perspective.h"
#include "tinyxml2.h"


class PerspectiveParser
{
    public:

        PerspectiveParser() {}
        ~PerspectiveParser() {}

        PerspectiveParser(const PerspectiveParser& other)
            : perspective(other.perspective)
        {}

        PerspectiveParser& operator= (const PerspectiveParser& other)
        {
            if (this != &other)
            {
                perspective = other.perspective;
            }

            return *this;
        }


        Perspective parse(tinyxml2::XMLNode* parent);


    private:

        Perspective perspective;
};


#endif // PERSPECTIVEPARSER_H
