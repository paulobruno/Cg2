#include "RaycastingScene.h"


RaycastingScene::RaycastingScene()
{}


void RaycastingScene::render()
{
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

            Position3d cameraRayDirection(x, y, znear);

            Position3d worldRayDirection = camera.getEye() - camera.camToWorld(cameraRayDirection);
            worldRayDirection.normalize();

            //LOG("x: " << worldRayDirection.get_x() << "\ty: " << worldRayDirection.get_y() << "\tz: " << worldRayDirection.get_z());

            ColorRgba color = backgroundColor;

            for (unsigned int k = 0; k < objects.size(); ++k)
            {
                //TODO this verification must be deleted after the implementation of the abstract factory
                if (objects[k])
                {
                    Position3d* interception = objects[k]->interceptedWithRay(camera.getEye(), worldRayDirection);

                    if (interception)
                    {
                        color = calculateColor(camera.getEye(), *interception, objects[k]);
                        //color = ColorRgba(1.0f, 0.0f, 0.0f);
                        break;
                    }
                    else
                    {
                        color = backgroundColor;
                    }
                }
            }

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


    //return ColorRgba(1.0f, 0.0f, 0.0f);
}
