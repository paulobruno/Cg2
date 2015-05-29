// 2013, PAULO BRUNO DE SOUSA SERAFIM, Fortaleza - CE, Brasil

#ifndef PB_AFFINE_SPACE_H
#define PB_AFFINE_SPACE_H

#include "PbPosition3d.h"

void multByScalar(double scalar, PbPosition3d *point);

double dotProduct(PbPosition3d p1, PbPosition3d p2);
PbPosition3d crossProduct(PbPosition3d v1, PbPosition3d v2);

PbPosition3d pointsSubtraction(PbPosition3d endPoint, PbPosition3d initPoint);

#endif // PB_AFFINE_SPACE_H
