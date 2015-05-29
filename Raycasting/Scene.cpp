#include "Scene.h"


#ifndef XMLCheckResult
    #define XMLCheckResult(errorResult) if (errorResult != XML_SUCCESS) { LOGerr("Error: " << errorResult); }
#endif

#ifndef XMLCheckAttribution
    #define XMLCheckAttribution(attributionResult) if (attributionResult != XML_NO_ERROR) { LOGerr("Error: " << attributionResult); }
#endif

using namespace tinyxml2;


Scene::Scene()
{
}



bool Scene::loadXml(const char* filename)
{
    XMLDocument doc;


    XMLError result = doc.LoadFile(filename);
    XMLCheckResult(result);

    XMLNode* root = doc.FirstChildElement("Scene");

    if (!root)
    {
        LOGerr("Root not defined");
        return XML_ERROR_FILE_READ_ERROR;
    }

    return readFromRoot(root);
}


bool Scene::readFromRoot(XMLNode* root)
{
    if (!root)
    {
        LOGerr("root not received")
        return false;
    }

    readElement(root, "Effects");
    readElement(root, "Perspective");
    readElement(root, "Camera");
    readElement(root, "Objects");
    readElement(root, "Lights");

    LOG("success");
    return XML_SUCCESS;
}


void Scene::readElement(XMLNode* parent, const char* elementName)
{
    if (!parent)
    {
        LOGwar("Parent element not defined");
        return;
    }

    XMLElement* element = parent->FirstChildElement(elementName);

    if (!element)
    {
        LOGwar(elementName << " not defined");
        return;
    }

    setAttributes(element, elementName);
}


void Scene::setAttributes(XMLElement* element, const char* elementName)
{
    if (!element)
    {
        LOGwar("Element not defined");
        return;
    }

    DefinedElements type = definedElementFromName(elementName);

    switch (type)
    {
        case EFFECTS:
            setEffectsAttributes(element);
            break;

        case PERSPECTIVE:
            setPerspectiveAttributes(element);
            break;

        case CAMERA:
            setCameraAttributes(element);
            break;

        case OBJECTS:
            setObjectsGroup(element);
            break;

        case LIGHTS:
            setLightsGroup(element);
            break;

        default:
            LOGwar("Element name does not exists");
            break;
    }
}


DefinedElements Scene::definedElementFromName(const char* elementName)
{
    if ("Effects" == elementName)
    {
        return EFFECTS;
    }

    if ("Perspective" == elementName)
    {
        return PERSPECTIVE;
    }

    if ("Camera" == elementName)
    {
        return CAMERA;
    }

    if ("Objects" == elementName)
    {
        return OBJECTS;
    }

    if ("Lights" == elementName)
    {
        return LIGHTS;
    }

    return WRONG_ELEMENT;
}


void Scene::setEffectsAttributes(XMLElement* effectsElement)
{
    float radius = 0.0f, focalLength = 0.0f, dof = 0.0f;

    XMLCheckAttribution(effectsElement->QueryFloatAttribute("Radius", &radius));
    XMLCheckAttribution(effectsElement->QueryFloatAttribute("FocalLength", &focalLength));
    XMLCheckAttribution(effectsElement->QueryFloatAttribute("DOF", &dof));

    setEffects(radius, focalLength, dof);
}


void Scene::setEffects(float radius, float focalLenght, float depthOfField)
{

}


void Scene::setPerspectiveAttributes(XMLElement* perspectiveElement)
{
    unsigned int width = 640, height = 480;
    float far = 120000.0f, near = 0.01f, fov = 45.0f;

    XMLCheckAttribution(perspectiveElement->QueryFloatAttribute("Far", &far));
    XMLCheckAttribution(perspectiveElement->QueryFloatAttribute("Near", &near));
    XMLCheckAttribution(perspectiveElement->QueryUnsignedAttribute("Width", &width));
    XMLCheckAttribution(perspectiveElement->QueryFloatAttribute("Angle", &fov));
    XMLCheckAttribution(perspectiveElement->QueryUnsignedAttribute("Height", &height));

    setPerspective(fov, near, far, width, height);
}


void Scene::setPerspective(float fov, float zNear, float zFar, unsigned int width, unsigned int height)
{

}


void Scene::setCameraAttributes(XMLElement* cameraElement)
{
    setCameraEyeAttributes(cameraElement);
    setCameraLookAtAttributes(cameraElement);
    setCameraViewUpAttributes(cameraElement);
}


void Scene::setCameraEyeAttributes(XMLElement* cameraElement)
{
    XMLElement* eyeAttribute = cameraElement->FirstChildElement("Eye");

    if (!eyeAttribute)
    {
        LOGwar("Camera.Eye not defined");
        return;
    }

    float eye_x = 0.0f,    eye_y = 0.0f,    eye_z = -1.0f;

    XMLCheckAttribution(eyeAttribute->QueryFloatAttribute("x", &eye_x));
    XMLCheckAttribution(eyeAttribute->QueryFloatAttribute("y", &eye_y));
    XMLCheckAttribution(eyeAttribute->QueryFloatAttribute("z", &eye_z));

    camera.updateEye(eye_x, eye_y, eye_z);
}


void Scene::setCameraLookAtAttributes(XMLElement* cameraElement)
{
    XMLElement* lookAtAttribute = cameraElement->FirstChildElement("At");

    if (!lookAtAttribute)
    {
        LOGwar("Camera.At not defined");
        return;
    }

    float lookAt_x = 0.0f, lookAt_y = 0.0f, lookAt_z = 0.0f;

    XMLCheckAttribution(lookAtAttribute->QueryFloatAttribute("x", &lookAt_x));
    XMLCheckAttribution(lookAtAttribute->QueryFloatAttribute("y", &lookAt_y));
    XMLCheckAttribution(lookAtAttribute->QueryFloatAttribute("z", &lookAt_z));

    camera.updateLookAt(lookAt_x, lookAt_y, lookAt_z);
}


void Scene::setCameraViewUpAttributes(XMLElement* cameraElement)
{
    XMLElement* viewUpAttribute = cameraElement->FirstChildElement("Up");

    if (!viewUpAttribute)
    {
        LOGwar("Camera.Up not defined");
        return;
    }

    float viewUp_x = 0.0f, viewUp_y = 1.0f, viewUp_z = -1.0f;

    XMLCheckAttribution(viewUpAttribute->QueryFloatAttribute("x", &viewUp_x));
    XMLCheckAttribution(viewUpAttribute->QueryFloatAttribute("y", &viewUp_y));
    XMLCheckAttribution(viewUpAttribute->QueryFloatAttribute("z", &viewUp_z));

    camera.updateViewUp(viewUp_x, viewUp_y, viewUp_z);
}


void Scene::setObjectsGroup(XMLElement* objectsGroup)
{
    XMLElement* objectElement = objectsGroup->FirstChildElement("Object");

    while (objectElement)
    {
        setObjectAttributes(objectElement);

        objectElement = objectElement->NextSiblingElement("Object");
    }
}


void Scene::setObjectAttributes(XMLElement* objectElement)
{
    setObjectType(objectElement);
    setObjectEnabled(objectElement);
    setObjectName(objectElement);
    setObjectTexture(objectElement);
    setObjectBump(objectElement);
    setObjectPosition(objectElement);
    setObjectRotation(objectElement);
    setObjectScale(objectElement);

    setObjectMaterialAttributes(objectElement);
    setObjectEffectsAttributes(objectElement);
}


void Scene::setObjectType(XMLElement* objectElement)
{
    const char* objType = nullptr;

    objType = objectElement->Attribute("Type");

    if (!objType)
    {
        LOGerr("Object.Type string error");
        return;
    }
}


void Scene::setObjectEnabled(XMLElement* objectElement)
{
    bool enabled = false;

    XMLCheckAttribution(objectElement->QueryBoolAttribute("Enabled", &enabled));
}


void Scene::setObjectName(XMLElement* objectElement)
{
    const char* objName = nullptr;
    objName = objectElement->Attribute("Name");

    if (!objName)
    {
        LOGerr("Object.Name string error");
        return;
    }
}


void Scene::setObjectTexture(XMLElement* objectElement)
{
    const char* objTexture = nullptr;

    objTexture = objectElement->Attribute("Texture");

    if (!objTexture)
    {
        LOGerr("Object.Texture string error");
        return;
    }
}


void Scene::setObjectBump(XMLElement* objectElement)
{
    const char* objBump = nullptr;
    objBump = objectElement->Attribute("Bump");

    if (!objBump)
    {
        LOGerr("Object.Bump string error");
        return;
    }
}


void Scene::setObjectPosition(XMLElement* objectElement)
{
    XMLElement* subListElement = objectElement->FirstChildElement("Position");

    if (!subListElement)
    {
        LOGwar("Object.Position not defined");
        return;
    }

    float pos_x, pos_y, pos_z;

    XMLCheckAttribution(subListElement->QueryFloatAttribute("x", &pos_x));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("y", &pos_y));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("z", &pos_z));
}


void Scene::setObjectRotation(XMLElement* objectElement)
{
    XMLElement* subListElement = objectElement->FirstChildElement("Rotation");

    if (!subListElement)
    {
        LOGwar("Object.Rotation not defined");
        return;
    }

    float rot_x, rot_y, rot_z;

    XMLCheckAttribution(subListElement->QueryFloatAttribute("x", &rot_x));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("y", &rot_y));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("z", &rot_z));
}


void Scene::setObjectScale(XMLElement* objectElement)
{
    XMLElement* subListElement = objectElement->FirstChildElement("Scale");

    if (!subListElement)
    {
        LOGwar("Object.Scale not defined");
        return;
    }

    float scale_x, scale_y, scale_z;

    XMLCheckAttribution(subListElement->QueryFloatAttribute("x", &scale_x));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("y", &scale_y));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("z", &scale_z));
}

void Scene::setObjectMaterialAttributes(XMLElement* objectElement)
{
    XMLElement* subListElement = objectElement->FirstChildElement("Material");

    if (!subListElement)
    {
        LOGwar("Object.Material not defined");
        return;
    }

    setMaterialReflection(subListElement);
    setMaterialGlossyResflection(subListElement);
    setMaterialShininess(subListElement);
    setMaterialRefraction(subListElement);
    setMaterialGlossyRefraction(subListElement);
    setMaterialAmbient(subListElement);
    setMaterialSpecular(subListElement);
    setMaterialDiffuse(subListElement);
}


void Scene::setMaterialReflection(XMLElement* materialElement)
{
    float reflection = 0.0f;

    XMLCheckAttribution(materialElement->QueryFloatAttribute("Reflection", &reflection));
}


void Scene::setMaterialGlossyResflection(XMLElement* materialElement)
{
    float glossyReflection = 0.0f;

    XMLCheckAttribution(materialElement->QueryFloatAttribute("GLossyReflection", &glossyReflection));
}


void Scene::setMaterialShininess(XMLElement* materialElement)
{
    float shininess = 0.4f;

    XMLCheckAttribution(materialElement->QueryFloatAttribute("Shininess", &shininess));
}


void Scene::setMaterialRefraction(XMLElement* materialElement)
{
    float refraction = 0.0f;

    XMLCheckAttribution(materialElement->QueryFloatAttribute("Refraction", &refraction));
}


void Scene::setMaterialGlossyRefraction(XMLElement* materialElement)
{
    float glossyRefraction = 0.0f;

    XMLCheckAttribution(materialElement->QueryFloatAttribute("GLossyRefraction", &glossyRefraction));
}


void Scene::setMaterialAmbient(XMLElement* materialElement)
{
   XMLElement* subListElement = materialElement->FirstChildElement("Ambient");

   if (!subListElement)
   {
       LOGwar("Material.Ambient not defined");
       return;
   }

   float ka_r, ka_g, ka_b;

   XMLCheckAttribution(subListElement->QueryFloatAttribute("r", &ka_r));
   XMLCheckAttribution(subListElement->QueryFloatAttribute("g", &ka_g));
   XMLCheckAttribution(subListElement->QueryFloatAttribute("b", &ka_b));
}


void Scene::setMaterialSpecular(XMLElement* materialElement)
{
    XMLElement* subListElement = materialElement->FirstChildElement("Specular");

    if (!subListElement)
    {
        LOGwar("Material.Specular not defined");
        return;
    }

    float ks_r, ks_g, ks_b;

    XMLCheckAttribution(subListElement->QueryFloatAttribute("r", &ks_r));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("g", &ks_g));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("b", &ks_b));
}


void Scene::setMaterialDiffuse(XMLElement* materialElement)
{
    XMLElement* subListElement = materialElement->FirstChildElement("Diffuse");

    if (!subListElement)
    {
        LOGwar("Material.Diffuse not defined");
        return;
    }

    float kd_r, kd_g, kd_b;

    XMLCheckAttribution(subListElement->QueryFloatAttribute("r", &kd_r));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("g", &kd_g));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("b", &kd_b));
}


void Scene::setObjectEffectsAttributes(XMLElement* objectElement)
{
    XMLElement* subListElement = objectElement->FirstChildElement("Effects");

    if (!subListElement)
    {
        LOGwar("Object.Effects not defined");
        return;
    }

    setEffectsMotion(subListElement);
    setEffectsTranslate(subListElement);
    setEffectsRotate(subListElement);
}


void Scene::setEffectsMotion(XMLElement* effectsElement)
{
    bool motion = false;

    XMLCheckAttribution(effectsElement->QueryBoolAttribute("Motion", &motion));
}


void Scene::setEffectsTranslate(XMLElement* effectsElement)
{
    XMLElement* subListElement = effectsElement->FirstChildElement("Translate");

    if (!subListElement)
    {
        LOGwar("Object.Effects.Translate not defined");
        return;
    }

    float translate_x, translate_y, translate_z;

    XMLCheckAttribution(subListElement->QueryFloatAttribute("x", &translate_x));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("y", &translate_y));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("z", &translate_z));
}


void Scene::setEffectsRotate(XMLElement* effectsElement)
{
    XMLElement* subListElement = effectsElement->FirstChildElement("Rotate");

    if (!subListElement)
    {
        LOGwar("Object.Effects.Rotate not defined");
        return;
    }

    float rotate_x, rotate_y, rotate_z;

    XMLCheckAttribution(subListElement->QueryFloatAttribute("x", &rotate_x));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("y", &rotate_y));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("z", &rotate_z));
}


void Scene::setLightsGroup(XMLElement* lightsElement)
{
    XMLElement* lightElement = lightsElement->FirstChildElement("Light");

    // light ambient need
    if (!lightElement)
    {
        LOGwar("Ambient light not defined");
        return;
    }

    setAmbientLight(lightElement);

    lightElement = lightsElement->FirstChildElement("Light");

    while (lightElement)
    {
        setLightAttributes(lightElement);

        lightElement = lightsElement->NextSiblingElement("Light");
    }
}


void Scene::setAmbientLight(XMLElement* lightElement)
{
    setLightAmbientType(lightElement);

    setLightMaterialAttributes(lightElement);
}


void Scene::setLightAmbientType(XMLElement* lightElement)
{
    const char* lightType = nullptr;
    lightType = lightElement->Attribute("Type");

    if (!strcmp(lightType, "LIGHT_AMBIENT"))
    {
    }
    else
    {
        LOGerr("First light must be ambient");
        return;
    }
}


void Scene::setLightAttributes(XMLElement* lightElement)
{
    setLightType(lightElement);
    setLightExponent(lightElement);
    setLightEnable(lightElement);
    setLightName(lightElement);
    setLightAngleInner(lightElement);
    setLightAngle(lightElement);
    setLightPosition(lightElement);
    setLightDirection(lightElement);
    setLightVecA(lightElement);
    setLightVecB(lightElement);
    setLightAttenuation(lightElement);

    setLightMaterialAttributes(lightElement);
}

void Scene::setLightType(XMLElement* lightElement)
{
    const char* lightType = nullptr;
    lightType = lightElement->Attribute("Type");

    if (!lightType)
    {
        LOGerr("Light.Type string error");
        return;
    }
}

void Scene::setLightExponent(XMLElement* lightElement)
{
    float lightExponent = 0.0f;

    XMLCheckAttribution(lightElement->QueryFloatAttribute("Exponent", &lightExponent));
}


void Scene::setLightEnable(XMLElement* lightElement)
{
    bool lightEnable = true;

    XMLCheckAttribution(lightElement->QueryBoolAttribute("Enable", &lightEnable));
}


void Scene::setLightName(XMLElement* lightElement)
{
    const char* lightName = nullptr;
    lightName = lightElement->Attribute("Name");

    if (!lightName)
    {
        LOGerr("Light.Name string error");
        return;
    }
}


void Scene::setLightAngleInner(XMLElement* lightElement)
{
    float lightAngleInner = 0.0f;

    XMLCheckAttribution(lightElement->QueryFloatAttribute("AngleInner", &lightAngleInner));
}


void Scene::setLightAngle(XMLElement* lightElement)
{
    float lightAngle = 0.0f;

    XMLCheckAttribution(lightElement->QueryFloatAttribute("Angle", &lightAngle));
}


void Scene::setLightPosition(XMLElement* lightElement)
{

    XMLElement* subListElement = lightElement->FirstChildElement("Position");

    if (!subListElement)
    {
        LOGwar("Light.Position of ambient light defined");
        return;
    }

    float pos_x, pos_y, pos_z;

    XMLCheckAttribution(subListElement->QueryFloatAttribute("x", &pos_x));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("y", &pos_y));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("z", &pos_z));

    //lights .setPosition(pos_x, pos_y, pos_z);
}


void Scene::setLightDirection(XMLElement* lightElement)
{
    XMLElement* subListElement = lightElement->FirstChildElement("Direction");

    if (!subListElement)
    {
        LOGwar("Light.Direction of ambient light defined");
        return;
    }

    float dir_x, dir_y, dir_z;

    XMLCheckAttribution(subListElement->QueryFloatAttribute("x", &dir_x));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("y", &dir_y));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("z", &dir_z));

    //lights .setDirection(dir_x, dir_y, dir_z);
}


void Scene::setLightVecA(XMLElement* lightElement)
{
    XMLElement* subListElement = lightElement->FirstChildElement("VecA");

    if (!subListElement)
    {
        LOGwar("Light.VecA of ambient light defined");
        return;
    }

    float vecA_x, vecA_y, vecA_z;

    XMLCheckAttribution(subListElement->QueryFloatAttribute("x", &vecA_x));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("y", &vecA_y));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("z", &vecA_z));

    //lights .setVecA(vecA_x, vecA_y, vecA_z);
}


void Scene::setLightVecB(XMLElement* lightElement)
{
    XMLElement* subListElement = lightElement->FirstChildElement("VecB");

    if (!subListElement)
    {
        LOGwar("Light.VecB of ambient light defined");
        return;
    }

    float vecB_x, vecB_y, vecB_z;

    XMLCheckAttribution(subListElement->QueryFloatAttribute("x", &vecB_x));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("y", &vecB_y));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("z", &vecB_z));

    //lights .setVecB(vecB_x, vecB_y, vecB_z);
}


void Scene::setLightAttenuation(XMLElement* lightElement)
{
    XMLElement* subListElement = lightElement->FirstChildElement("Attenuation");

    if (!subListElement)
    {
        LOGwar("Light.Attenuation of ambient light defined");
        return;
    }

    float constantAtt, linearAtt, quadraticAtt;

    XMLCheckAttribution(subListElement->QueryFloatAttribute("x", &constantAtt));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("y", &linearAtt));
    XMLCheckAttribution(subListElement->QueryFloatAttribute("z", &quadraticAtt));

    //lights .setConstantAttenuation(constantAtt);
    //lights .setLinearAttenuation(linearAtt);
    //lights .setQuadraticAttenuation(quadraticAtt);
}


void Scene::setLightMaterialAttributes(XMLElement* lightElement)
{
    XMLElement* subListElement = lightElement->FirstChildElement("Material");

    if (!subListElement)
    {
        LOGwar("Light.Material not defined");
        return;
    }

    setMaterialAmbient(subListElement);
    setMaterialSpecular(subListElement);
    setMaterialDiffuse(subListElement);
}





bool Scene::saveXml(const char* filename)
{
    XMLDocument doc;

    XMLNode* root = doc.NewElement("Scene");
    doc.InsertFirstChild(root);


    XMLElement* element = doc.NewElement("Perspective");
    element->SetAttribute("Far", 120000.0f);
    element->SetAttribute("Near", 0.01f);
    element->SetAttribute("Width", width);
    element->SetAttribute("Angle", 60.0f);
    element->SetAttribute("Height", height);
    root->InsertEndChild(element);


    element = doc.NewElement("Camera");

    XMLElement* camElem = doc.NewElement("Eye");
    camElem->SetAttribute("x", camera.getEye_x());
    camElem->SetAttribute("y", camera.getEye_y());
    camElem->SetAttribute("z", camera.getEye_z());
    element->InsertEndChild(camElem);

    camElem = doc.NewElement("At");
    camElem->SetAttribute("x", camera.getLookAt_x());
    camElem->SetAttribute("y", camera.getLookAt_y());
    camElem->SetAttribute("z", camera.getLookAt_z());
    element->InsertEndChild(camElem);

    camElem = doc.NewElement("Up");
    camElem->SetAttribute("x", camera.getViewUp().get_x());
    camElem->SetAttribute("y", camera.getViewUp().get_y());
    camElem->SetAttribute("z", camera.getViewUp().get_z());
    element->InsertEndChild(camElem);

    root->InsertEndChild(element);


    element = doc.NewElement("Objects");

    for (unsigned int i = 0; i < objects.size(); ++i)
    {
        XMLElement* listElement;
        XMLElement* objAttribs;

        if (objects[i]->getId() != "OBJPLANE")
        {
            listElement = doc.NewElement("Object");
            listElement->SetAttribute("Type", objects[i]->getId().c_str());
            listElement->SetAttribute("Enabled", 1);
            listElement->SetAttribute("Name", objects[i]->getId().c_str());
            listElement->SetAttribute("Texture", "");
            listElement->SetAttribute("Bump", "");
            element->InsertEndChild(listElement);

            objAttribs = doc.NewElement("Position");
            objAttribs->SetAttribute("x", -1.0f*objects[i]->getCenter().get_x());
            objAttribs->SetAttribute("y", objects[i]->getCenter().get_y());
            objAttribs->SetAttribute("z", objects[i]->getCenter().get_z());
            listElement->InsertEndChild(objAttribs);

            objAttribs = doc.NewElement("Rotation");
            objAttribs->SetAttribute("x", 0);
            objAttribs->SetAttribute("y", 0);
            objAttribs->SetAttribute("z", 0);
            listElement->InsertEndChild(objAttribs);

            objAttribs = doc.NewElement("Scale");
            objAttribs->SetAttribute("x", objects[i]->getTransform().getScale().get_x());
            objAttribs->SetAttribute("y", objects[i]->getTransform().getScale().get_y());
            objAttribs->SetAttribute("z", objects[i]->getTransform().getScale().get_z());
            listElement->InsertEndChild(objAttribs);
        }/*
        else
        {
            char axis = objects[i]->getAxis();

            listElement = doc.NewElement("Object");
            listElement->SetAttribute("Type", "OBJCUBE");
            listElement->SetAttribute("Enabled", 1);
            listElement->SetAttribute("Name", objects[i]->getId()());
            listElement->SetAttribute("Texture", "");
            listElement->SetAttribute("Bump", "");
            element->InsertEndChild(listElement);

            switch (axis)
            {
                case 'x':
                    objAttribs = doc.NewElement("Position");
                    objAttribs->SetAttribute("x", -1.0f*objects[i]->getCenter().get_x() - 0.001);
                    objAttribs->SetAttribute("y", objects[i]->getCenter().get_y());
                    objAttribs->SetAttribute("z", objects[i]->getCenter().get_z());
                    listElement->InsertEndChild(objAttribs);

                    objAttribs = doc.NewElement("Rotation");
                    objAttribs->SetAttribute("x", 0);
                    objAttribs->SetAttribute("y", 0);
                    objAttribs->SetAttribute("z", 0);
                    listElement->InsertEndChild(objAttribs);

                    objAttribs = doc.NewElement("Scale");
                    objAttribs->SetAttribute("x", 0.001);
                    objAttribs->SetAttribute("y", 2*objects[i]->getTransform().getScale_y());
                    objAttribs->SetAttribute("z", 2*objects[i]->getTransform().getScale_z());
                    listElement->InsertEndChild(objAttribs);
                    break;

                case 'y':
                    objAttribs = doc.NewElement("Position");
                    objAttribs->SetAttribute("x", -1.0f*objects[i]->getCenter().get_x());
                    objAttribs->SetAttribute("y", objects[i]->getCenter().get_y() + 0.001);
                    objAttribs->SetAttribute("z", objects[i]->getCenter().get_z());
                    listElement->InsertEndChild(objAttribs);

                    objAttribs = doc.NewElement("Rotation");
                    objAttribs->SetAttribute("x", 0);
                    objAttribs->SetAttribute("y", 0);
                    objAttribs->SetAttribute("z", 0);
                    listElement->InsertEndChild(objAttribs);

                    objAttribs = doc.NewElement("Scale");
                    objAttribs->SetAttribute("x", 2*objects[i]->getTransform().getScale_x());
                    objAttribs->SetAttribute("y", 0.001);
                    objAttribs->SetAttribute("z", 2*objects[i]->getTransform().getScale_z());
                    listElement->InsertEndChild(objAttribs);
                    break;

                case 'z':
                    objAttribs = doc.NewElement("Position");
                    objAttribs->SetAttribute("x", -1.0f*objects[i]->getCenter().get_x());
                    objAttribs->SetAttribute("y", objects[i]->getCenter().get_y());
                    objAttribs->SetAttribute("z", objects[i]->getCenter().get_z() + 0.001);
                    listElement->InsertEndChild(objAttribs);

                    objAttribs = doc.NewElement("Rotation");
                    objAttribs->SetAttribute("x", 0);
                    objAttribs->SetAttribute("y", 0);
                    objAttribs->SetAttribute("z", 0);
                    listElement->InsertEndChild(objAttribs);

                    objAttribs = doc.NewElement("Scale");
                    objAttribs->SetAttribute("x", 2*objects[i]->getTransform().getScale_x());
                    objAttribs->SetAttribute("y", 2*objects[i]->getTransform().getScale_y());
                    objAttribs->SetAttribute("z", 0.001);
                    listElement->InsertEndChild(objAttribs);
                    break;

                default:
                    LOGerr("Erro, eixo do plano em desacordo");
                    break;
            }
        }*/

        objAttribs = doc.NewElement("Material");
        objAttribs->SetAttribute("Reflection", 0);
        objAttribs->SetAttribute("GLossyReflection", 0);
        objAttribs->SetAttribute("Shininess", objects[i]->getMaterial().getShininess()/128.0f);
        objAttribs->SetAttribute("Refraction", 0);
        objAttribs->SetAttribute("GLossyRefraction", 0);
        listElement->InsertEndChild(objAttribs);

        XMLElement* mtlAttribs = doc.NewElement("Ambient");
        mtlAttribs->SetAttribute("r", objects[i]->getMaterial().getKaR());
        mtlAttribs->SetAttribute("g", objects[i]->getMaterial().getKaG());
        mtlAttribs->SetAttribute("b", objects[i]->getMaterial().getKaB());
        objAttribs->InsertEndChild(mtlAttribs);

        mtlAttribs = doc.NewElement("Specular");
        mtlAttribs->SetAttribute("r", objects[i]->getMaterial().getKsR());
        mtlAttribs->SetAttribute("g", objects[i]->getMaterial().getKsG());
        mtlAttribs->SetAttribute("b", objects[i]->getMaterial().getKsB());
        objAttribs->InsertEndChild(mtlAttribs);

        mtlAttribs = doc.NewElement("Diffuse");
        mtlAttribs->SetAttribute("r", objects[i]->getMaterial().getKdR());
        mtlAttribs->SetAttribute("g", objects[i]->getMaterial().getKdG());
        mtlAttribs->SetAttribute("b", objects[i]->getMaterial().getKdB());
        objAttribs->InsertEndChild(mtlAttribs);

        objAttribs = doc.NewElement("Effects");
        objAttribs->SetAttribute("Motion", 1);
        listElement->InsertEndChild(objAttribs);

        XMLElement* effectAttribs = doc.NewElement("Translate");
        effectAttribs->SetAttribute("x", 0);
        effectAttribs->SetAttribute("y", 0);
        effectAttribs->SetAttribute("z", 0);
        objAttribs->InsertEndChild(effectAttribs);

        effectAttribs = doc.NewElement("Rotate");
        effectAttribs->SetAttribute("x", 0);
        effectAttribs->SetAttribute("y", 0);
        effectAttribs->SetAttribute("z", 0);
        objAttribs->InsertEndChild(effectAttribs);
    }

    root->InsertEndChild(element);


    element = doc.NewElement("Lights");

    // luz ambiente
    XMLElement* listElement = doc.NewElement("Light");
    listElement->SetAttribute("Type", "LIGHT_AMBIENT");
    listElement->SetAttribute("Exponent", -1);
    listElement->SetAttribute("Enable", 1);
    listElement->SetAttribute("Name", "      Ambient Light");
    listElement->SetAttribute("AngleInner", -1);
    listElement->SetAttribute("Angle", -1);
    element->InsertEndChild(listElement);

    XMLElement* objAttribs = doc.NewElement("Position");
    objAttribs->SetAttribute("x", 0);
    objAttribs->SetAttribute("y", 0);
    objAttribs->SetAttribute("z", 0);
    listElement->InsertEndChild(objAttribs);

    objAttribs = doc.NewElement("Direction");
    objAttribs->SetAttribute("x", 0);
    objAttribs->SetAttribute("y", 0);
    objAttribs->SetAttribute("z", 0);
    listElement->InsertEndChild(objAttribs);

    objAttribs = doc.NewElement("VecA");
    objAttribs->SetAttribute("x", 0);
    objAttribs->SetAttribute("y", 0);
    objAttribs->SetAttribute("z", 0);
    listElement->InsertEndChild(objAttribs);

    objAttribs = doc.NewElement("VecB");
    objAttribs->SetAttribute("x", 0);
    objAttribs->SetAttribute("y", 0);
    objAttribs->SetAttribute("z", 0);
    listElement->InsertEndChild(objAttribs);

    objAttribs = doc.NewElement("Attenuation");
    objAttribs->SetAttribute("x", 0);
    objAttribs->SetAttribute("y", 0);
    objAttribs->SetAttribute("z", 0);
    listElement->InsertEndChild(objAttribs);

    objAttribs = doc.NewElement("Material");
    listElement->InsertEndChild(objAttribs);

    XMLElement* mtlAttribs = doc.NewElement("Ambient");
    mtlAttribs->SetAttribute("r", 1);
    mtlAttribs->SetAttribute("g", 1);
    mtlAttribs->SetAttribute("b", 1);
    objAttribs->InsertEndChild(mtlAttribs);

    mtlAttribs = doc.NewElement("Specular");
    mtlAttribs->SetAttribute("r", 0);
    mtlAttribs->SetAttribute("g", 0);
    mtlAttribs->SetAttribute("b", 0);
    objAttribs->InsertEndChild(mtlAttribs);

    mtlAttribs = doc.NewElement("Diffuse");
    mtlAttribs->SetAttribute("r", 0);
    mtlAttribs->SetAttribute("g", 0);
    mtlAttribs->SetAttribute("b", 0);
    objAttribs->InsertEndChild(mtlAttribs);
    // fim luz ambiente

    for (unsigned int j = 0; j < lights.size(); ++j)
    {
        listElement = doc.NewElement("Light");
        listElement->SetAttribute("Type", "LIGHT_PONTUAL");
        listElement->SetAttribute("Exponent", -1);
        listElement->SetAttribute("Enable", 1);
        listElement->SetAttribute("Name", "      Pontual Light");
        listElement->SetAttribute("AngleInner", -1);
        listElement->SetAttribute("Angle", -1);
        element->InsertEndChild(listElement);

        objAttribs = doc.NewElement("Position");
        objAttribs->SetAttribute("x", -1.0f*lights[j]->getPosition().get_x());
        objAttribs->SetAttribute("y", lights[j]->getPosition().get_y());
        objAttribs->SetAttribute("z", lights[j]->getPosition().get_z());
        listElement->InsertEndChild(objAttribs);

        objAttribs = doc.NewElement("Direction");
        objAttribs->SetAttribute("x", 0);
        objAttribs->SetAttribute("y", 0);
        objAttribs->SetAttribute("z", 0);
        listElement->InsertEndChild(objAttribs);

        objAttribs = doc.NewElement("VecA");
        objAttribs->SetAttribute("x", 0);
        objAttribs->SetAttribute("y", 0);
        objAttribs->SetAttribute("z", 0);
        listElement->InsertEndChild(objAttribs);

        objAttribs = doc.NewElement("VecB");
        objAttribs->SetAttribute("x", 0);
        objAttribs->SetAttribute("y", 0);
        objAttribs->SetAttribute("z", 0);
        listElement->InsertEndChild(objAttribs);

        objAttribs = doc.NewElement("Attenuation");
        objAttribs->SetAttribute("x", lights[j]->getConstantAttenuation());
        objAttribs->SetAttribute("y", lights[j]->getLinearAttenuation());
        objAttribs->SetAttribute("z", lights[j]->getQuadraticAttenuation());
        listElement->InsertEndChild(objAttribs);

        objAttribs = doc.NewElement("Material");
        listElement->InsertEndChild(objAttribs);

        mtlAttribs = doc.NewElement("Ambient");
        mtlAttribs->SetAttribute("r", *(lights[j]->getAmbient()));
        mtlAttribs->SetAttribute("g", *(lights[j]->getAmbient() + 1));
        mtlAttribs->SetAttribute("b", *(lights[j]->getAmbient() + 2));
        objAttribs->InsertEndChild(mtlAttribs);

        mtlAttribs = doc.NewElement("Specular");
        mtlAttribs->SetAttribute("r", *(lights[j]->getSpecular()));
        mtlAttribs->SetAttribute("g", *(lights[j]->getSpecular() + 1));
        mtlAttribs->SetAttribute("b", *(lights[j]->getSpecular() + 2));
        objAttribs->InsertEndChild(mtlAttribs);

        mtlAttribs = doc.NewElement("Diffuse");
        mtlAttribs->SetAttribute("r", *(lights[j]->getDiffuse()));
        mtlAttribs->SetAttribute("g", *(lights[j]->getDiffuse() + 1));
        mtlAttribs->SetAttribute("b", *(lights[j]->getDiffuse() + 2));
        objAttribs->InsertEndChild(mtlAttribs);
    }

    root->InsertEndChild(element);

    XMLError errorResult = doc.SaveFile(filename);
    XMLCheckResult(errorResult);

    return XML_SUCCESS;
}


void Scene::addLightSource(LightSource light)
{
    lights.push_back(&light);
}


void Scene::addObject(Object obj)
{
    objects.push_back(&obj);
}
