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
#include "BoundingBox.h"

#include <QImage>


class Scene
{
    public:

        explicit Scene();
        virtual ~Scene();

        void loadXml(const char* filename);
        void saveXml(const char* filename);

        void activateTexture(QImage textureImage) {texture = textureImage; hasTexture = true;}

        void updateSuperSampling(unsigned int subdivisions) {samples = subdivisions;}
        void activateSuperSampling(bool active) {hasSuperSampling = active;}

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

        bool hasSuperSampling = false;
        unsigned int samples = 2;

        QImage texture;
        bool hasTexture = false;

        BoundingBox rootBoundingBox;


        void createBoundingBox();
};


#endif // SCENE_H
