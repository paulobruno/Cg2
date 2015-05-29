#ifndef SCENE_H
#define SCENE_H


#include <cstdlib>
#include <vector>

#include "Camera.h"
#include "LightSource.h"
#include "Object.h"
#include "SceneXmlLoader.h"
#include "Perspective.h"


class Scene
{
    public:

        explicit Scene();

        bool loadXml(const char* filename);
        bool saveXml(const char* filename);


    protected:

        unsigned int width, height;
        Camera camera;
        SceneXmlLoader loader;
        Perspective perspective;

        LightSource lightAmbient;
        std::vector<LightSource*> lights;
        std::vector<Object*> objects;
};


#endif // SCENE_H
