#include "Object.h"

Object::Object()
{
    transform = Transform();
    material = Material();
    properties = ObjectProperties();
    effects = ObjectEffects();
}


Object::Object(Transform transform, Material material, ObjectProperties properties, ObjectEffects effects)
    : transform(transform)
    , material(material)
    , properties(properties)
    , effects(effects)
{}


Object::~Object()
{}
