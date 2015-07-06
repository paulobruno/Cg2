#include "Scene.h"


Scene::Scene()
{
    backgroundColor = ColorRgba(0.0f, 0.0f, 0.0f);
    width = 640;
    height = 480;
    camera = Camera();
    loader = SceneXmlLoader();
    perspective = Perspective();
}


Scene::~Scene()
{
    while (!lights.empty())
    {
        lights.pop_back();
    }
    lights.clear();

    while (!objects.empty())
    {
        objects.pop_back();
    }
    objects.clear();
}


void Scene::loadXml(const char* filename)
{
    loader.loadXml(filename);


    width = loader.getWidth();
    height = loader.getHeight();
    camera = loader.getCamera();
    perspective = loader.getPerspective();

    lights = loader.getLights();
    objects = loader.getObjects();


    createBoundingBox();
}


void Scene::saveXml(const char* filename)
{
    loader.saveXml(filename);
}


void Scene::createBoundingBox()
{
    Transform transform;

    float scaleX = 2.0f, scaleY = 2.0f, scaleZ = 2.0f;

    for (unsigned int k = 0; k < objects.size(); ++k)
    {
        float p_x = objects[k]->getTransform().getPosition().get_x();
        float p_y = objects[k]->getTransform().getPosition().get_y();
        float p_z = objects[k]->getTransform().getPosition().get_z();

        float s_x = objects[k]->getTransform().getScale().get_x();
        float s_y = objects[k]->getTransform().getScale().get_y();
        float s_z = objects[k]->getTransform().getScale().get_z();

        LOG("p_y: " << p_y << "\ts_y: " << s_y);

        if (-1.0f * ( p_x - s_x ) > scaleX)
        {
            scaleX = -1.0f * ( p_x - s_x );
        }
        if (( p_x + s_x ) > scaleX)
        {
            scaleX = p_x + s_x;
        }

        if (-1.0f * ( p_y - s_y ) > scaleY)
        {
            scaleY = -1.0f * ( p_y - s_y );
        }
        if (( p_y + s_y ) > scaleY)
        {
            scaleY = p_y + s_y;
        }

        if (-1.0f * ( p_z - s_z ) > scaleZ)
        {
            scaleZ = -1.0f * ( p_z - s_z );
        }
        if (( p_z + s_z ) > scaleZ)
        {
            scaleZ = p_z + s_z;
        }
    }

    transform.setScale(Position3d(scaleX, scaleY, scaleZ));

    LOG("s_x: " << scaleX << "\ts_y: " << scaleY << "\ts_z: " << scaleZ);

    rootBoundingBox.updateTransform(transform);
}
