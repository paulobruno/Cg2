#include "Effects.h"


Effects::Effects()
{
    radius = 0.0f;
    focalLength = 0.0f;
    depthOfField = 0.0f;
}


Effects::Effects(float radius, float focalLength, float depthOfField)
    : radius(radius)
    , focalLength(focalLength)
    , depthOfField(depthOfField)
{}


Effects::~Effects()
{}
