#include "BoundingBox.h"


BoundingBox::BoundingBox()
    : Cube()
{

}


BoundingBox::BoundingBox(Transform transform, Material material, ObjectProperties properties, ObjectEffects effects)
    : Cube(transform, material, properties, effects)
{}
