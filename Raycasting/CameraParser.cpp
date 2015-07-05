#include "CameraParser.h"


Camera CameraParser::parse(tinyxml2::XMLNode *parent)
{
    tinyxml2::XMLElement* cameraElement = parent->FirstChildElement("Camera");

    if (!cameraElement)
    {
        LOGwar("Camera not defined");
    }
    else
    {
        parseEyeAttributes(cameraElement);
        parseLookAtAttributes(cameraElement);
        parseViewUpAttributes(cameraElement);
    }

    return camera;
}


void CameraParser::parseEyeAttributes(tinyxml2::XMLElement* cameraElement)
{
    tinyxml2::XMLElement* eyeAttribute = cameraElement->FirstChildElement("Eye");

    if (!eyeAttribute)
    {
        LOGwar("Camera.Eye not defined");
        return;
    }

    float eye_x = 0.0f,    eye_y = 0.0f,    eye_z = -1.0f;

    XMLCheckAttribution(eyeAttribute->QueryFloatAttribute("x", &eye_x));
    XMLCheckAttribution(eyeAttribute->QueryFloatAttribute("y", &eye_y));
    XMLCheckAttribution(eyeAttribute->QueryFloatAttribute("z", &eye_z));

    camera.updateEye(eye_x, eye_y, eye_z);
}


void CameraParser::parseLookAtAttributes(tinyxml2::XMLElement* cameraElement)
{
    tinyxml2::XMLElement* lookAtAttribute = cameraElement->FirstChildElement("At");

    if (!lookAtAttribute)
    {
        LOGwar("Camera.At not defined");
        return;
    }

    float lookAt_x = 0.0f, lookAt_y = 0.0f, lookAt_z = 0.0f;

    XMLCheckAttribution(lookAtAttribute->QueryFloatAttribute("x", &lookAt_x));
    XMLCheckAttribution(lookAtAttribute->QueryFloatAttribute("y", &lookAt_y));
    XMLCheckAttribution(lookAtAttribute->QueryFloatAttribute("z", &lookAt_z));

    camera.updateLookAt(lookAt_x, lookAt_y, lookAt_z);
}


void CameraParser::parseViewUpAttributes(tinyxml2::XMLElement* cameraElement)
{
    tinyxml2::XMLElement* viewUpAttribute = cameraElement->FirstChildElement("Up");

    if (!viewUpAttribute)
    {
        LOGwar("Camera.Up not defined");
        return;
    }

    float viewUp_x = 0.0f, viewUp_y = 1.0f, viewUp_z = -1.0f;

    XMLCheckAttribution(viewUpAttribute->QueryFloatAttribute("x", &viewUp_x));
    XMLCheckAttribution(viewUpAttribute->QueryFloatAttribute("y", &viewUp_y));
    XMLCheckAttribution(viewUpAttribute->QueryFloatAttribute("z", &viewUp_z));

    camera.updateViewUp(camera.getEye_x() + viewUp_x,
                        camera.getEye_y() + viewUp_y,
                        camera.getEye_z() + viewUp_z);
}
