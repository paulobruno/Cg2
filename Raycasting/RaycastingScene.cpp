#include "RaycastingScene.h"


#define TRANSPARENCY 1.0f
#define RECURSION_DEPTH 5
#define RANDOM (float)rand()/(float)RAND_MAX


RaycastingScene::RaycastingScene()
{}


RaycastingScene::~RaycastingScene()
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
            float x = -1.0f * ((-w / 2.0f) + (delay_x / 2.0) + ((float)j * delay_x));
            float y = (-h / 2.0f) + (delay_y / 2.0) + ((float)i * delay_y);

            Position3d cameraRayDirection(x, y, znear);

            Position3d worldRayDirection = camera.getEye() - camera.camToWorld(cameraRayDirection);
            worldRayDirection.normalize();

            
            ColorRgba color = sendRay(camera.getEye(), worldRayDirection, NULL, 0);


            image.setPixel(j, i, color);
        }
    }

    image.saveImage();
}


ColorRgba RaycastingScene::sendRay(Position3d startPoint, Position3d worldRayDirection, Object* sender, unsigned int depth)
{
    Object* hittedObj = nullptr;
    Position3d* hittedInterception = nullptr;

    for (unsigned int k = 0; k < objects.size(); ++k)
    {
        Position3d* interception = objects[k]->interceptedWithRay(startPoint, worldRayDirection);

        if (interception)
        {
            if (objects[k] != sender) // se n interceptou ele msm
            {
                if (hittedObj) // ja havia interceptado alguem
                {
                    float currentDistance = interception->distance(startPoint);
                    float previousDistance = hittedInterception->distance(startPoint);

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
    }

    ColorRgba color = backgroundColor;

    if (hittedObj) // collision occurred
    {
        if ((hasTexture) && (hittedObj->getProperties().getType() == "OBJCUBE"))
        {
            return hittedObj->textureColor(texture, hittedInterception);
        }


        if (hittedObj->isGlass())
        {
            return calculateColor(startPoint, *hittedInterception, hittedObj, depth);
        }
        else
        {
            Position3d* secondaryInterception = NULL;

            for (unsigned int k = 0; k < objects.size(); ++k)
            {
                if (objects[k] != hittedObj)
                {
                    Position3d lightDirection = lights[0]->getPosition() - *hittedInterception;
                    lightDirection.normalize();

                    secondaryInterception = objects[k]->interceptedWithRay(*hittedInterception, lightDirection);

                    if (secondaryInterception)
                    {
                        if (hittedInterception->distance(lights[0]->getPosition())
                          > secondaryInterception->distance(lights[0]->getPosition()))
                        {
                            break;
                        }
                        else
                        {
                            secondaryInterception = NULL;
                        }
                    }
                }
            }


            if (secondaryInterception) // intercepted another object before light
            {
                return hittedObj->getMaterial().getKa();
            }
            else
            {
                return calculateColor(startPoint, *hittedInterception, hittedObj, depth);
            }
        }
    }
    else
    {
        color = backgroundColor;
    }

    return color;
}


ColorRgba RaycastingScene::calculateColor(Position3d startPoint, Position3d interceptionPoint, Object* object, unsigned int depth)
{
    Position3d v = Position3d(startPoint - interceptionPoint);
    v.normalize();

    Position3d n = object->getNormal(interceptionPoint);
    n.normalize();

    if (v.dotProduct(n) < 0.0f)
    {
        n*(-1.0f);
    }

    ColorRgba color = object->getMaterial().getKa();


    if (n.dotProduct(v) > 0)
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

        float matTf[4] =
        {
            mat.getTfR(),
            mat.getTfG(),
            mat.getTfB(),
            mat.getTfA()
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

            Ir += (matKd[0]*dif[0]*(l.dotProduct(n)) + matKs[0]*spe[0]*(sh)) / attenuation;
            Ig += (matKd[1]*dif[1]*(l.dotProduct(n)) + matKs[1]*spe[1]*(sh)) / attenuation;
            Ib += (matKd[2]*dif[2]*(l.dotProduct(n)) + matKs[2]*spe[2]*(sh)) / attenuation;

            if (Ir < 0.0f)
            {
                Ir = 0.0f;
            }
            if (Ig < 0.0f)
            {
                Ig = 0.0f;
            }
            if (Ib < 0.0f)
            {
                Ib = 0.0f;
            }

            Ir += (matKa[0]*amb[0]);
            Ig += (matKa[1]*amb[1]);
            Ib += (matKa[2]*amb[2]);


            if (object->isMirror())
            {
                if (depth <= RECURSION_DEPTH)
                {
                    Ir = 0.0f;
                    Ig = 0.0f;
                    Ib = 0.0f;

                    Position3d newL = Position3d(startPoint - interceptionPoint);
                    newL.normalize();

                    Position3d newR = n*(2*newL.dotProduct(n)) - newL;
                    newR.normalize();

                    ColorRgba reflectedColor = sendRay(interceptionPoint, newR, object, depth+1);

                    Ir += matKs[0]*spe[0]*(reflectedColor.getRed());
                    Ig += matKs[1]*spe[1]*(reflectedColor.getGreen());
                    Ib += matKs[2]*spe[2]*(reflectedColor.getBlue());
                    //LOG("Ir: " << Ir << " Ig: " << Ig << " Ib: " << Ib);
                    //++contrib;
                }
            }

            if (object->isGlass())
            {
                if (depth <= RECURSION_DEPTH)
                {
                    Position3d n = object->getNormal(interceptionPoint);
                    n.normalize();

                    Position3d L = Position3d(startPoint - interceptionPoint);
                    L.normalize();

                    float dn = TRANSPARENCY / mat.getTransparency();
                    float dotNL = n.dotProduct(L);

                    float theta = 1 - dn*(1-(dotNL*dotNL));
                    if (theta >= 0)
                    {
                        Position3d T = n*( dn*dotNL - sqrt( 1 - dn*(1-(dotNL*dotNL)) ) ) - L*dn;
                        T.normalize();

                        ColorRgba transmittedColor = sendRay(interceptionPoint, T, object, depth+1);

                        Ir += matTf[0]*spe[0]*(transmittedColor.getRed());
                        Ig += matTf[1]*spe[1]*(transmittedColor.getGreen());
                        Ib += matTf[2]*spe[2]*(transmittedColor.getBlue());
                        //++contrib;
                    }
                }
            }
        }

        //Ir += mat.getKaR();
        //Ig += mat.getKaG();
        //Ib += mat.getKaB();

       /* Ir /= contrib;
        Ig /= contrib;
        Ib /= contrib;
*/
        //LOG("Ir: " << Ir << " Ig: " << Ig << " Ib: " << Ib);

        if (Ir > 1.0f)
        {
            Ir = 1.0f;
        }
        if (Ig > 1.0f)
        {
            Ig = 1.0f;
        }
        if (Ib > 1.0f)
        {
            Ib = 1.0f;
        }


        color = ColorRgba(Ir, Ig, Ib, 0);
    }

    return color;
}
