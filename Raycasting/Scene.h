#ifndef SCENE_H
#define SCENE_H


#include <cstdlib>
#include <vector>

#include "Camera.h"
#include "LightSource.h"
#include "Object.h"
#include "SceneXmlLoader.h"


class Scene
{
    public:

        explicit Scene();

        bool loadXml(const char* filename);
        bool saveXml(const char* filename);


    private:

        unsigned int width, height;
        Camera camera;
        SceneXmlLoader loader;

        LightSource lightAmbient;
        std::vector<LightSource*> lights;
        std::vector<Object*> objects;
};


#endif // SCENE_H
