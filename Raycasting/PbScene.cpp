#include "PbScene.h"

#define RECURSION_DEPTH 3


PbScene::PbScene(PbCamera camera, PbLightSource light, PbPosition3d (&screenPlane)[4], PbGraphics *graphics, PbColor4 backColor)
	: camera(camera),
	  screenPlane(screenPlane),
	  renderer(graphics),
	  backgroundColor(backColor)
{
	lights.push_back(light);

    out.open("log");
	
    objects.reserve(10);
}
	
		
void PbScene::drawPhong(const char *filename, unsigned int width, unsigned int height)
{
	renderer->newImage(filename, width, height);

	// (0,0) in screen position is the upperLeft screenPlane[0]
	// (w,h) is the lowerRight screenPlane[2]



	float pixelWidth = (screenPlane[2].get_x() - screenPlane[0].get_x()) / (float) width; // worldCoordinates
	float pixelHeight = (screenPlane[0].get_y() - screenPlane[2].get_y()) / (float) height; // worldCoordinates


    for (unsigned int j = 0; j < height; ++j)
	{
        for (unsigned int i = 0; i < width; ++i)
		{
/*
            // supersampling
            float aux_x[4] =
            {
                screenPlane[0].get_x() + ((float)i + 0.25f) * pixelWidth,
                screenPlane[1].get_x() + ((float)i + 0.25f) * pixelWidth,
                screenPlane[2].get_x() + ((float)i + 0.75f) * pixelWidth,
                screenPlane[3].get_x() + ((float)i + 0.75f) * pixelWidth
            };
            float aux_y[4] =
            {
                screenPlane[0].get_y() - ((float)j + 0.25f) * pixelHeight,
                screenPlane[1].get_y() - ((float)j + 0.75f) * pixelHeight,
                screenPlane[2].get_y() - ((float)j + 0.75f) * pixelHeight,
                screenPlane[3].get_y() - ((float)j + 0.25f) * pixelHeight
            };

            PbColor4 color[4];

            for (unsigned int m = 0; m < 4; ++m)
            {
                PbPosition3d ray(aux_x[m] - camera.getEye_x(),
                                 aux_y[m] - camera.getEye_y(),
                                 screenPlane[0].get_z() - camera.getEye_z());

                ray.normalize();

                unsigned int k;

                for (k = 0; k < objects.size(); ++k)
                {
                    // interceptar
                    interceptPoint = objects[k]->intercept(camera.getEye(), ray);

                    if (interceptPoint)
                    {
                        break;
                    }
                }

                if (interceptPoint) // ha intersecao
                {
                    // calcular a cor
                    color[m] = calculatePhongIlumination(*interceptPoint, objects[k]);

                    // gerar a imagem
                    //renderer->setPixel(i, j, color);
                }
                else // nao ha intersecao
                {
                    color[m] = backgroundColor;
                    //renderer->setPixel(i, j, backgroundColor);
                }
            }

            PbColor4 cor =
            {
                (color[0].r + color[1].r + color[2].r + color[3].r),
                (color[0].g + color[1].g + color[2].g + color[3].g),
                (color[0].b + color[1].b + color[2].b + color[3].b),
                (color[0].a + color[1].a + color[2].a + color[3].a)
            };

            renderer->setPixel(i, j, cor);*/

			// gerar o raio
            float aux_x = screenPlane[0].get_x() + ((float)i + 0.5f) * pixelWidth;
            float aux_y = screenPlane[0].get_y() - ((float)j + 0.5f) * pixelHeight;

			PbPosition3d ray(aux_x - camera.getEye_x(), aux_y - camera.getEye_y(), screenPlane[0].get_z() - camera.getEye_z());
	
			ray.normalize();
			



            renderer->setPixel(i,j, sendRay(camera.getEye(), ray, 0, -1));
        }
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
            if (oldId != k) // interceptou com ele mesmo
            {
                intId = k;
                break;
            }
        }
    }

    if (interceptPoint) // ha intersecao
    {
        PbPosition3d* secIntercept = NULL;

        for (m = 0; m < objects.size(); ++m)
        {
            // raio fonte luminosa
            secIntercept = objects[m]->intercept(*interceptPoint, lights[0].getPosition());

            if (secIntercept)
            {
                if (intId == m)
                {
                    secIntercept = NULL;
                }
                else
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
            return backgroundColor;
        }
        else
        {
            //return calculatePhongIlumination(*interceptPoint, objects[k], depth, intId);
            if (objects[intId]->isMirror())
            {
                if (depth > RECURSION_DEPTH)
                {
                    //out << "profundidade\n";
                    return calculatePhongIlumination(*interceptPoint, objects[k], depth, intId);
                }
                else
                {
                    PbPosition3d n = objects[intId]->getNormal(*interceptPoint); // ja recebe normalizado

                    PbPosition3d l = PbPosition3d(camera.getEye() - *interceptPoint);
                    l.normalize();

                    PbPosition3d r = n*(2*l.dotProduct(n)) - l;
                    r.normalize();

//                    out << "novo raio ->\n\tn: " << n.get_x() << ' ' << n.get_y() << ' ' << n.get_z()
//                        << "\n\tl: " << l.get_x() << ' ' << l.get_y() << ' '  << l.get_z()
//                        << "\n\tr: " << r.get_x() << ' ' << r.get_y() << ' '  << r.get_z() << '\n';
                    return sendRay(*interceptPoint, r, depth+1, intId);
                }
            }
            else if (objects[intId]->isGlass())
            {
                if (depth > RECURSION_DEPTH)
                {
                    //out << "profundidade\n";
                    return calculatePhongIlumination(*interceptPoint, objects[k], depth, intId);
                }
                else
                {
                    PbPosition3d N = objects[intId]->getNormal(*interceptPoint); // ja recebe normalizado

                    PbPosition3d L = PbPosition3d(camera.getEye() - *interceptPoint);
                    L.normalize();

                    float dn = objects[intId]->getEtaWorld() / objects[intId]->getEtaObject();
                    float dotNL = N.dotProduct(L);

                    PbPosition3d T = N*( dn*dotNL - sqrt( 1 - dn*(1-(dotNL*dotNL)) ) ) - L*dn;
                    T.normalize();

                    return sendRay(*interceptPoint, T, depth+1, intId);
                }
            }
            else
            {
                // calcular a cor difusa
                return calculatePhongIlumination(*interceptPoint, objects[k], depth, intId);
            }

        }
    }
    else // nao ha intersecao
    {
        return backgroundColor;
    }

    return backgroundColor;
}


PbColor4 PbScene::calculatePhongIlumination(PbPosition3d point, PbObject *object, int depth, int objId)
{
    PbPosition3d v = PbPosition3d(camera.getEye() - point);
    v.normalize();

    PbPosition3d n = object->getNormal(point); // ja recebe normalizado

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

               /* if (object->isMirror())
                {
                    if (depth <= RECURSION_DEPTH)
                    {
                        PbPosition3d newL = PbPosition3d(camera.getEye() - point);
                        newL.normalize();

                        PbPosition3d newR = n*(2*l.dotProduct(n)) - l;
                        newR.normalize();

    //                    out << "novo raio ->\n\tn: " << n.get_x() << ' ' << n.get_y() << ' ' << n.get_z()
    //                        << "\n\tl: " << l.get_x() << ' ' << l.get_y() << ' '  << l.get_z()
    //                        << "\n\tr: " << r.get_x() << ' ' << r.get_y() << ' '  << r.get_z() << '\n';
                        PbColor4 reflectedColor = sendRay(point, newR, depth+1, objId);

                        Ir += matKs[0]*spe[0]*reflectedColor.r;
                        Ig += matKs[1]*spe[1]*reflectedColor.g;
                        Ib += matKs[2]*spe[2]*reflectedColor.b;
                    }
                }*/
            }


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
