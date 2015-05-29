// 2013, PAULO BRUNO DE SOUSA SERAFIM, Fortaleza - CE, Brasil


#ifndef PB_CAMERA_H
#define PB_CAMERA_H


#include <cmath>

#include "PbPosition3d.h"


class PbCamera 
{
    public:
    
		explicit PbCamera(PbPosition3d camEye, PbPosition3d camLookAt);
		explicit PbCamera(PbPosition3d camEye, PbPosition3d camLookAt, PbPosition3d camViewUp);

        explicit PbCamera(double eye_x, double eye_y, double eye_z,
                 		  double lookAt_x, double lookAt_y, double lookAt_z);
		explicit PbCamera(double eye_x, double eye_y, double eye_z, 
                          double lookAt_x, double lookAt_y, double lookAt_z,
                 		  double viewUp_x, double viewUp_y, double viewUp_z);

        virtual ~PbCamera() {}


		void updateEye(PbPosition3d camEye);
		void updateEye(double x, double y, double z);

		void updateLookAt(PbPosition3d camLookAt);
		void updateLookAt(double x, double y, double z);

		void updateViewUp(PbPosition3d camViewUp);
		void updateViewUp(double x, double y, double z);

		void updateCamera(PbPosition3d camEye, PbPosition3d camLookAt);
		void updateCamera(PbPosition3d camEye, PbPosition3d camLookAt, PbPosition3d camViewUp);
        void updateCamera(double eye_x, double eye_y, double eye_z,
                          double lookAt_x, double lookAt_y, double lookAt_z);
        void updateCamera(double eye_x, double eye_y, double eye_z,
                          double lookAt_x, double lookAt_y, double lookAt_z,
                          double viewUp_x, double viewUp_y, double viewUp_z);

		
		PbPosition3d getEye() {return eye;}
		PbPosition3d getLookAt() {return lookAt;}
		PbPosition3d getViewUp() {return viewUp;}

        double* getMatrix() {return matrix;}


		PbCamera& operator= (const PbCamera &cam);


	private:
	
        double matrix[16];
        PbPosition3d eye, lookAt, viewUp;

        void createMatrix();
};


#endif // PB_CAMERA_H
