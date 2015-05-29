#ifndef PB_GRAPHICS_H
#define PB_GRAPHICS_H


#include "../utils/pb_log.h"
#include "../utils/PbColor4.h"


class PbGraphics
{
	public:
	
		explicit PbGraphics() {}
		virtual ~PbGraphics() {}
		
		virtual void newImage(const char *filename, unsigned int w, unsigned int h) = 0;
		
		virtual void setPixel(unsigned int x, unsigned int y, PbColor4 color) = 0;
		virtual void setPixel(unsigned int x, unsigned int y, PB_uint8 r, PB_uint8 g, PB_uint8 b, PB_uint8 a = 255) = 0;

		virtual bool saveImage() = 0;
};


#endif // PB_GRAPHICS_H
