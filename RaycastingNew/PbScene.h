#ifndef PBSCENE_H
#define PBSCENE_H


#include <cstdlib>
#include <vector>

#include "tinyxml2.h"
#include "PbCamera.h"
#include "PbLightSource.h"
#include "PbObject.h"


class PbScene
{
    public:

        explicit PbScene();

        bool loadXml(const char* filename);
        bool saveXml(const char* filename);


    private:

        unsigned int width, height;
        PbCamera camera;

        PbLightSource lightAmbient;
        std::vector<PbLightSource*> lights;
        std::vector<PbObject*> objects;


        void setEffects(float radius, float focalLenght, float depthOfField);
        void setPerspective(float fov, float zNear, float zFar, unsigned int width, unsigned int height);
        void setCamera(float eye_x,    float eye_y,    float eye_z,
                       float lookAt_x, float lookAt_y, float lookAt_z,
                       float viewUp_x, float viewUp_y, float viewUp_z);

        void addLightSource(PbLightSource light);
        void addObject(PbObject obj);
};

#endif // PBSCENE_H
