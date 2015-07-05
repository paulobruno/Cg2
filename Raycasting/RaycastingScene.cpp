#include "RaycastingScene.h"


RaycastingScene::RaycastingScene()
{}


void RaycastingScene::render()
{
    /*LightSource* light = new LightSource();
    light->setAmbient(1.0f, 1.0f, 1.0f);
    light->setDiffuse(0.8f, 0.8f, 0.8f);
    light->setSpecular(0.47451f, 0.47451f, 0.47451f);
    light->setPosition(0.0f, 25.0f, 0.0f, 0.0f);
    light->setConstantAttenuation(1.0f);
    light->setLinearAttenuation(0.0f);
    light->setQuadraticAttenuation(0.0f);*/
    //lights.push_back(light);

    LOG("eye_x: " << camera.getEye_x() << "\t eye_y: " << camera.getEye_y() << "\t eye_z: " << camera.getEye_z());
    LOG("at_x: " << camera.getLookAt_x() << "\t at_y: " << camera.getLookAt_y() << "\t at_z: " << camera.getLookAt_z());


    image.newImage("teste.png", width, height);


    float angle = perspective.getFieldOfView();
    float aspectRatio = (float)width / (float)height;

    float h = 2 * perspective.getNear() * tan(M_PI*angle / 360.0f);
    float w = h * aspectRatio;

    float delay_x = w / (float)width;
    float delay_y = h / (float)height;

    float znear = perspective.getNear();


    for (unsigned int i = 0; i < height; ++i)
    {
        for (unsigned int j = 0; j < width; ++j)
        {
            float x = (-w / 2.0f) + (delay_x / 2.0) + ((float)j * delay_x);
            float y = (-h / 2.0f) + (delay_y / 2.0) + ((float)i * delay_y);

            x *= -1.0f;

            Position3d cameraRayDirection(x, y, znear);

            Position3d worldRayDirection = camera.getEye() - camera.camToWorld(cameraRayDirection);
            worldRayDirection.normalize();


            Object* hittedObj = nullptr;
            Position3d* hittedInterception = nullptr;

            for (unsigned int k = 0; k < objects.size(); ++k)
            {
                Position3d* interception = objects[k]->interceptedWithRay(camera.getEye(), worldRayDirection);

                if (interception)
                {
                    if (hittedObj)
                    {
                        float currentDistance = interception->distance(camera.getEye());
                        float previousDistance = hittedInterception->distance(camera.getEye());

                        if (currentDistance < previousDistance)
                        {
                            hittedObj = objects[k];
                            hittedInterception = interception;
                        }
                    }
                    else
                    {
                        hittedObj = objects[k];
                        hittedInterception = interception;
                    }
                }
            }


            ColorRgba color = backgroundColor;

            if (hittedObj)
            {
                color = calculateColor(camera.getEye(), *hittedInterception, hittedObj);
            }
            else
            {
                color = backgroundColor;
            }

/*
            Position3d* interception = sphere.interceptedWithRay(camera.getEye(), worldRayDirection);

            if (interception)
            {
                color = calculateColor(camera.getEye(), *interception, &sphere);
            }
            else
            {
                color = backgroundColor;
            }
*/


            image.setPixel(j, i, color);
        }
    }

    image.saveImage();
}


ColorRgba RaycastingScene::calculateColor(Position3d startPoint, Position3d interceptionPoint, Object* object)
{
    Position3d v = Position3d(startPoint - interceptionPoint);
    v.normalize();

    Position3d n = object->getNormal(interceptionPoint);
    n.normalize();

    if (v.dotProduct(n) < 0.0f)
    {
        n*(-1.0f);
    }

    ColorRgba color;


    if (n.dotProduct(v) < 0)
    {
        color = backgroundColor;
    }
    else
    {
        Material mat = object->getMaterial();

        float matKa[4] =
        {
            mat.getKaR(),
            mat.getKaG(),
            mat.getKaB(),
            mat.getKaA()
        };

        float matKd[4] =
        {
            mat.getKdR(),
            mat.getKdG(),
            mat.getKdB(),
            mat.getKdA()
        };

        float matKs[4] =
        {
            mat.getKsR(),
            mat.getKsG(),
            mat.getKsB(),
            mat.getKsA()
        };


        float Ir = 0.0f;
        float Ig = 0.0f;
        float Ib = 0.0f;


        for (unsigned int i = 0; i < lights.size(); ++i)
        {
            float amb[4] = {*(lights[i]->getAmbient() + 0),
                            *(lights[i]->getAmbient() + 1),
                            *(lights[i]->getAmbient() + 2),
                            *(lights[i]->getAmbient() + 3)};

            float dif[4] = {*(lights[i]->getDiffuse() + 0),
                            *(lights[i]->getDiffuse() + 1),
                            *(lights[i]->getDiffuse() + 2),
                            *(lights[i]->getDiffuse() + 3)};

            float spe[4] = {*(lights[i]->getSpecular() + 0),
                            *(lights[i]->getSpecular() + 1),
                            *(lights[i]->getSpecular() + 2),
                            *(lights[i]->getSpecular() + 3)};

            float a = lights[i]->getConstantAttenuation();
            float b = lights[i]->getLinearAttenuation();
            float c = lights[i]->getQuadraticAttenuation();

            float dist = interceptionPoint.distance(lights[i]->getPosition());
            float attenuation = a + b*dist + c*dist*dist;


            Position3d l = Position3d(lights[i]->getPosition() - interceptionPoint);
            l.normalize();

            Position3d r = n*(2*l.dotProduct(n)) - l;
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

            /*if (object->isMirror())
            {
                if (depth <= RECURSION_DEPTH)
                {
                    Position3d newL = Position3d(startPoint - point);
                    newL.normalize();

                    Position3d newR = n*(2*newL.dotProduct(n)) - newL;
                    newR.normalize();

//                    out << "novo raio ->\n\tn: " << n.get_x() << ' ' << n.get_y() << ' ' << n.get_z()
//                        << "\n\tl: " << l.get_x() << ' ' << l.get_y() << ' '  << l.get_z()
//                        << "\n\tr: " << r.get_x() << ' ' << r.get_y() << ' '  << r.get_z() << '\n';
                    ColorRgba reflectedColor = sendRay(point, newR, depth+1, objId);

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
                    Position3d n = object->getNormal(point); // ja recebe normalizado

                    Position3d L = Position3d(startPoint - point);
                    L.normalize();

                    float dn = transparency / mat.getTransparency();
                    float dotNL = n.dotProduct(L);

                    float theta = 1 - dn*(1-(dotNL*dotNL));
                    if (theta >= 0)
                    {
                        Position3d T = n*( dn*dotNL - sqrt( 1 - dn*(1-(dotNL*dotNL)) ) ) - L*dn;
                        T.normalize();

                        ColorRgba transmittedColor = sendRay(point, T, depth+1, objId);

                        Ir += matTf[0]*spe[0]*((float)transmittedColor.r/255.0);
                        Ig += matTf[1]*spe[1]*((float)transmittedColor.g/255.0);
                        Ib += matTf[2]*spe[2]*((float)transmittedColor.b/255.0);
                        //++contrib;
                    }
                }
            }*/
        }

       /* Ir /= contrib;
        Ig /= contrib;
        Ib /= contrib;
*/
        //LOG("Ir: " << Ir << " Ig: " << Ig << " Ib: " << Ib);

        if (Ir > 1.0f)
        {
            Ir = 1.0f;
        }
        else if (Ir < 0.0f)
        {
            Ir = 0.0f;
        }
        else
        {
            Ir *= 1.0f;
        }

        if (Ig > 1.0f)
        {
            Ig = 1.0f;
        }
        else if (Ig < 0.0f)
        {
            Ig = 0.0f;
        }
        else
        {
            Ig *= 1.0f;
        }

        if (Ib > 1.0f)
        {
            Ib = 1.0f;
        }
        else if (Ib < 0.0f)
        {
            Ib = 0.0f;
        }
        else
        {
            Ib *= 1.0f;
        }


        color = ColorRgba(Ir, Ig, Ib, 0);
    }

    return color;
}
