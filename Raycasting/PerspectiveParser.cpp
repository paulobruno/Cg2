#include "PerspectiveParser.h"


Perspective PerspectiveParser::parse(tinyxml2::XMLNode *parent)
{
    tinyxml2::XMLElement* perspectiveElement = parent->FirstChildElement("Perspective");

    if (!perspectiveElement)
    {
        LOGwar("Object.Material not defined");
    }
    else
    {
        unsigned int width = 640, height = 480;
        float far = 120000.0f, near = 0.01f, fov = 45.0f;

        XMLCheckAttribution(perspectiveElement->QueryFloatAttribute("Far", &far));
        XMLCheckAttribution(perspectiveElement->QueryFloatAttribute("Near", &near));
        XMLCheckAttribution(perspectiveElement->QueryUnsignedAttribute("Width", &width));
        XMLCheckAttribution(perspectiveElement->QueryFloatAttribute("Angle", &fov));
        XMLCheckAttribution(perspectiveElement->QueryUnsignedAttribute("Height", &height));

        perspective = Perspective(fov, near, far, width, height);
    }

    return perspective;
}
