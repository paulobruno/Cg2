// 2013, PAULO BRUNO DE SOUSA SERAFIM, Fortaleza - CE, Brasil


#include "PbCamera.h"


PbCamera::PbCamera()
{
    eye.set_pos(0.0f, 0.0f, -1.0f);
    lookAt.set_pos(0.0f, 0.0f, 0.0f);
    viewUp.set_pos(0.0f, 1.0f, -1.0f);

    this->createMatrix();
}


PbCamera :: PbCamera(PbPosition3d camEye, PbPosition3d camLookAt)
    : eye(camEye),
      lookAt(camLookAt)
{
	viewUp = camEye;
    viewUp.set_y(viewUp.get_y() + 1.0f);

	this->createMatrix();
}


PbCamera :: PbCamera(PbPosition3d camEye, PbPosition3d camLookAt, PbPosition3d camViewUp)
    : eye(camEye),
      lookAt(camLookAt),
      viewUp(camViewUp)
{
	this->createMatrix();
}


PbCamera :: PbCamera(double eye_x, double eye_y, double eye_z,
                     double lookAt_x, double lookAt_y, double lookAt_z)
{
    eye.set_pos(eye_x, eye_y, eye_z);
    lookAt.set_pos(lookAt_x, lookAt_y, lookAt_z);
    viewUp.set_pos(eye_x, eye_y + 1.0f, eye_z);

    this->createMatrix();
}


PbCamera :: PbCamera(double eye_x, double eye_y, double eye_z,
                     double lookAt_x, double lookAt_y, double lookAt_z,
                     double viewUp_x, double viewUp_y, double viewUp_z)
{
    eye.set_pos(eye_x, eye_y, eye_z);
    lookAt.set_pos(lookAt_x, lookAt_y, lookAt_z);
    viewUp.set_pos(viewUp_x, viewUp_y, viewUp_z);

	this->createMatrix();
}


void PbCamera :: updateEye(PbPosition3d camEye)
{
	eye = camEye;
	this->createMatrix();
}


void PbCamera :: updateEye(double x, double y, double z)
{
    eye.set_pos(x, y, z);
	this->createMatrix();
}


void PbCamera :: updateLookAt(PbPosition3d camLookAt)
{
	lookAt = camLookAt;
	this->createMatrix();
}


void PbCamera :: updateLookAt(double x, double y, double z)
{
    lookAt.set_pos(x, y, z);
	this->createMatrix();
}


void PbCamera :: updateViewUp(PbPosition3d camViewUp)
{
	viewUp = camViewUp;
	this->createMatrix();
}


void PbCamera :: updateViewUp(double x, double y, double z)
{
    viewUp.set_pos(x, y, z);
	this->createMatrix();
}


void PbCamera :: updateCamera(PbPosition3d camEye, PbPosition3d camLookAt)
{
	eye = camEye;
	lookAt = camLookAt;

	viewUp = camEye;
    viewUp.set_y(viewUp.get_y() + 1.0f);

	this->createMatrix();
}


void PbCamera :: updateCamera(PbPosition3d camEye, PbPosition3d camLookAt, PbPosition3d camViewUp)
{
	eye = camEye;
	lookAt = camLookAt;
	viewUp = camViewUp;

	this->createMatrix();
}


void PbCamera :: updateCamera(double eye_x, double eye_y, double eye_z,
                              double lookAt_x, double lookAt_y, double lookAt_z)
{
    eye.set_pos(eye_x, eye_y, eye_z);
    lookAt.set_pos(lookAt_x, lookAt_y, lookAt_z);
    viewUp.set_pos(eye_x, eye_y + 1.0f, eye_z);

    this->createMatrix();
}


void PbCamera :: updateCamera(double eye_x, double eye_y, double eye_z,
                              double lookAt_x, double lookAt_y, double lookAt_z,
                              double viewUp_x, double viewUp_y, double viewUp_z)
{
    eye.set_pos(eye_x, eye_y, eye_z);
    lookAt.set_pos(lookAt_x, lookAt_y, lookAt_z);
    viewUp.set_pos(viewUp_x, viewUp_y, viewUp_z);

    this->createMatrix();
}


void PbCamera :: createMatrix()
{
	PbPosition3d i, j, k, auxVector;

    // vector of z axis
	k = eye - lookAt;
	k.normalize();

    // vector of y axis
	auxVector = viewUp - eye;

	// i = aux x k
	i = auxVector.crossProduct(k);
	i.normalize();

    // vector of x axis, j = k x i
	j = k.crossProduct(i);

    // matrix of transformation
    matrix[0]  = i.get_x();
    matrix[1]  = j.get_x();
    matrix[2]  = k.get_x();
    matrix[3]  = 0.0;

    matrix[4]  = i.get_y();
    matrix[5]  = j.get_y();
    matrix[6]  = k.get_y();
    matrix[7]  = 0.0;

    matrix[8]  = i.get_z();
    matrix[9]  = j.get_z();
    matrix[10] = k.get_z();
    matrix[11] = 0.0;

    matrix[12] = -i.dotProduct(eye);
    matrix[13] = -j.dotProduct(eye);
    matrix[14] = -k.dotProduct(eye);
    matrix[15] = 1.0;
}


PbCamera& PbCamera :: operator= (const PbCamera &cam)
{
	if (this != &cam)
	{
        for (int i = 0; i < 16; i++)
            matrix[i] = cam.matrix[i];

		eye = cam.eye;
		lookAt = cam.lookAt;
		viewUp = cam.viewUp;
	}

	return *this;
}
