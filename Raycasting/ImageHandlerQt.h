#ifndef IMAGEHANDLERQT_H
#define IMAGEHANDLERQT_H


#include <QColor>
#include <QImage>
#include <string>

#include "ColorRgba.h"
#include "ImageHandler.h"


class ImageHandlerQt : public ImageHandler
{
    public:

        explicit ImageHandlerQt() {}
        ~ImageHandlerQt() {}

        void newImage(std::string filename, unsigned int w, unsigned int h);

        void setPixel(unsigned int x, unsigned int y, ColorRgba color);
        void setPixel(unsigned int x, unsigned int y, float r, float g, float b, float a = 1.0f);

        bool saveImage();


    private:

        QImage image;
        std::string imageName;
};


#endif // IMAGEHANDLERQT_H
