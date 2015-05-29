#include "PbQt.h"

void PbQt::newImage(const char *filename, unsigned int w, unsigned int h)
{
	imgname = filename;

	img = QImage(w, h, QImage::Format_RGB32);
}

		
void PbQt::setPixel(unsigned int x, unsigned int y, PbColor4 color)
{	
    img.setPixel(x, y, qRgba(color.r, color.g, color.b, color.a));
}


void PbQt::setPixel(unsigned int x, unsigned int y, PB_uint8 r, PB_uint8 g, PB_uint8 b, PB_uint8 a)
{
    img.setPixel(x, y, qRgba(r, g, b, a));
}

bool PbQt::saveImage()
{
	if (imgname)
    {
        return img.save(imgname);
	}
	else
	{
		return false;
	}
}
