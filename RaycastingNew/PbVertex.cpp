// 2013, PAULO BRUNO DE SOUSA SERAFIM, Fortaleza - CE, Brasil

#include "PbVertex.h"

PbVertex :: PbVertex()
{
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;

    normal.set_pos(0.0, 0.0, 0.0);
}

PbVertex :: PbVertex(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;

    normal.set_pos(0.0, 0.0, 0.0);
}

void PbVertex :: setNormal(double n_x, double n_y, double n_z)
{
    normal.set_pos(n_x, n_y, n_z);
    normal.normalize();
}

void PbVertex :: incrementNormal(PbPosition3d n)
{
    normal.set_pos(normal.get_x() + n.get_x(), normal.get_y() + n.get_y(), normal.get_z() + n.get_z());
}

void PbVertex :: incrementNormal(double n_x, double n_y, double n_z)
{
    normal.set_pos(normal.get_x() + n_x, normal.get_y() + n_y, normal.get_z() + n_z);
}
