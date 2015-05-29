#include "PbScene.h"


using namespace tinyxml2;


PbScene::PbScene()
{
}


#ifndef XMLCheckResult
    #define XMLCheckResult(errorResult) if (errorResult != XML_SUCCESS) { printf("Error doc: %i\n", errorResult); return errorResult; }
#endif


bool PbScene::loadXml(const char* filename)
{
    XMLDocument doc;

    XMLElement* element = nullptr;
    XMLElement* listElement = nullptr;
    XMLElement* subListElement = nullptr;
    XMLElement* subSubListElement = nullptr;


    XMLError result = doc.LoadFile(filename);
    XMLCheckResult(result);


    XMLNode* root = doc.FirstChild();

    if (!root)
    {
        LOGerr("Root not defined");
        return XML_ERROR_FILE_READ_ERROR;
    }


    element = root->FirstChildElement("Effects");

    if (element != nullptr)
    {
        float radius = 0.0f, focalLength = 0.0f, dof = 0.0f;

        result = element->QueryFloatAttribute("Radius", &radius);
        result = element->QueryFloatAttribute("FocalLength", &focalLength);
        result = element->QueryFloatAttribute("DOF", &dof);

        setEffects(radius, focalLength, dof);
    }
    else
    {
        LOGwar("Effects not defined");
    }

    element = root->FirstChildElement("Perspective");

    if (element)
    {
        unsigned int width = 640, height = 480;
        float far = 120000.0f, near = 0.01f, fov = 45.0f;

        result = element->QueryFloatAttribute("Far", &far);
        result = element->QueryFloatAttribute("Near", &near);
        result = element->QueryUnsignedAttribute("Width", &width);
        result = element->QueryFloatAttribute("Angle", &fov);
        result = element->QueryUnsignedAttribute("Height", &height);

        setPerspective(fov, near, far, width, height);
    }
    else
    {
        LOGwar("Perspective not defined");
    }


    element = root->FirstChildElement("Camera");

    if (element)
    {
        float eye_x = 0.0f,    eye_y = 0.0f,    eye_z = -1.0f;
        float lookAt_x = 0.0f, lookAt_y = 0.0f, lookAt_z = 0.0f;
        float viewUp_x = 0.0f, viewUp_y = 1.0f, viewUp_z = -1.0f;


        listElement = element->FirstChildElement("Eye");

        if (listElement)
        {
            result = listElement->QueryFloatAttribute("x", &eye_x);
            result = listElement->QueryFloatAttribute("y", &eye_y);
            result = listElement->QueryFloatAttribute("z", &eye_z);
        }
        else
        {
            LOGwar("Camera.Eye not defined");
        }


        listElement = element->FirstChildElement("At");

        if (listElement)
        {
            result = listElement->QueryFloatAttribute("x", &lookAt_x);
            result = listElement->QueryFloatAttribute("y", &lookAt_y);
            result = listElement->QueryFloatAttribute("z", &lookAt_z);
        }
        else
        {
            LOGwar("Camera.At not defined");
        }


        listElement = element->FirstChildElement("Up");

        if (listElement)
        {
            result = listElement->QueryFloatAttribute("x", &viewUp_x);
            result = listElement->QueryFloatAttribute("y", &viewUp_y);
            result = listElement->QueryFloatAttribute("z", &viewUp_z);
        }
        else
        {
            LOGwar("Camera.Up not defined");
        }


        camera.updateCamera(eye_x,    eye_y,    eye_z,
                            lookAt_x, lookAt_y, lookAt_z,
                            viewUp_x, viewUp_y, viewUp_z);
    }
    else
    {
        LOGwar("Camera not defined");
    }


    element = root->FirstChildElement("Objects");

    if (element)
    {
        listElement = element->FirstChildElement("Object");


        while (listElement)
        {
            const char* objType = nullptr;
            bool enabled = false;
            const char* objName = nullptr;
            const char* objTexture = nullptr;
            const char* objBump = nullptr;

            objType = listElement->Attribute("Type");

            if (!objType)
            {
                LOGerr("Object.Type string error");
                return false;
            }

            result = listElement->QueryBoolAttribute("Enabled", &enabled);

            objName = listElement->Attribute("Name");

            if (!objName)
            {
                LOGerr("Object.Name string error");
                return false;
            }

            objTexture = listElement->Attribute("Texture");

            if (!objTexture)
            {
                LOGerr("Object.Texture string error");
                return false;
            }

            objBump = listElement->Attribute("Bump");

            if (!objBump)
            {
                LOGerr("Object.Bump string error");
                return false;
            }


                subListElement = listElement->FirstChildElement("Position");

                if (!subListElement)
                {
                    LOGwar("Object.Position not defined");
                    return XML_ERROR_PARSING_ELEMENT;
                }

                float pos_x, pos_y, pos_z;

                result = subListElement->QueryFloatAttribute("x", &pos_x);
                result = subListElement->QueryFloatAttribute("y", &pos_y);
                result = subListElement->QueryFloatAttribute("z", &pos_z);


                subListElement = listElement->FirstChildElement("Rotation");

                if (!subListElement)
                {
                    LOGwar("Object.Rotation not defined");
                    return XML_ERROR_PARSING_ELEMENT;
                }

                float rot_x, rot_y, rot_z;

                result = subListElement->QueryFloatAttribute("x", &rot_x);
                result = subListElement->QueryFloatAttribute("y", &rot_y);
                result = subListElement->QueryFloatAttribute("z", &rot_z);


                subListElement = listElement->FirstChildElement("Scale");

                if (!subListElement)
                {
                    LOGwar("Object.Scale not defined");
                    return XML_ERROR_PARSING_ELEMENT;
                }

                float scale_x, scale_y, scale_z;

                result = subListElement->QueryFloatAttribute("x", &scale_x);
                result = subListElement->QueryFloatAttribute("y", &scale_y);
                result = subListElement->QueryFloatAttribute("z", &scale_z);


                subListElement = listElement->FirstChildElement("Material");

                if (!subListElement)
                {
                    LOGwar("Object.Material not defined");
                    return XML_ERROR_PARSING_ELEMENT;
                }

                float reflection, glossyReflection, shininess, refraction, glossyRefraction;

                result = subListElement->QueryFloatAttribute("Reflection", &reflection);
                result = subListElement->QueryFloatAttribute("GLossyReflection", &glossyReflection);
                result = subListElement->QueryFloatAttribute("Shininess", &shininess);
                result = subListElement->QueryFloatAttribute("Refraction", &refraction);
                result = subListElement->QueryFloatAttribute("GLossyRefraction", &glossyRefraction);


                    subSubListElement = subListElement->FirstChildElement("Ambient");

                    if (!subSubListElement)
                    {
                        LOGwar("Object.Material.Ambient not defined");
                        return XML_ERROR_PARSING_ELEMENT;
                    }

                    float ka_r, ka_g, ka_b;

                    result = subSubListElement->QueryFloatAttribute("r", &ka_r);
                    result = subSubListElement->QueryFloatAttribute("g", &ka_g);
                    result = subSubListElement->QueryFloatAttribute("b", &ka_b);


                    subSubListElement = subListElement->FirstChildElement("Specular");

                    if (!subSubListElement)
                    {
                        LOGwar("Object.Material.Specular not defined");
                        return XML_ERROR_PARSING_ELEMENT;
                    }

                    float ks_r, ks_g, ks_b;

                    result = subSubListElement->QueryFloatAttribute("r", &ks_r);
                    result = subSubListElement->QueryFloatAttribute("g", &ks_g);
                    result = subSubListElement->QueryFloatAttribute("b", &ks_b);


                    subSubListElement = subListElement->FirstChildElement("Diffuse");

                    if (!subSubListElement)
                    {
                        LOGwar("Object.Material.Diffuse not defined");
                        return XML_ERROR_PARSING_ELEMENT;
                    }

                    float kd_r, kd_g, kd_b;

                    result = subSubListElement->QueryFloatAttribute("r", &kd_r);
                    result = subSubListElement->QueryFloatAttribute("g", &kd_g);
                    result = subSubListElement->QueryFloatAttribute("b", &kd_b);


                subListElement = listElement->FirstChildElement("Effects");

                if (!subListElement)
                {
                    LOGwar("Object.Effects not defined");
                    return XML_ERROR_PARSING_ELEMENT;
                }

                bool motion;

                result = subListElement->QueryBoolAttribute("Motion", &motion);


                    subSubListElement = subListElement->FirstChildElement("Translate");

                    if (!subSubListElement)
                    {
                        LOGwar("Object.Effects.Translate not defined");
                        return XML_ERROR_PARSING_ELEMENT;
                    }

                    float translate_x, translate_y, translate_z;

                    result = subSubListElement->QueryFloatAttribute("x", &translate_x);
                    result = subSubListElement->QueryFloatAttribute("y", &translate_y);
                    result = subSubListElement->QueryFloatAttribute("z", &translate_z);


                    subSubListElement = subListElement->FirstChildElement("Rotate");

                    if (!subSubListElement)
                    {
                        LOGwar("Object.Effects.Rotate not defined");
                        return XML_ERROR_PARSING_ELEMENT;
                    }

                    float rotate_x, rotate_y, rotate_z;

                    result = subSubListElement->QueryFloatAttribute("x", &rotate_x);
                    result = subSubListElement->QueryFloatAttribute("y", &rotate_y);
                    result = subSubListElement->QueryFloatAttribute("z", &rotate_z);


            listElement = listElement->NextSiblingElement("Object");
        }
    }
    else
    {
        LOGwar("Objects not defined");
    }


    element = root->FirstChildElement("Lights");

    if (element)
    {/*
        listElement = element->FirstChildElement("Light");

        // first light must be ambient
        if (listElement)
        {
            const char* lightType = nullptr;
            float lightExponent = 0.0f;
            bool lightEnable = true;
            const char* lightName = nullptr;
            float lightAngleInner = 0.0f;
            float lightAngle = 0.0f;


            lightType = listElement->Attribute("Type");

            if (lightType)
            {
                if (strcmp(lightType, "LIGHT_AMBIENT"))
                {
                    LOGerr("First light must be ambient");
                    return false;
                }
            }
            else
            {
                LOGerr("Light.Type string error");
                return false;
            }

            result = listElement->QueryFloatAttribute("Exponent", &lightExponent);
            result = listElement->QueryBoolAttribute("Enable", &lightEnable);

            lightName = listElement->Attribute("Name");

            if (!lightName)
            {
                LOGerr("Light.Name string error");
                return false;
            }

            result = listElement->QueryFloatAttribute("AngleInner", &lightAngleInner);
            result = listElement->QueryFloatAttribute("Angle", &lightAngle);


                subListElement = listElement->FirstChildElement("Position");

                if (subListElement)
                {
                    LOGwar("Light.Position of ambient light defined");
                }


                subListElement = listElement->FirstChildElement("Direction");

                if (subListElement)
                {
                    LOGwar("Light.Direction of ambient light defined");
                }


                subListElement = listElement->FirstChildElement("VecA");

                if (subListElement)
                {
                    LOGwar("Light.VecA of ambient light defined");
                }


                subListElement = listElement->FirstChildElement("VecB");

                if (subListElement)
                {
                    LOGwar("Light.VecB of ambient light defined");
                }


                subListElement = listElement->FirstChildElement("Attenuation");

                if (subListElement)
                {
                    LOGwar("Light.Attenuation of ambient light defined");
                }


                subListElement = listElement->FirstChildElement("Material");

                if (subListElement)
                {
                    subSubListElement = subListElement->FirstChildElement("Ambient");

                    if (subSubListElement)
                    {
                        float ka_r, ka_g, ka_b;

                        result = subSubListElement->QueryFloatAttribute("r", &ka_r);
                        result = subSubListElement->QueryFloatAttribute("g", &ka_g);
                        result = subSubListElement->QueryFloatAttribute("b", &ka_b);

                        lightAmbient.setAmbient(ka_r, ka_g, ka_b);
                    }
                    else
                    {
                        LOGwar("Light.Material.Ambient not defined");
                    }


                    subSubListElement = subListElement->FirstChildElement("Specular");

                    if (subSubListElement)
                    {
                        LOGwar("Light.Material.Specular of ambient light defined");
                    }


                    subSubListElement = subListElement->FirstChildElement("Diffuse");

                    if (subSubListElement)
                    {
                        LOGwar("Light.Material.Diffuse of ambient light defined");
                    }
                }
                else
                {
                    LOGwar("Light.Material not defined");
                }
        }
        else
        {
            LOGwar("Light ambient not defined");
        }


        listElement = element->FirstChildElement("Light");


        while (listElement)
        {
            const char* lightType = nullptr;
            float lightExponent = 0.0f;
            bool lightEnable = true;
            const char* lightName = nullptr;
            float lightAngleInner = 0.0f;
            float lightAngle = 0.0f;


            lightType = listElement->Attribute("Type");

            if (lightType)
            {
                if (strcmp(lightType, "LIGHT_AMBIENT"))
                {
                    LOGerr("First light must be ambient");
                    return false;
                }
            }
            else
            {
                LOGerr("Light.Type string error");
                return false;
            }

            result = listElement->QueryFloatAttribute("Exponent", &lightExponent);
            result = listElement->QueryBoolAttribute("Enable", &lightEnable);

            lightName = listElement->Attribute("Name");

            if (!lightName)
            {
                LOGerr("Light.Name string error");
                return false;
            }

            result = listElement->QueryFloatAttribute("AngleInner", &lightAngleInner);
            result = listElement->QueryFloatAttribute("Angle", &lightAngle);


                subListElement = listElement->FirstChildElement("Position");

                if (subListElement)
                {
                    float pos_x, pos_y, pos_z;

                    result = subListElement->QueryFloatAttribute("x", &pos_x);
                    result = subListElement->QueryFloatAttribute("y", &pos_y);
                    result = subListElement->QueryFloatAttribute("z", &pos_z);

                    lights .setPosition(pos_x, pos_y, pos_z);
                }
                else
                {
                    LOGwar("Light.Position not defined");
                }


                subListElement = listElement->FirstChildElement("Direction");

                if (subListElement)
                {
                    float dir_x, dir_y, dir_z;

                    result = subListElement->QueryFloatAttribute("x", &dir_x);
                    result = subListElement->QueryFloatAttribute("y", &dir_y);
                    result = subListElement->QueryFloatAttribute("z", &dir_z);

                    lights .setDirection(dir_x, dir_y, dir_z);
                }
                else
                {
                    LOGwar("Light.Direction not defined");
                }


                subListElement = listElement->FirstChildElement("VecA");

                if (subListElement)
                {
                    float vecA_x, vecA_y, vecA_z;

                    result = subListElement->QueryFloatAttribute("x", &vecA_x);
                    result = subListElement->QueryFloatAttribute("y", &vecA_y);
                    result = subListElement->QueryFloatAttribute("z", &vecA_z);

                    lights .setVecA(vecA_x, vecA_y, vecA_z);
                }
                else
                {
                    LOGwar("Light.VecA not defined");
                }


                subListElement = listElement->FirstChildElement("VecB");

                if (subListElement)
                {
                    float vecB_x, vecB_y, vecB_z;

                    result = subListElement->QueryFloatAttribute("x", &vecB_x);
                    result = subListElement->QueryFloatAttribute("y", &vecB_y);
                    result = subListElement->QueryFloatAttribute("z", &vecB_z);

                    lights .setVecB(vecB_x, vecB_y, vecB_z);
                }
                else
                {
                    LOGwar("Light.VecB not defined");
                }


                subListElement = listElement->FirstChildElement("Attenuation");

                if (subListElement)
                {
                    float constantAtt, linearAtt, quadraticAtt;

                    result = subListElement->QueryFloatAttribute("x", &constantAtt);
                    result = subListElement->QueryFloatAttribute("y", &linearAtt);
                    result = subListElement->QueryFloatAttribute("z", &quadraticAtt);

                    lights .setConstantAttenuation(constantAtt);
                    lights .setLinearAttenuation(linearAtt);
                    lights .setQuadraticAttenuation(quadraticAtt);
                }
                else
                {
                    LOGwar("Light.Attenuation not defined");
                }


                subListElement = listElement->FirstChildElement("Material");

                if (subListElement)
                {
                    subSubListElement = subListElement->FirstChildElement("Ambient");

                    if (subSubListElement)
                    {

                        float ka_r, ka_g, ka_b;

                        result = subSubListElement->QueryFloatAttribute("r", &ka_r);
                        result = subSubListElement->QueryFloatAttribute("g", &ka_g);
                        result = subSubListElement->QueryFloatAttribute("b", &ka_b);

                        lights .setAmbient(ka_r, ka_g, ka_b);
                    }
                    else
                    {
                        LOGwar("Light.Material.Ambient not defined");
                    }


                    subSubListElement = subListElement->FirstChildElement("Specular");

                    if (subSubListElement)
                    {
                        float ks_r, ks_g, ks_b;

                        result = subSubListElement->QueryFloatAttribute("r", &ks_r);
                        result = subSubListElement->QueryFloatAttribute("g", &ks_g);
                        result = subSubListElement->QueryFloatAttribute("b", &ks_b);

                        lights .setSpecular(ks_r, ks_g, ks_b);
                    }
                    else
                    {
                        LOGwar("Light.Material.Specular not defined");
                    }


                    subSubListElement = subListElement->FirstChildElement("Diffuse");

                    if (subSubListElement)
                    {
                        float kd_r, kd_g, kd_b;

                        result = subSubListElement->QueryFloatAttribute("r", &kd_r);
                        result = subSubListElement->QueryFloatAttribute("g", &kd_g);
                        result = subSubListElement->QueryFloatAttribute("b", &kd_b);

                        lights .setDiffuse(kd_r, kd_g, kd_b);
                    }
                    else
                    {
                        LOGwar("Light.Material.Diffuse not defined");
                    }
                }
                else
                {
                    LOGwar("Light.Material not defined");
                }
        }*/
    }
    else
    {
        LOGwar("Lights not defined");
    }


    LOG("success");
    return XML_SUCCESS;
}


bool PbScene::saveXml(const char* filename)
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
            /*objAttribs->SetAttribute("x", objects[i]->getTransform().getScale_x());
            objAttribs->SetAttribute("y", objects[i]->getTransform().getScale_y());
            objAttribs->SetAttribute("z", objects[i]->getTransform().getScale_z());
            listElement->InsertEndChild(objAttribs);*/
        }/*
        else
        {
            char axis = objects[i]->getAxis();

            listElement = doc.NewElement("Object");
            listElement->SetAttribute("Type", "OBJCUBE");
            listElement->SetAttribute("Enabled", 1);
            listElement->SetAttribute("Name", objects[i]->getId().c_str());
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

    XMLError errorResult = doc.SaveFile("PbScene.xml");
    XMLCheckResult(errorResult);

    return XML_SUCCESS;
}


void PbScene::setEffects(float radius, float focalLenght, float depthOfField)
{

}


void PbScene::setPerspective(float fov, float zNear, float zFar, unsigned int width, unsigned int height)
{

}


void PbScene::setCamera(float eye_x,    float eye_y,    float eye_z,
                        float lookAt_x, float lookAt_y, float lookAt_z,
                        float viewUp_x, float viewUp_y, float viewUp_z)
{
    camera = PbCamera(eye_x, eye_y, eye_z, lookAt_x, lookAt_y, lookAt_z, viewUp_x, viewUp_y, viewUp_z);
}


void PbScene::addLightSource(PbLightSource light)
{
    lights.push_back(&light);
}


void PbScene::addObject(PbObject obj)
{
    objects.push_back(&obj);
}
