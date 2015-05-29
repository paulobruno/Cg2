#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H


#include "log.h"
#include "ColorRgba.h"

#include <string>


class ImageHandler
{
    public:

        explicit ImageHandler() {}
        virtual ~ImageHandler() {}

        virtual void newImage(std::string filename, unsigned int w, unsigned int h) = 0;

        virtual void setPixel(unsigned int x, unsigned int y, ColorRgba color) = 0;
        virtual void setPixel(unsigned int x, unsigned int y, float r, float g, float b, float a = 1.0f) = 0;

        virtual bool saveImage() = 0;
};


#endif // IMAGEHANDLER_H
