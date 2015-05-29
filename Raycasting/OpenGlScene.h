#ifndef OPENGLSCENE_H
#define OPENGLSCENE_H


#include "Scene.h"

#include <string>


class OpenGlScene
{
    public:

        OpenGlScene();


        void loadScene(const char *filename);


    private:

        Scene* scene;
};


#endif // OPENGLSCENE_H
