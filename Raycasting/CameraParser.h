#ifndef CAMERAPARSER_H
#define CAMERAPARSER_H


#include "log.h"
#include "tinyxml2.h"
#include "Camera.h"


class CameraParser
{
    public:

        CameraParser() {}
        ~CameraParser() {}

        CameraParser(const CameraParser& other)
            : camera(other.camera)
        {}

        CameraParser& operator= (const CameraParser& other)
        {
            if (this != &other)
            {
                camera = other.camera;
            }

            return *this;
        }


        Camera parse(tinyxml2::XMLNode* parent);


    private:

        Camera camera;


        void parseEyeAttributes(tinyxml2::XMLElement* cameraElement);
        void parseLookAtAttributes(tinyxml2::XMLElement* cameraElement);
        void parseViewUpAttributes(tinyxml2::XMLElement* cameraElement);
};


#endif // CAMERAPARSER_H
