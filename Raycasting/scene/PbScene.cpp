#include "PbScene.h"


#define RECURSION_DEPTH 4
#define SUBDIVISIONS 1
#define RANDOM (float)rand()/(float)RAND_MAX


using namespace tinyxml2;


PbScene::PbScene(unsigned int width, unsigned int height, PbCamera camera, PbLightSource light, PbPosition3d (&screenPlane)[4], PbGraphics *graphics, PbColor4 backColor, float transparency)
    : width(width),
      height(height),
      camera(camera),
	  screenPlane(screenPlane),
	  renderer(graphics),
      backgroundColor(backColor),
      transparency(transparency)
{
	lights.push_back(light);

    //out.open("log");
	
    objects.reserve(10);
}
	
		
void PbScene::drawPhong(const char *filename)
{
	renderer->newImage(filename, width, height);

	// (0,0) in screen position is the upperLeft screenPlane[0]
	// (w,h) is the lowerRight screenPlane[2]



	float pixelWidth = (screenPlane[2].get_x() - screenPlane[0].get_x()) / (float) width; // worldCoordinates
	float pixelHeight = (screenPlane[0].get_y() - screenPlane[2].get_y()) / (float) height; // worldCoordinates


    for (unsigned int j = 0; j < height; ++j)
	{
        for (unsigned int i = 0; i < width; ++i)
        {/*

            float aux_x = screenPlane[0].get_x() + ((float)i + 0.5f) * pixelWidth;
            float aux_y = screenPlane[0].get_x() - ((float)j + 0.5f) * pixelHeight;
            PbPosition3d ray(aux_x - camera.getEye_x(), aux_y - camera.getEye_y(), screenPlane[0].get_z() - camera.getEye_z());

            ray.normalize();

            PbColor4 auxcolor = sendRay(camera.getEye(), ray, 1, -1);

            renderer->setPixel(i,j, auxcolor);
            */

            // gerar o raio

            PbColor4 color = {0, 0, 0, 0};
            float r = 0.0f, g = 0.0f, b = 0.0f;

            // supersampling
            for (unsigned int s_j = 0; s_j < SUBDIVISIONS; ++s_j)
            {
                for (unsigned int s_i = 0; s_i < SUBDIVISIONS; ++s_i)
                {
                    float aux_x = screenPlane[0].get_x() + ((float)i + 0.05f /*(RANDOM+(float)s_i)/SUBDIVISIONS*/) * pixelWidth;
                    float aux_y = screenPlane[0].get_y() - ((float)j + 0.05f /*(RANDOM+(float)s_j)/SUBDIVISIONS*/) * pixelHeight;

                    PbPosition3d ray(aux_x - camera.getEye_x(), aux_y - camera.getEye_y(), screenPlane[0].get_z() - camera.getEye_z());

                    ray.normalize();

                    PbColor4 auxcolor = sendRay(camera.getEye(), ray, 1, -1);
                    r += auxcolor.r;
                    g += auxcolor.g;
                    b += auxcolor.b;
                }
            }

            r /= (float)(SUBDIVISIONS*SUBDIVISIONS);
            g /= (float)(SUBDIVISIONS*SUBDIVISIONS);
            b /= (float)(SUBDIVISIONS*SUBDIVISIONS);

            if (r > 255.0f) r = 255;
            if (g > 255.0f) g = 255;
            if (b > 255.0f) b = 255;
            if (r < 0.0f) r = 0;
            if (g < 0.0f) g = 0;
            if (b < 0.0f) b = 0;

            color.r = (PB_uint8)r;
            color.g = (PB_uint8)g;
            color.b = (PB_uint8)b;

            renderer->setPixel(i,j, color);


        }
        /*if (!(j % 10))
        {
            printf("%: %f\n", (float)(j*width)*100.0f/(width*height) );
            fflush(stdout);
        }*/
    }


    renderer->saveImage();
}


// oldId is the object intercepted, used to avoid interception with itself
PbColor4 PbScene::sendRay(PbPosition3d startPoint, PbPosition3d ray, unsigned int depth, int oldId)
{
    PbPosition3d *interceptPoint = NULL;

    unsigned int k = 0;
    unsigned int m = 0;


    int intId = -1;

    for (k = 0; k < objects.size(); ++k)
    {
        // interceptar
        interceptPoint = objects[k]->intercept(startPoint, ray);

        if (interceptPoint)
        {
            if (oldId != k) // nao interceptou com ele mesmo
            {
                intId = k;
                break;
            }
        }
    }


    if (interceptPoint) // ha intersecao
    {
        static int count = 0;
        if (objects[intId]->getAxis() == 'y')
        {
            ++count;
        }


        if (objects[intId]->isGlass())
        {
            return calculatePhongIlumination(startPoint, *interceptPoint, objects[k], depth, intId);
        }
        else
        {
            PbPosition3d* secIntercept = NULL;

            for (m = 0; m < objects.size(); ++m)
            {
                if (intId == m)
                {
                    secIntercept = NULL;
                }
                else
                {
                    // raio fonte luminosa
                    secIntercept = objects[m]->intercept(*interceptPoint, lights[0].getPosition());
/*
                    if (count == 75)
                    {
                        LOG("ip_x: " << interceptPoint->get_x());
                        LOG("ip y: " << interceptPoint->get_y());
                        LOG("ip z: " << interceptPoint->get_z());


                        LOG("l_x: " << lights[0].getPosition().get_x());
                        LOG("l y: " << lights[0].getPosition().get_y());
                        LOG("l z: " << lights[0].getPosition().get_z());
                    }*/

                    if (secIntercept)
                    {
                        if (secIntercept->distance(lights[0].getPosition()) >= interceptPoint->distance(lights[0].getPosition()))
                        {
                            secIntercept = NULL;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }


            if (secIntercept) // interceptou alguem antes da luz
            {
                float matKa[4] =
                {
                    objects[intId]->getMaterial().getKaR(),
                    objects[intId]->getMaterial().getKaG(),
                    objects[intId]->getMaterial().getKaB(),
                    objects[intId]->getMaterial().getKaA()
                };
                PbColor4 amb =
                {
                    (PB_uint8)(matKa[0] * 255.0f),
                    (PB_uint8)(matKa[1] * 255.0f),
                    (PB_uint8)(matKa[2] * 255.0f),
                    (PB_uint8)(matKa[3] * 255.0f)
                };
                return amb;
            }
            else
            {
                return calculatePhongIlumination(startPoint, *interceptPoint, objects[k], depth, intId);
            }
        }
    }
    else // nao ha intersecao
    {
        return backgroundColor;
    }

    return backgroundColor;
}


PbColor4 PbScene::calculatePhongIlumination(PbPosition3d startPoint, PbPosition3d point, PbObject *object, int depth, int objId)
{
    //int contrib = 1;

    PbPosition3d v = PbPosition3d(startPoint - point);
    v.normalize();

    PbPosition3d n = object->getNormal(point); // ja recebe normalizado

    if (v.dotProduct(n) < 0.0f)
    {
        n*(-1.0f);
    }

    PbColor4 color;


    if (n.dotProduct(v) < 0)
    {
        color = {0, 0, 0, 0};
    }
    else
    {
        PbMaterial mat = object->getMaterial();

        float matKa[4] = {*(mat.getKa() + 0),
                          *(mat.getKa() + 1),
                          *(mat.getKa() + 2),
                          *(mat.getKa() + 3)};

        float matKd[4] = {*(mat.getKd() + 0),
                          *(mat.getKd() + 1),
                          *(mat.getKd() + 2),
                          *(mat.getKd() + 3)};

        float matKs[4] = {*(mat.getKs() + 0),
                          *(mat.getKs() + 1),
                          *(mat.getKs() + 2),
                          *(mat.getKs() + 3)};

        float matTf[4] = {*(mat.getTf() + 0),
                          *(mat.getTf() + 0),
                          *(mat.getTf() + 0),
                          *(mat.getTf() + 0)};

        float Ir = 0.0f;
        float Ig = 0.0f;
        float Ib = 0.0f;


        for (unsigned int i = 0; i < lights.size(); ++i)
        {
                float amb[4] = {*(lights[i].getAmbient() + 0),
                                *(lights[i].getAmbient() + 1),
                                *(lights[i].getAmbient() + 2),
                                *(lights[i].getAmbient() + 3)};

                float dif[4] = {*(lights[i].getDiffuse() + 0),
                                *(lights[i].getDiffuse() + 1),
                                *(lights[i].getDiffuse() + 2),
                                *(lights[i].getDiffuse() + 3)};

                float spe[4] = {*(lights[i].getSpecular() + 0),
                                *(lights[i].getSpecular() + 1),
                                *(lights[i].getSpecular() + 2),
                                *(lights[i].getSpecular() + 3)};

                float a = lights[i].getConstantAttenuation();
                float b = lights[i].getLinearAttenuation();
                float c = lights[i].getQuadraticAttenuation();

                float dist = point.distance(lights[i].getPosition());
                float attenuation = a + b*dist + c*dist*dist;


                PbPosition3d l = PbPosition3d(lights[i].getPosition() - point);
                l.normalize();

                PbPosition3d r = n*(2*l.dotProduct(n)) - l;
                r.normalize();


                float sh = r.dotProduct(v);
                if (sh < 0.0f)
                {
                    sh = 0.0f;
                }
                else
                {
                    sh = pow(sh, mat.getShininess());
                }

                Ir += (matKa[0]*amb[0]) + ( (matKd[0]*dif[0]*(l.dotProduct(n)) + matKs[0]*spe[0]*(sh)) / attenuation );
                Ig += (matKa[1]*amb[1]) + ( (matKd[1]*dif[1]*(l.dotProduct(n)) + matKs[1]*spe[1]*(sh)) / attenuation );
                Ib += (matKa[2]*amb[2]) + ( (matKd[2]*dif[2]*(l.dotProduct(n)) + matKs[2]*spe[2]*(sh)) / attenuation );

                if (object->isMirror())
                {
                    if (depth <= RECURSION_DEPTH)
                    {
                        PbPosition3d newL = PbPosition3d(startPoint - point);
                        newL.normalize();

                        PbPosition3d newR = n*(2*newL.dotProduct(n)) - newL;
                        newR.normalize();

    //                    out << "novo raio ->\n\tn: " << n.get_x() << ' ' << n.get_y() << ' ' << n.get_z()
    //                        << "\n\tl: " << l.get_x() << ' ' << l.get_y() << ' '  << l.get_z()
    //                        << "\n\tr: " << r.get_x() << ' ' << r.get_y() << ' '  << r.get_z() << '\n';
                        PbColor4 reflectedColor = sendRay(point, newR, depth+1, objId);

                        Ir += matKs[0]*spe[0]*((float)reflectedColor.r/255.0);
                        Ig += matKs[1]*spe[1]*((float)reflectedColor.g/255.0);
                        Ib += matKs[2]*spe[2]*((float)reflectedColor.b/255.0);
                        //LOG("Ir: " << Ir << " Ig: " << Ig << " Ib: " << Ib);
                        //++contrib;
                    }
                }

                if (object->isGlass())
                {
                    if (depth <= RECURSION_DEPTH)
                    {
                        PbPosition3d n = object->getNormal(point); // ja recebe normalizado

                        PbPosition3d L = PbPosition3d(startPoint - point);
                        L.normalize();

                        float dn = transparency / mat.getTransparency();
                        float dotNL = n.dotProduct(L);

                        float theta = 1 - dn*(1-(dotNL*dotNL));
                        if (theta >= 0)
                        {
                            PbPosition3d T = n*( dn*dotNL - sqrt( 1 - dn*(1-(dotNL*dotNL)) ) ) - L*dn;
                            T.normalize();

                            PbColor4 transmittedColor = sendRay(point, T, depth+1, objId);

                            Ir += matTf[0]*spe[0]*((float)transmittedColor.r/255.0);
                            Ig += matTf[1]*spe[1]*((float)transmittedColor.g/255.0);
                            Ib += matTf[2]*spe[2]*((float)transmittedColor.b/255.0);
                            //++contrib;
                        }
                    }
                }
            }

       /* Ir /= contrib;
        Ig /= contrib;
        Ib /= contrib;
*/
        //LOG("Ir: " << Ir << " Ig: " << Ig << " Ib: " << Ib);

        if (Ir > 1.0f)
        {
            Ir = 255;
        }
        else if (Ir < 0.0f)
        {
            Ir = 0;
        }
        else
        {
            Ir *= 255.0f;
        }

        if (Ig > 1.0f)
        {
            Ig = 255;
        }
        else if (Ig < 0.0f)
        {
            Ig = 0;
        }
        else
        {
            Ig *= 255.0f;
        }

        if (Ib > 1.0f)
        {
            Ib = 255;
        }
        else if (Ib < 0.0f)
        {
            Ib = 0;
        }
        else
        {
            Ib *= 255.0f;
        }


        color = {(PB_uint8)Ir, (PB_uint8)Ig, (PB_uint8)Ib, 0};
    }

    return color;
}


#ifndef XMLCheckResult
    #define XMLCheckResult(errorResult) if (errorResult != XML_SUCCESS) { printf("Error: %i\n", errorResult); return errorResult; }
#endif

bool PbScene::saveXml()
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
            objAttribs->SetAttribute("x", objects[i]->getScale_x());
            objAttribs->SetAttribute("y", objects[i]->getScale_y());
            objAttribs->SetAttribute("z", objects[i]->getScale_z());
            listElement->InsertEndChild(objAttribs);
        }
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
                    objAttribs->SetAttribute("y", 2*objects[i]->getScale_y());
                    objAttribs->SetAttribute("z", 2*objects[i]->getScale_z());
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
                    objAttribs->SetAttribute("x", 2*objects[i]->getScale_x());
                    objAttribs->SetAttribute("y", 0.001);
                    objAttribs->SetAttribute("z", 2*objects[i]->getScale_z());
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
                    objAttribs->SetAttribute("x", 2*objects[i]->getScale_x());
                    objAttribs->SetAttribute("y", 2*objects[i]->getScale_y());
                    objAttribs->SetAttribute("z", 0.001);
                    listElement->InsertEndChild(objAttribs);
                    break;

                default:
                    LOGerr("Erro, eixo do plano em desacordo");
                    break;
            }
        }

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
        objAttribs->SetAttribute("x", -1.0f*lights[j].get_x());
        objAttribs->SetAttribute("y", lights[j].get_y());
        objAttribs->SetAttribute("z", lights[j].get_z());
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
        objAttribs->SetAttribute("x", lights[j].getConstantAttenuation());
        objAttribs->SetAttribute("y", lights[j].getLinearAttenuation());
        objAttribs->SetAttribute("z", lights[j].getQuadraticAttenuation());
        listElement->InsertEndChild(objAttribs);

        objAttribs = doc.NewElement("Material");
        listElement->InsertEndChild(objAttribs);

        mtlAttribs = doc.NewElement("Ambient");
        mtlAttribs->SetAttribute("r", *(lights[j].getAmbient()));
        mtlAttribs->SetAttribute("g", *(lights[j].getAmbient() + 1));
        mtlAttribs->SetAttribute("b", *(lights[j].getAmbient() + 2));
        objAttribs->InsertEndChild(mtlAttribs);

        mtlAttribs = doc.NewElement("Specular");
        mtlAttribs->SetAttribute("r", *(lights[j].getSpecular()));
        mtlAttribs->SetAttribute("g", *(lights[j].getSpecular() + 1));
        mtlAttribs->SetAttribute("b", *(lights[j].getSpecular() + 2));
        objAttribs->InsertEndChild(mtlAttribs);

        mtlAttribs = doc.NewElement("Diffuse");
        mtlAttribs->SetAttribute("r", *(lights[j].getDiffuse()));
        mtlAttribs->SetAttribute("g", *(lights[j].getDiffuse() + 1));
        mtlAttribs->SetAttribute("b", *(lights[j].getDiffuse() + 2));
        objAttribs->InsertEndChild(mtlAttribs);
    }

    root->InsertEndChild(element);

    XMLError errorResult = doc.SaveFile("PbScene.xml");
    XMLCheckResult(errorResult);

    return XML_SUCCESS;
}
