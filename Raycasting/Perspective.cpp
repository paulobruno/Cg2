#include "Perspective.h"


Perspective::Perspective()
{
    fieldOfView = 45.0f;
    near = 0.01f;
    far = 120000.0f;
    width = 640;
    height = 480;
}


Perspective::Perspective(float fieldOfView, float near, float far, unsigned int width, unsigned int height)
    : fieldOfView(fieldOfView)
    , near(near)
    , far(far)
    , width(width)
    , height(height)
{}


Perspective::~Perspective()
{}
