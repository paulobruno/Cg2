#ifndef OBJECT_H
#define OBJECT_H


#include "Material.h"
#include "Position3d.h"
#include "Transform.h"
#include "ObjectProperties.h"
#include "ObjectEffects.h"
#include "ColorRgba.h"

#include <QImage>
#include <string>


class Object
{
    public:

        Object();
        Object(Transform transform, Material material, ObjectProperties properties, ObjectEffects effects);
        ~Object();

        std::string getId() {return nullptr;}

        Transform getTransform() {return transform;}
        void updateTransform(Transform t) {transform = t;}

        Material getMaterial() {return material;}

        ObjectProperties getProperties() {return properties;}

        bool isGlass() {return material.getRefraction() > 0 ? true : false;}
        bool isMirror() {return material.getReflection() > 0 ? true : false;}

        virtual Position3d* interceptedWithRay(Position3d rayOrigin, Position3d rayDirection) = 0;
        virtual Position3d getNormal(Position3d point) = 0;

        virtual ColorRgba textureColor(QImage texture, Position3d* point) = 0;


    protected:

        Transform transform;
        Material material;
        ObjectProperties properties;
        ObjectEffects effects;
        Position3d interceptionPosition;
};


#endif // OBJECT_H
