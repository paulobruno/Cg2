#include "OpenGlScene.h"

OpenGlScene::OpenGlScene()
{
}


void OpenGlScene::loadScene(const char* filename)
{
    scene->loadXml(filename);
}
