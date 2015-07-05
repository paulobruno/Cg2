#include "SceneXmlLoader.h"


#ifndef XMLCheckResult
    #define XMLCheckResult(errorResult) if (errorResult != tinyxml2::XML_SUCCESS) { LOGerr("Error: " << errorResult); }
#endif

#ifndef XMLCheckAttribution
    #define XMLCheckAttribution(attributionResult) if (attributionResult != tinyxml2::XML_NO_ERROR) { LOGerr("Error: " << attributionResult); }
#endif


SceneXmlLoader::SceneXmlLoader()
{}


bool SceneXmlLoader::loadXml(const char* filename)
{
    tinyxml2::XMLDocument doc;

    tinyxml2::XMLError result = doc.LoadFile(filename);
    XMLCheckResult(result);

    tinyxml2::XMLNode* root = doc.FirstChildElement("Scene");

    if (!root)
    {
        LOGerr("Root not defined");
        return tinyxml2::XML_ERROR_FILE_READ_ERROR;
    }

    return readFromRoot(root);
}


bool SceneXmlLoader::readFromRoot(tinyxml2::XMLNode* root)
{
    effects = effectsParser.parse(root);
    perspective = perspectiveParser.parse(root);
    camera = cameraParser.parse(root);
    objects = objectsParser.parse(root);
    lights = lightsParser.parse(root);

    LOGdbg("success");

    return tinyxml2::XML_SUCCESS;
}





bool SceneXmlLoader::saveXml(const char* filename)
{
    tinyxml2::XMLDocument doc;

    tinyxml2::XMLNode* root = doc.NewElement("Scene");
    doc.InsertFirstChild(root);


    tinyxml2::XMLElement* element = doc.NewElement("Perspective");
    element->SetAttribute("Far", perspective.getFar());
    element->SetAttribute("Near", perspective.getNear());
    element->SetAttribute("Width", perspective.getWidth());
    element->SetAttribute("Angle", perspective.getFieldOfView());
    element->SetAttribute("Height", perspective.getHeight());
    root->InsertEndChild(element);


    element = doc.NewElement("Camera");

    tinyxml2::XMLElement* camElem = doc.NewElement("Eye");
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
        tinyxml2::XMLElement* listElement;
        tinyxml2::XMLElement* objAttribs;

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
            objAttribs->SetAttribute("x", -1.0f*objects[i]->getTransform().getPosition().get_x());
            objAttribs->SetAttribute("y", objects[i]->getTransform().getPosition().get_y());
            objAttribs->SetAttribute("z", objects[i]->getTransform().getPosition().get_z());
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

        tinyxml2::XMLElement* mtlAttribs = doc.NewElement("Ambient");
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

        tinyxml2::XMLElement* effectAttribs = doc.NewElement("Translate");
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
    tinyxml2::XMLElement* listElement = doc.NewElement("Light");
    listElement->SetAttribute("Type", "LIGHT_AMBIENT");
    listElement->SetAttribute("Exponent", -1);
    listElement->SetAttribute("Enable", 1);
    listElement->SetAttribute("Name", "      Ambient Light");
    listElement->SetAttribute("AngleInner", -1);
    listElement->SetAttribute("Angle", -1);
    element->InsertEndChild(listElement);

    tinyxml2::XMLElement* objAttribs = doc.NewElement("Position");
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

    tinyxml2::XMLElement* mtlAttribs = doc.NewElement("Ambient");
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

    tinyxml2::XMLError errorResult = doc.SaveFile(filename);
    XMLCheckResult(errorResult);

    return tinyxml2::XML_SUCCESS;
}
