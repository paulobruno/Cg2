// 2013, PAULO BRUNO DE SOUSA SERAFIM, Fortaleza - CE, Brasil

#ifndef PB_VERTEX_H
#define PB_VERTEX_H

#include "PbPosition3d.h"
#include <vector>

class PbVertex : public PbPosition3d {
    public:
        PbVertex();
        PbVertex(double x, double y, double z);

        virtual ~PbVertex() {}

        void setNormal(PbPosition3d norm) {normal = norm;}
        void setNormal(double n_x, double n_y, double n_z);

        void incrementNormal(PbPosition3d n);
        void incrementNormal(double n_x, double n_y, double n_z);

        PbPosition3d getNormal() {return normal;}
        double getNormal_x() {return normal.get_x();}
        double getNormal_y() {return normal.get_y();}
        double getNormal_z() {return normal.get_z();}

        void normalize() {normal.normalize();}

private:
        std::vector<PbVertex> edgesVector;
        PbPosition3d normal;
};

#endif // PB_VERTEX_H
