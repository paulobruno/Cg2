#ifndef SCENEXMLLOADER_H
#define SCENEXMLLOADER_H


#include <cstdlib>
#include <vector>

#include "Camera.h"
#include "LightSource.h"
#include "Object.h"
#include "tinyxml2.h"

#include "EffectsParser.h"
#include "PerspectiveParser.h"
#include "CameraParser.h"
#include "ObjectsParser.h"
#include "LightsParser.h"


class SceneXmlLoader
{
    public:

        SceneXmlLoader();

        bool loadXml(const char* filename);
        bool saveXml(const char* filename);


    private:

        unsigned int width, height;
        Camera camera;
        Effects effects;
        Perspective perspective;

        std::vector<LightSource> lights;
        std::vector<Object> objects;

        EffectsParser effectsParser;
        PerspectiveParser perspectiveParser;
        CameraParser cameraParser;
        ObjectsParser objectsParser;
        LightsParser lightsParser;



        bool readXml(tinyxml2::XMLDocument document);
        bool getRoot(tinyxml2::XMLDocument document);
        bool readFromRoot(tinyxml2::XMLNode* root);
};


#endif // SCENEXMLLOADER_H
