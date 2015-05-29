#include <QColor>
#include <QImage>

#ifndef PB_QT_H
#define PB_QT_H


#include "PbGraphics.h"


class PbQt : public PbGraphics
{
	public:
	
        explicit PbQt() {}
        ~PbQt() {imgname = NULL;}
		
		void newImage(const char *filename, unsigned int w, unsigned int h);
		
		void setPixel(unsigned int x, unsigned int y, PbColor4 color);
        void setPixel(unsigned int x, unsigned int y, PB_uint8 r, PB_uint8 g, PB_uint8 b, PB_uint8 a = 255);
	
		bool saveImage();
		
	
	private:
	
		QImage img;
	
		const char *imgname;
};


#endif // PB_QT_H
