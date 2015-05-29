#ifndef PB_SCENE_H
#define PB_SCENE_H


#include "PbObject.h"
#include "PbLightSource.h"
#include "PbPosition3d.h"
#include "PbCamera.h"
#include "PbGraphics.h"
#include "PbColor4.h"


#include <vector>


class PbScene
{
	public:
	
		explicit PbScene(PbCamera camera, PbLightSource light, PbPosition3d (&screenPlane)[4], PbGraphics *graphics, PbColor4 backColor);
		
		~PbScene() {delete renderer;}
		
			
		void drawPhong(const char *filename, unsigned int width, unsigned int height);
		
		
		void addObject(PbObject *obj) {objects.push_back(obj);}
		void addLightSource(PbLightSource light) {lights.push_back(light);}
	
	
		std::vector<PbObject*>& getObjects() {return objects;}
		std::vector<PbLightSource>& getLightSource() {return lights;}
	
	
	private:
	
		PbCamera camera;
		PbPosition3d (&screenPlane)[4]; // order: upperLeft, lowerleft, lowerRight, upperRight
	
		std::vector<PbObject*> objects;
		std::vector<PbLightSource> lights;

		PbGraphics *renderer;
		
		PbColor4 backgroundColor;
		
		
        PbColor4 calculatePhongIlumination(PbPosition3d point, PbObject *object);
};

#endif // PB_SCENE_H
