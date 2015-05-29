#include "Scene.h"


Scene::Scene()
{
    width = 640;
    height = 480;
    camera = Camera();
    loader = SceneXmlLoader();
    perspective = Perspective();
}


bool Scene::loadXml(const char* filename)
{
    loader.loadXml(filename);
}


bool Scene::saveXml(const char* filename)
{
    loader.saveXml(filename);
}
