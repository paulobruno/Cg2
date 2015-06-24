#ifndef SCENE_H
#define SCENE_H


#include <cstdlib>
#include <vector>

#include "Camera.h"
#include "LightSource.h"
#include "Object.h"
#include "ColorRgba.h"
#include "SceneXmlLoader.h"
#include "Perspective.h"


class Scene
{
    public:

        explicit Scene();

        void loadXml(const char* filename);
        void saveXml(const char* filename);

        void changeBackgroundColor(double r, double g, double b) {backgroundColor.setColor(r, g, b);}


    protected:

        ColorRgba backgroundColor;
        unsigned int width, height;
        Camera camera;
        SceneXmlLoader loader;
        Perspective perspective;

        LightSource lightAmbient;
        std::vector<LightSource*> lights;
        std::vector<Object*> objects;
};


#endif // SCENE_H
