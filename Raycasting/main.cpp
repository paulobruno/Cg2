#include "pb_log.h"

#include "PbPosition3d.h"
#include "PbPosition4d.h"

#include "PbCamera.h"
#include "PbLightSource.h"

#include "PbSphere.h"
#include "PbPlane.h"
#include "PbCube.h"
#include "PbScene.h"
#include "PbCylinder.h"

#include "PbColor4.h"
#include "PbGraphics.h"
#include "PbQt.h"


#include <QTime>
#include <iostream>
#include <cstdlib>


int main(int argc, const char *argv[])
{
    srand(time(NULL));

	PbGraphics *renderer = new (std::nothrow) PbQt();
	
	if (!renderer)
	{
		LOGerr("Renderizador nao carregado. Programa abortado");
		return 1;
	}
	

    PbCamera camera(0, 0, -4.0, 0, 0, 0, 0, 1, 0);
	

	PbPosition3d screenPlane[4] =
	{
        PbPosition3d(-3.0f,  3.0f, 0.0f), // upperLeft
        PbPosition3d(-3.0f, -3.0f, 0.0f), // lowerLeft
        PbPosition3d( 3.0f, -3.0f, 0.0f), // lowerRight
        PbPosition3d( 3.0f,  3.0f, 0.0f), // upperRight
	}; // world coordinates

    PbLightSource light0;
    light0.setAmbient(0.01f, 0.01f, 0.01f);
    light0.setDiffuse(1.0f, 1.0f, 1.0f);
    light0.setSpecular(1.0f, 1.0f, 1.0f);
    light0.setPosition(-1.0f, 3.0f, -3.0f, 0.0f);
	
    PbLightSource light1;
    light1.setAmbient(0.01f, 0.01f, 0.01f);
    light1.setDiffuse(1.0f, 1.0f, 1.0f);
    light1.setSpecular(1.0f, 1.0f, 1.0f);
    light1.setPosition(20.0f, 20.0f, -1.0f, 0.0f);

    PbLightSource light2;
    light2.setAmbient(0.01f, 0.01f, 0.01f);
    light2.setDiffuse(1.0f, 1.0f, 1.0f);
    light2.setSpecular(1.0f, 1.0f, 1.0f);
    light2.setPosition(20.0f, -2.0f, -20.0f, 0.0f);

    PbSphere sphere("White.mtl", 0.0f, 0.0f, 0.0f, 1.0f);
    PbSphere sphere1("Green.mtl", 1.5f, 0.0f, 2.0f, 0.5f);

    PbPlane plane( "White.mtl", PbPosition3d(-3.0f, -3.0f, -3.0f), PbPosition3d( 3.0f, -3.0f, -3.0f), PbPosition3d( 3.0f, -3.0f,  3.0f)); // bottom
    PbPlane plane2("White.mtl", PbPosition3d(-3.0f, -3.0f,  3.0f), PbPosition3d( 3.0f, -3.0f,  3.0f), PbPosition3d( 3.0f,  3.0f,  3.0f)); // back
    PbPlane plane3(  "Red.mtl", PbPosition3d(-3.0f, -3.0f, -3.0f), PbPosition3d(-3.0f, -3.0f,  3.0f), PbPosition3d(-3.0f,  3.0f,  3.0f)); // left
    PbPlane plane4( "Blue.mtl", PbPosition3d( 3.0f, -3.0f,  3.0f), PbPosition3d( 3.0f, -3.0f, -3.0f), PbPosition3d( 3.0f,  3.0f, -3.0f)); // right
	
    // cube
    PbPlane face1("Yellow.mtl", PbPosition3d(-2.0f, -3.0f,  1.0f), PbPosition3d(-1.0f, -3.0f,  1.0f), PbPosition3d(-1.0f, -2.0f,  1.0f)); // front
    PbPlane face2("Yellow.mtl", PbPosition3d(-2.0f, -2.0f,  1.0f), PbPosition3d(-1.0f, -2.0f,  1.0f), PbPosition3d(-1.0f, -2.0f,  2.0f)); // top
    PbPlane face3("Yellow.mtl", PbPosition3d(-1.0f, -3.0f,  1.0f), PbPosition3d(-1.0f, -3.0f,  2.0f), PbPosition3d(-1.0f, -2.0f,  2.0f)); // right
    PbPlane face4("Yellow.mtl", PbPosition3d(-1.0f, -3.0f,  2.0f), PbPosition3d(-1.0f, -3.0f,  1.0f), PbPosition3d(-2.0f, -3.0f,  1.0f)); // bottom
    PbPlane face5("Yellow.mtl", PbPosition3d(-2.0f, -3.0f,  2.0f), PbPosition3d(-2.0f, -3.0f,  1.0f), PbPosition3d(-2.0f, -2.0f,  1.0f)); // left
    PbPlane face6("Yellow.mtl", PbPosition3d(-1.0f, -3.0f,  2.0f), PbPosition3d(-2.0f, -3.0f,  2.0f), PbPosition3d(-2.0f, -2.0f,  2.0f)); // back

    //PbCube cube("Yellow.mtl", face1, face2, face3, face4, face5, face6);

    PbCylinder cylinder("Grey.mtl", 2.0f, -1.5f, 0.0f, -2.0f, -1.0f);


	PbColor4 backColor = {0, 0, 0, 0};
	
	
    PbScene scene(camera, light0, screenPlane, renderer, backColor);

    //scene.addLightSource(light1);
    //scene.addLightSource(light2);

    scene.addObject(&cylinder);
    scene.addObject(&sphere);
    scene.addObject(&sphere1);

    scene.addObject(&face1);
    scene.addObject(&face2);
    scene.addObject(&face3);
    scene.addObject(&face4);
    scene.addObject(&face5);
    scene.addObject(&face6);

    //scene.addObject(&cube);

    sphere.setMirror();
    //plane2.setMirror();
    scene.addObject(&plane);  // bottom
    scene.addObject(&plane2); // back
    scene.addObject(&plane3); // left
    scene.addObject(&plane4); // right

    scene.saveXml();

    QTime myTimer;
    myTimer.start();

    scene.drawPhong("teste.png", 1280, 1280);

    int elapsed = myTimer.elapsed();

    std::cout << "time: " << (float)elapsed/1000.f << "s\n";

	return 0;
}
