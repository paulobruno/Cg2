#include "Object.h"

Object::Object()
    : mirror(true)
    , glass(true)
{
    transform = Transform();
    material = Material();
    properties = ObjectProperties();
    effects = ObjectEffects();
}


Object::Object(Transform transform, Material material, ObjectProperties properties, ObjectEffects effects)
    : mirror(true)
    , glass(true)
    , transform(transform)
    , material(material)
    , properties(properties)
    , effects(effects)
{}


Object::~Object()
{}
