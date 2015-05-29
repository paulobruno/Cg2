// 2013, PAULO BRUNO DE SOUSA SERAFIM, Fortaleza - CE, Brasil

#include "PbFace.h"
#include "PbAffineSpace.h"

PbPosition3d PbFace :: calculateNormal()
{
    PbPosition3d i, j, n;

    PbVertex v1 = *(vertexVector[0]);
    PbVertex v2 = *(vertexVector[1]);
    PbVertex v3 = *(vertexVector[2]);

    i = pointsSubtraction(v2, v1);
    i.normalize();

    j = pointsSubtraction(v3, v1);
    j.normalize();

    n = crossProduct(i, j);

    return n;
}

PbVertex PbFace :: calculateCenter()
{
    PbVertex v1 = *(vertexVector[0]);
    PbVertex v2 = *(vertexVector[1]);
    PbVertex v3 = *(vertexVector[2]);

    double aux_x = (v1.get_x() + v2.get_x() + v3.get_x()) / 3.0;
    double aux_y = (v1.get_y() + v2.get_y() + v3.get_y()) / 3.0;
    double aux_z = (v1.get_z() + v2.get_z() + v3.get_z()) / 3.0;

    PbVertex center(aux_x, aux_y, aux_z);

    return center;
}

PbFace :: PbFace()
{
    vertexVector.push_back( new PbVertex(0.0, 0.0, 0.0) );
    vertexVector.push_back( new PbVertex(1.0, 0.0, 0.0) );
    vertexVector.push_back( new PbVertex(0.0, 1.0, 0.0) );

    normal.set_pos(0.0, 0.0, 1.0);
    center = calculateCenter();
}

PbFace :: PbFace(PbVertex* v1, PbVertex* v2, PbVertex* v3)
{
    vertexVector.push_back(v1);
    vertexVector.push_back(v2);
    vertexVector.push_back(v3);

    normal = calculateNormal();
    center = calculateCenter();
}

void PbFace :: setVertexV1(PbVertex* v1)
{
    vertexVector[0] = v1;
    normal = calculateNormal();
    center = calculateCenter();
}

void PbFace :: setVertexV2(PbVertex* v2)
{
    vertexVector[1] = v2;
    normal = calculateNormal();
    center = calculateCenter();
}

void PbFace :: setVertexV3(PbVertex* v3)
{
    vertexVector[2] = v3;
    normal = calculateNormal();
    center = calculateCenter();
}

void PbFace :: setVertices(PbVertex* v1, PbVertex* v2, PbVertex* v3)
{
    vertexVector[0] = v1;
    vertexVector[1] = v2;
    vertexVector[2] = v3;

    normal = calculateNormal();
    center = calculateCenter();
}
