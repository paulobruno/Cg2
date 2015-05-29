#include "PbSphere.h"


PbPosition3d PbSphere::getNormal(PbPosition3d point)
{
    // verificar se o ponto esta na superficie da esfera
        PbPosition3d n = point - center;
        n.normalize();
        return n;
}


PbPosition3d* PbSphere::intercept(PbPosition3d initialPoint, PbPosition3d rayDirection)
{
	// vector ray direction
	float v_x = rayDirection.get_x();
	float v_y = rayDirection.get_y();
	float v_z = rayDirection.get_z();

	// adjust interception equation
	float a = (v_x * v_x) + (v_y * v_y) + (v_z * v_z);
		
	// difference: ray initial point - sphere center point
	float d_x = initialPoint.get_x() - center.get_x();
	float d_y = initialPoint.get_y() - center.get_y();
	float d_z = initialPoint.get_z() - center.get_z();
	
	// adjust interception equation
	float b = 2 * ( (v_x * d_x) + (v_y * d_y) + (v_z * d_z) );
    float c = (d_x * d_x) + (d_y * d_y) + (d_z * d_z) - (radius * radius);

	float delta = b*b - (4*a*c);

	if (delta <= 0)
	{
		return NULL;
	}
	
	// bhaskara
	float t1 = (- b + sqrt(delta)) / (2*a);
	float t2 = (- b - sqrt(delta)) / (2*a);
	
    //LOG("t1 = " << t1 << "\tt2 = " << t2);
	
	
    return ( new PbPosition3d(initialPoint + (rayDirection * (t1 <= t2 ? t1 : t2))) );
}
