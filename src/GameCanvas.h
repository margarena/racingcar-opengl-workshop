 /*
 * GameCanvas.h
 *
 *  Created on: May 6, 2020
 *      Author: noyan
 */
#ifndef GAMECANVAS_H_
#define GAMECANVAS_H_

#include "gBaseCanvas.h"
#include "gApp.h"
#include "gImage.h"
#include "gBox.h"
#include "gLight.h"
#include "gCamera.h"
#include "gModel.h"
#include "gSkybox.h"

class GameCanvas : public gBaseCanvas {
public:
	GameCanvas(gApp* root);
	virtual ~GameCanvas();

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void charPressed(unsigned int codepoint);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseScrolled(int x, int y);
	void mouseEntered();
	void mouseExited();
	void windowResized(int w, int h);
	void showNotify();
	void hideNotify();

private:
	enum {
		CHECKPOINTSPEC_NONE, CHECKPOINTSPEC_SPEEDUP, CHECKPOINTSPEC_SLOWDOWN, CHECKPOINTSPEC_FINISH
	};
	enum {
		CAMERA_BACK, CAMERA_TOP
	};

	static const int wheelnum = 4;
	static const int checkpointnum = 13;
	static const int cameranum = 2;

	gApp* root;
	gModel city;
	gLight light;
	gCamera camera[cameranum];
	bool wpressed, spressed;
	bool dpressed, apressed;
	bool spacepressed;
	gSkybox skybox;
	gModel car, aicar;
	gModel aiwheel[wheelnum];
	float carpanangle, carpananglediff;
	float speed, acceleration, deceleration, maxspeed;
	float camerapanangle;
	float carrollangle, carrollanglediff, carrollanglemax;
	float cartiltangle, cartiltanglediff, cartiltanglemax;
	float turbospeed, turboacceleration, turbodeceleration, turbomaxspeed;
	float totalspeed;
	float cameracardiff;
	void resetRotations();
	void userInteraction();
	void moveCar();
	void moveCamera();
	void moveAiCar();
	void checkCollisions();
	glm::vec3 startposition;
	glm::vec3 checkpoint[checkpointnum];
	gBox checkpointbox[checkpointnum];
	float aispeed;
	float aiwheeltiltangle, aiwheeltiltanglediff;
	int aitargetno;
	float aicarpanangle;
	int checkpointspecs[checkpointnum];
	bool gameover;
	gImage speedometer;
	int speedometerx, speedometery;
	gImage speedometerneedle;
	int speedometerneedlex, speedometerneedley;
	float speedometerneedleangle;
	gBoundingBox carbox, aicarbox;
	int camerano;
};

#endif /* GAMECANVAS_H_ */
