#ifndef SCENE_H
#define SCENE_H


#include <cstdlib>
#include <vector>

#include "tinyxml2.h"
#include "Camera.h"
#include "LightSource.h"
#include "Object.h"

using namespace tinyxml2;


enum DefinedElements
{
    EFFECTS = 0,
    PERSPECTIVE,
    CAMERA,
    OBJECTS,
    LIGHTS,
    WRONG_ELEMENT
};


class Scene
{
    public:

        explicit Scene();

        bool loadXml(const char* filename);
        bool saveXml(const char* filename);


    private:

        unsigned int width, height;
        Camera camera;

        LightSource lightAmbient;
        std::vector<LightSource*> lights;
        std::vector<Object*> objects;


        /*void setEffects(float radius, float focalLenght, float depthOfField);
        void setPerspective(float fov, float zNear, float zFar, unsigned int width, unsigned int height);
        void setCamera(float eye_x,    float eye_y,    float eye_z,
                       float lookAt_x, float lookAt_y, float lookAt_z,
                       float viewUp_x, float viewUp_y, float viewUp_z);*/

        void addLightSource(LightSource light);
        void addObject(Object obj);



        bool readXml(XMLDocument document);
        bool getRoot(XMLDocument document);
        bool readFromRoot(XMLNode* root);
        void readElement(XMLNode* parent, const char* elementName);
        void setAttributes(XMLElement* element, const char* elementName);
        DefinedElements definedElementFromName(const char* elementName);

        void setEffectsAttributes(XMLElement* effectsElement);
        void setEffects(float radius, float focalLenght, float depthOfField);
        void setPerspectiveAttributes(XMLElement* perspectiveElement);
        void setPerspective(float fov, float zNear, float zFar, unsigned int width, unsigned int height);
        void setCameraAttributes(XMLElement* cameraElement);
        void setCameraEyeAttributes(XMLElement* cameraElement);
        void setCameraLookAtAttributes(XMLElement* cameraElement);
        void setCameraViewUpAttributes(XMLElement* cameraElement);
        void setObjectsGroup(XMLElement* objectsGroup);
        void setObjectAttributes(XMLElement* objectElement);
        void setObjectType(XMLElement* objectElement);
        void setObjectEnabled(XMLElement* objectElement);
        void setObjectName(XMLElement* objectElement);
        void setObjectTexture(XMLElement* objectElement);
        void setObjectBump(XMLElement* objectElement);
        void setObjectPosition(XMLElement *objectElement);
        void setObjectRotation(XMLElement* objectElement);
        void setObjectScale(XMLElement* objectElement);
        void setObjectMaterialAttributes(XMLElement* objectElement);
        void setMaterialReflection(XMLElement* materialElement);
        void setMaterialGlossyResflection(XMLElement* materialElement);
        void setMaterialShininess(XMLElement* materialElement);
        void setMaterialRefraction(XMLElement* materialElement);
        void setMaterialGlossyRefraction(XMLElement* materialElement);
        void setMaterialAmbient(XMLElement* materialElement);
        void setMaterialSpecular(XMLElement* materialElement);
        void setMaterialDiffuse(XMLElement* materialElement);
        void setObjectEffectsAttributes(XMLElement* objectElement);
        void setEffectsMotion(XMLElement* effectsElement);
        void setEffectsTranslate(XMLElement* effectsElement);
        void setEffectsRotate(XMLElement* effectsElement);
        void setLightsGroup(XMLElement* lightsElement);
        void setAmbientLight(XMLElement* lightElement);
        void setLightAmbientType(XMLElement* lightElement);
        void setLightAttributes(XMLElement* lightElement);
        void setLightType(XMLElement* lightElement);
        void setLightExponent(XMLElement* lightElement);
        void setLightEnable(XMLElement* lightElement);
        void setLightName(XMLElement* lightElement);
        void setLightAngleInner(XMLElement* lightElement);
        void setLightAngle(XMLElement* lightElement);
        void setLightPosition(XMLElement* lightElement);
        void setLightDirection(XMLElement* lightElement);
        void setLightVecA(XMLElement* lightElement);
        void setLightVecB(XMLElement* lightElement);
        void setLightAttenuation(XMLElement* lightElement);
        void setLightMaterialAttributes(XMLElement* lightElement);
};


#endif // SCENE_H
