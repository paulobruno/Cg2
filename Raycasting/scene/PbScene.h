#ifndef PB_SCENE_H
#define PB_SCENE_H


#include "../utils/PbPosition3d.h"
#include "../utils/PbGraphics.h"
#include "../utils/PbColor4.h"
#include "../utils/tinyxml2.h"
#include "../objects/PbObject.h"
#include "../scene/PbLightSource.h"
#include "../scene/PbCamera.h"

#include <fstream>
#include <vector>
#include <cstdlib>


class PbScene
{
	public:
	
        explicit PbScene(unsigned int width, unsigned int height, PbCamera camera, PbLightSource light, PbPosition3d (&screenPlane)[4], PbGraphics *graphics, PbColor4 backColor, float transparency = 1.0f);
		
		~PbScene() {delete renderer;}
		
			
        void drawPhong(const char *filename);
		
		
		void addObject(PbObject *obj) {objects.push_back(obj);}
		void addLightSource(PbLightSource light) {lights.push_back(light);}
	
	
		std::vector<PbObject*>& getObjects() {return objects;}
		std::vector<PbLightSource>& getLightSource() {return lights;}
	
	
        float getTransparency() {return transparency;}

        bool saveXml();


	private:
	
        unsigned int width, height;

		PbCamera camera;
		PbPosition3d (&screenPlane)[4]; // order: upperLeft, lowerleft, lowerRight, upperRight
	
		std::vector<PbObject*> objects;
		std::vector<PbLightSource> lights;

		PbGraphics *renderer;
		
		PbColor4 backgroundColor;
		
        //std::ofstream out;

        float transparency;

        PbColor4 sendRay(PbPosition3d startPoint, PbPosition3d ray, unsigned int depth, int oldId);
        PbColor4 calculatePhongIlumination(PbPosition3d startPoint, PbPosition3d point, PbObject *object, int depth, int objId);
};

#endif // PB_SCENE_H
