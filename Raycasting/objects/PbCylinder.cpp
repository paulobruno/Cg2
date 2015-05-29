#include "PbCylinder.h"

#define DELTA_Y 0.001
#define ZERO_THRESHOLD 0.0001

PbPosition3d PbCylinder::getNormal(PbPosition3d point)
{
    // plano superior
    if ((point.get_y() >= yMax - DELTA_Y) &&
        (point.get_y() <= yMax + DELTA_Y))
    {
        return PbPosition3d(0.0f, 1.0f, 0.0f);
    }

    // plano inferior
    if ((point.get_y() >= yMin - DELTA_Y) &&
        (point.get_y() <= yMin + DELTA_Y))
    {
        return PbPosition3d(0.0f, -1.0f, 0.0f);
    }

    // superfície lateral

    PbPosition3d n(point.get_x() - center.get_x(), 0.0f, point.get_z() - center.get_z());
    n.normalize();

    return n;
}


PbPosition3d* PbCylinder::intercept(PbPosition3d initialPoint, PbPosition3d rayDirection)
{
    float t;

    float *t1 = interceptSup(initialPoint, rayDirection);
    float *t2 = interceptInf(initialPoint, rayDirection);
    float *t3 = interceptCyl(initialPoint, rayDirection);

    if (t1 && *t1 > ZERO_THRESHOLD)
    {
        if (t2 && *t2 > ZERO_THRESHOLD)
        {
            if (t3 && *t3 > ZERO_THRESHOLD)
            {
                t = *t2 <= *t3 ? *t2 : *t3;
            }
            else
            {
                t = *t2;
            }
            t = *t1 <= t ? *t1 : t;
        }
        else
        {
            if (t3 && *t3 > ZERO_THRESHOLD)
            {
                t = *t1 <= *t3 ? *t1 : *t3;
            }
            else
            {
                t = *t1;
            }
        }
    }
    else
    {
        if (t2 && *t2 > ZERO_THRESHOLD)
        {
            if (t3 && *t3 > ZERO_THRESHOLD)
            {
                t = *t2 <= *t3 ? *t2 : *t3;
            }
            else
            {
                t = *t2;
            }
        }
        else
        {
            if (t3 && *t3 > ZERO_THRESHOLD)
            {
                t = *t3;
            }
            else
            {
                return NULL;
            }
        }
    }


    return ( new PbPosition3d(initialPoint + (rayDirection * t)) );
}



float* PbCylinder::interceptInf(PbPosition3d initialPoint, PbPosition3d rayDirection)
{
    // superficie inferior
    PbPosition3d planeCenter(center.get_x(), yMin, center.get_z());
    PbPosition3d normal(0.0f, -1.0f, 0.0f);
    float distToCenter = normal.dotProduct(planeCenter);

    float b = rayDirection.dotProduct(normal);

    if (!b)
    {
        return NULL;
    }

    float a = distToCenter - initialPoint.dotProduct(normal);

    tInf = a/b;

    //tInf = - ( - yMin + initialPoint.get_y() ) / rayDirection.get_y();

    if (tInf > 0.0f)
    {
        float aux_x = initialPoint.get_x() + tInf * rayDirection.get_x();
        float aux_z = initialPoint.get_z() + tInf * rayDirection.get_z();

        // verifica se esta dentro do circulo
        if ( ((aux_x - center.get_x()) * (aux_x - center.get_x()) +
              (aux_z - center.get_z()) * (aux_z - center.get_z())) < (radius*radius))
        {
            return &tInf;
        }
        return NULL;
    }
    return NULL;
}


float* PbCylinder::interceptSup(PbPosition3d initialPoint, PbPosition3d rayDirection)
{
    // superficie superior
    PbPosition3d planeCenter(center.get_x(), yMax, center.get_z());
    PbPosition3d normal(0.0f, 1.0f, 0.0f);
    float distToCenter = normal.dotProduct(planeCenter);

    float b = rayDirection.dotProduct(normal);

    if (!b)
    {
        return NULL;
    }

    float a = distToCenter - initialPoint.dotProduct(normal);

    tSup = a/b;


    //tSup = ( yMax - initialPoint.get_y() ) / rayDirection.get_y();

    if (tSup > 0.0f)
    {
        float aux_x = initialPoint.get_x() + tSup * rayDirection.get_x();
        float aux_z = initialPoint.get_z() + tSup * rayDirection.get_z();

        // verifica se esta dentro do circulo
        if ( ((aux_x - center.get_x()) * (aux_x - center.get_x()) +
              (aux_z - center.get_z()) * (aux_z - center.get_z())) < (radius*radius))
        {
            return &tSup;
        }
        return NULL;
    }
    return NULL;
}


float* PbCylinder::interceptCyl(PbPosition3d initialPoint, PbPosition3d rayDirection)
{
    float v_x = rayDirection.get_x();
    float v_z = rayDirection.get_z();

    float x_0 = initialPoint.get_x();
    float z_0 = initialPoint.get_z();


    // adjust interception equation
    float a = (v_x * v_x) + (v_z * v_z);
    float b = 2 * ( (v_x * (x_0 - center.get_x()) ) +
                    (v_z * (z_0- center.get_z()) ) );
    float c = (x_0 - center.get_x()) * (x_0 - center.get_x()) +
              (z_0 - center.get_z()) * (z_0 - center.get_z()) - (radius * radius);


    float delta = b*b - (4*a*c);

    if (delta <= 0)
    {
        return NULL;
    }

    // bhaskara
    float t1 = (- b + sqrt(delta)) / (2*a);
    float t2 = (- b - sqrt(delta)) / (2*a);


    // holds the minor
    tCyl = t1 <= t2 ? t1 : t2;


    if ((tCyl * rayDirection.get_y() > yMax + DELTA_Y) ||
        (tCyl * rayDirection.get_y() < yMin - DELTA_Y)
        )
    {
        //if (initialPoint.get_x() != 0.0f && initialPoint.get_y() != 0.0f)
        //std::cout << "DELTA x: " << initialPoint.get_x() << " y: " << initialPoint.get_y() << '\n';
        return NULL;
    }

    return &tCyl;
}
