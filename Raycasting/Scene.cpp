#include "Scene.h"


Scene::Scene()
{}


bool Scene::loadXml(const char* filename)
{
    loader.loadXml(filename);
}


bool Scene::saveXml(const char* filename)
{
    loader.saveXml(filename);
}
