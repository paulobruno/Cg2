// 2013, PAULO BRUNO DE SOUSA SERAFIM, Fortaleza - CE, Brasil

#include "PbAffineSpace.h"

void multByScalar(double scalar, PbPosition3d *point)
{
	point->set_x( scalar * point->get_x() );
	point->set_y( scalar * point->get_y() );
	point->set_z( scalar * point->get_z() );
}

double dotProduct(PbPosition3d p1, PbPosition3d p2)
{
	return ( (p1.get_x() * p2.get_x()) + (p1.get_y() * p2.get_y()) + (p1.get_z() * p2.get_z()) );
}

PbPosition3d crossProduct(PbPosition3d v1, PbPosition3d v2)
{
	double aux_x = (v1.get_y() * v2.get_z()) - (v2.get_y() * v1.get_z());
	double aux_y = (v1.get_z() * v2.get_x()) - (v2.get_z() * v1.get_x());
	double aux_z = (v1.get_x() * v2.get_y()) - (v2.get_x() * v1.get_y());

    PbPosition3d auxVector(aux_x, aux_y , aux_z);

	return auxVector;
}

PbPosition3d pointsSubtraction(PbPosition3d endPoint, PbPosition3d initPoint)
{
	double aux_x = endPoint.get_x() - initPoint.get_x();
	double aux_y = endPoint.get_y() - initPoint.get_y();
	double aux_z = endPoint.get_z() - initPoint.get_z();

    PbPosition3d auxVector(aux_x, aux_y , aux_z);

	return auxVector;
}
