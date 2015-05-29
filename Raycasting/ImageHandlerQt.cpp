#include "ImageHandlerQt.h"


void ImageHandlerQt::newImage(std::string filename, unsigned int w, unsigned int h)
{
    imageName = filename;

    image = QImage(w, h, QImage::Format_RGB32);
}


void ImageHandlerQt::setPixel(unsigned int x, unsigned int y, ColorRgba color)
{
    image.setPixel(x, y, qRgba(255*color.getRed(), 255*color.getGreen(), 255*color.getBlue(), 255*color.getAlpha()));
}


void ImageHandlerQt::setPixel(unsigned int x, unsigned int y, float r, float g, float b, float a)
{
    image.setPixel(x, y, qRgba(255*r, 255*g, 255*b, 255*a));
}


bool ImageHandlerQt::saveImage()
{
    return image.save(imageName.c_str());
}
