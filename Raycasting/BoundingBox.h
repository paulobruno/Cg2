#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H


#include "log.h"
#include "Position3d.h"
#include "Object.h"
#include "Cube.h"
#include "Matrix4.h"

#include <QImage>


class BoundingBox : public Cube
{
    public:

        BoundingBox();
        BoundingBox(Transform transform, Material material, ObjectProperties properties, ObjectEffects effects);
        ~BoundingBox() {}
};


#endif // BOUNDINGBOX_H
