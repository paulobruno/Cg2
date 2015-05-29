#include "RaycastingScene.h"


RaycastingScene::RaycastingScene()
{
    image.newImage("teste.png", width, height);
}


void RaycastingScene::render()
{
    float angle = perspective.getFieldOfView();
    float aspectRatio = (float)width / (float)height;

    float h = 2 * perspective.getNear() * tan(M_PI*angle / 360.0f);
    float w = h * aspectRatio;

    float delay_x = w / (float)width;
    float delay_y = h / (float)height;

    float znear = -perspective.getNear();


    for (unsigned int i = 0; i < height; ++i)
    {
        for (unsigned int j = 0; j < width; ++j)
        {
            float x = (-w / 2.0f) + (delay_x / 2.0) + ((float)j * delay_x);
            float y = (-h / 2.0f) + (delay_y / 2.0) + ((float)i * delay_y);

            Position3d cameraRayDirection(x, y, znear);

            Position3d worldRayDirection = camera.getEye() - camera.camToWorld(cameraRayDirection);
            worldRayDirection.normalize();

            ColorRgba color;

            for (unsigned int i = 0; i < objects.size(); ++i)
            {
                /*Position3d* interception = objects[i].interceptedWithRay(camera.getEye(), worldRayDirection);

                // se interceptou
                if (interception)
                {
                    color = calculateColor(objects[i], *interception);
                    break;
                }*/
            }

            color = calculateColor(Object(), Position3d());

            image.setPixel(j, i, color);
        }
    }

    image.saveImage();
}


ColorRgba RaycastingScene::calculateColor(Object object, Position3d position)
{
    return ColorRgba(1.0f, 1.0f, 0.0f);
}
