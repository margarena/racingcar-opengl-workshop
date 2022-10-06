/*
 * GameCanvas.cpp
 *
 *  Created on: May 6, 2020
 *      Author: noyan
 */


#include "GameCanvas.h"


GameCanvas::GameCanvas(gApp* root) : gBaseCanvas(root) {
	this->root = root;
}

GameCanvas::~GameCanvas() {
}

void GameCanvas::setup() {
	gLogi("GameCanvas") << "setup";
	startposition = glm::vec3(-2.25985f, 0.0f, 1.93712f);
	checkpoint[0] = glm::vec3(-2.28f, 0.0f, 1.71393f);
	checkpoint[1] = glm::vec3(1.94213f, 0.0f, 1.71393f);
	checkpoint[2] = glm::vec3(2.30032f, 0.0f, 1.84597f);
	checkpoint[3] = glm::vec3(2.64717f, 0.0f, 2.05659f);
	checkpoint[4] = glm::vec3(2.8664f, 0.0f, 2.56344f);
	checkpoint[5] = glm::vec3(2.89682f, 0.0f, 7.45056f);
	checkpoint[6] = glm::vec3(2.78631f, 0.0f, 9.17722f);
	checkpoint[7] = glm::vec3(2.63636, 0.0f, 9.55431f);
	checkpoint[8] = glm::vec3(2.31006f, 0.0f, 9.66568f);
	checkpoint[9] = glm::vec3(1.9656f, 0.0f, 9.59342f);
	checkpoint[10] = glm::vec3(0.59357f, 0.0f, 9.12293f );
	checkpoint[11] = glm::vec3(-3.79327f, 0.0f, 7.91141f);
	checkpoint[12] = glm::vec3(-5.15253f, 0.0f, 7.59074f);
	city.loadModel("city/gmae.obj");
	light.setSpecularColor(5, 5, 5);
	light.setDiffuseColor(200, 200, 200);
	light.setAmbientColor(200, 200, 200);
	camera[CAMERA_BACK].boom(0.15f);
	light.boom(50.0f);
	light.dolly(20.0f);
	wpressed = false;
	spressed = false;
	apressed = false;
	dpressed = false;
	spacepressed = false;
	std::vector<std::string> skyboxtextures;
	skyboxtextures.push_back("skymap/right.jpg");
	skyboxtextures.push_back("skymap/left.jpg");
	skyboxtextures.push_back("skymap/top.jpg");
	skyboxtextures.push_back("skymap/bottom.jpg");
	skyboxtextures.push_back("skymap/front.jpg");
	skyboxtextures.push_back("skymap/back.jpg");
	skybox.loadTextures(skyboxtextures);
	skybox.pan(PI);
	car.loadModel("Mercedes-Benz_SLS_AMG/Mercedes_AMG_GT3.obj");
	car.scale(0.06f);
	car.pan(PI / 2);
	car.setPosition(startposition);
	aicar.loadModel("Audi_RS4/Audi_RS4b.obj");
	aicar.scale(0.033f);
	aicar.truck(0.2f);
	aicar.setPosition(checkpoint[0]);
	aicar.pan(-PI / 2);
	for(int i = 0; i < wheelnum; i++) {
		aiwheel[i].loadModel("Audi_RS4/Audi_RS4b_wheel.obj");
		aiwheel[i].scale(0.033f);
		aiwheel[i].setPosition(checkpoint[0]);
		aiwheel[i].pan(-PI / 2);
	}
	aiwheel[2].pan(PI);
	aiwheel[3].pan(PI);

	aiwheel[0].truck(-0.0486594f);
	aiwheel[0].boom(0.0210354f);
	aiwheel[0].dolly(-0.10158554f);

	aiwheel[1].truck(-0.0486594f);
	aiwheel[1].boom(0.0210354f);
	aiwheel[1].dolly(0.06652f);

	aiwheel[2].truck(-0.0498114f);
	aiwheel[2].boom(0.0210354f);
	aiwheel[2].dolly(0.10158554f);

	aiwheel[3].truck(-0.0498114f);
	aiwheel[3].boom(0.0210354f);
	aiwheel[3].dolly(-0.06652f);

	camera[CAMERA_BACK].setPosition(0.0f, 0.12f, 0.3f);
	camera[CAMERA_BACK].pan(-PI / 2);
	camera[CAMERA_TOP].boom(2.0f);
	camera[CAMERA_TOP].tilt(-PI / 2.0f);
	camera[CAMERA_TOP].roll(-PI / 2.0f);
	carpanangle = 0.0f;
	carpananglediff = 0.03f;
	speed = 0.0f;
	maxspeed = 0.06f;
	acceleration = 0.001f;
	deceleration = acceleration * 2.0f;
	turbospeed = 0.0f;
	turboacceleration = 1.5f * acceleration;
	turbodeceleration = turboacceleration * 0.5f;
	turbomaxspeed = 0.5f * maxspeed;
	camerapanangle = 0.0f;
	carrollangle = 0.0f;
	carrollanglemax = 0.04f;
	carrollanglediff = carrollanglemax / 10.0f;
	cartiltangle = 0.0f;
	cartiltanglemax = 0.02f;
	cartiltanglediff = cartiltanglemax / 10.0f;
	totalspeed = 0.0f;
	cameracardiff = 0.0f;
	for(int i = 0; i < checkpointnum; i++) {
		checkpointbox[i].setPosition(checkpoint[i]);
		checkpointbox[i].scale(0.05f);
	}
	aispeed = 0.01f;
	aiwheeltiltangle = 0.0f;
	aitargetno = 0;
	aicarpanangle = 0.0f;
	for(int i = 0; i < checkpointnum; i++) checkpointspecs[i] = CHECKPOINTSPEC_NONE;
	checkpointspecs[0] = CHECKPOINTSPEC_SPEEDUP;
	checkpointspecs[1] = CHECKPOINTSPEC_SLOWDOWN;
	checkpointspecs[4] = CHECKPOINTSPEC_SPEEDUP;
	checkpointspecs[6] = CHECKPOINTSPEC_SLOWDOWN;
	checkpointspecs[10] = CHECKPOINTSPEC_SPEEDUP;
	checkpointspecs[11] = CHECKPOINTSPEC_FINISH;
	gameover = false;
	speedometer.loadImage("speedometer_320.png");
	speedometerx = getWidth() / 20;
	speedometery = getHeight() - speedometer.getHeight() - getWidth() / 10;
	speedometerneedle.loadImage("speedometer_arrow_320.png");
	speedometerneedlex = speedometerx + (speedometer.getWidth() - speedometerneedle.getWidth()) / 2;
	speedometerneedley = speedometery;
	speedometerneedleangle = -90.0f;
	carbox = car.getBoundingBox();
	aicarbox = aicar.getBoundingBox();
	camerano = CAMERA_BACK;
}


void GameCanvas::update() {
	resetRotations();
	userInteraction();
	moveCar();
	moveCamera();
	moveAiCar();
	checkCollisions();
}

void GameCanvas::draw() {

	camera[camerano].begin();
	enableDepthTest();
	light.enable();
	skybox.draw();
	city.draw();
	enableAlphaBlending();
	setColor(255, 0, 0, 64);
	for(int i = 0; i < checkpointnum; i++) {
		checkpointbox[i].draw();
	}
	disableAlphaBlending();
	setColor(255, 255, 255);
	car.draw();
	aicar.draw();
	for(int i = 0; i < wheelnum; i++) {
		aiwheel[i].draw();
	}
	light.disable();
	disableDepthTest();
	camera[camerano].end();
	speedometer.draw(speedometerx, speedometery);
	speedometerneedle.draw(speedometerneedlex, speedometerneedley, speedometerneedle.getWidth(), speedometerneedle.getHeight(), speedometerneedle.getWidth() / 2, speedometerneedle.getHeight() - 10,  speedometerneedleangle);

}

void GameCanvas::resetRotations() {
	car.tilt(-cartiltangle);
	car.roll(-carrollangle);
	car.pan(-carpanangle);
	camera[CAMERA_BACK].pan(-camerapanangle);
	camera[CAMERA_TOP].roll(-carpanangle);
	aiwheel[0].tilt(aiwheeltiltangle);
	aiwheel[1].tilt(aiwheeltiltangle);
	aiwheel[2].tilt(-aiwheeltiltangle);
	aiwheel[3].tilt(-aiwheeltiltangle);
	for(int i = 0; i < wheelnum; i++) aiwheel[i].pan(-aicarpanangle);
	aicar.pan(-aicarpanangle);

}

void GameCanvas::userInteraction() {
	if(wpressed == true) {
			speed += acceleration;
			if(speed >= maxspeed) speed = maxspeed;
			cartiltangle -= cartiltanglediff;
			if(cartiltangle <= -cartiltanglemax) cartiltangle = -cartiltanglemax;
		} else if(spressed == true) {
			speed -= deceleration;
			if(speed <= 0.0f) speed = 0.0f;
			cartiltangle += cartiltanglediff;
			if(cartiltangle >= cartiltanglemax) cartiltangle = cartiltanglemax;
		} else {
			speed -= 0.2f * deceleration;
			if(speed <= 0.0f) speed = 0.0f;
		}

		if (spacepressed) {
			turbospeed += turboacceleration;
			if (turbospeed >= turbomaxspeed) turbospeed = turbomaxspeed;
		} else {
			turbospeed -= turbodeceleration;
			if (turbospeed <= 0.0f) turbospeed = 0.0f;
		}
		totalspeed = speed + turbospeed;

		if(dpressed == true && speed > 0.0f) {
			carpanangle -= carpananglediff;
			camerapanangle -= carpananglediff * 0.8f;
			carrollangle -= carrollanglediff;
			if(carrollangle <= -carrollanglemax) carrollangle = -carrollanglemax;

		} else if(apressed == true && speed > 0.0f) {
			carpanangle += carpananglediff;
			camerapanangle += carpananglediff * 0.8f;
			carrollangle += carrollanglediff;
			if(carrollangle >= carrollanglemax) carrollangle = carrollanglemax;
		}
}

void GameCanvas::moveCar() {
	car.pan(carpanangle);
	car.dolly(totalspeed);
	carrollangle *= 0.9f;
	car.roll(carrollangle);
	cartiltangle *= 0.9f;
	car.tilt(cartiltangle);
	speedometerneedleangle = -90.0f + 240.0f * totalspeed / (maxspeed + turbomaxspeed);
	carbox = car.getBoundingBox();
}

void GameCanvas::moveCamera() {
	cameracardiff = 0.3f + totalspeed * 0.35f;
	camerapanangle += (carpanangle - camerapanangle) * 0.05f;
	camera[CAMERA_BACK].setPosition(car.getPosX(), car.getPosY(), car.getPosZ());
	camera[CAMERA_BACK].pan(camerapanangle);
	camera[CAMERA_BACK].boom(0.12f);
	camera[CAMERA_BACK].dolly(cameracardiff);

	camera[CAMERA_TOP].setPosition(car.getPosX(), car.getPosY(), car.getPosZ());
	camera[CAMERA_TOP].dolly(2.0f);
	camera[CAMERA_TOP].roll(carpanangle);
	camera[CAMERA_TOP].boom(0.6f);
}

void GameCanvas::moveAiCar() {
	float distance = std::sqrt(std::pow(checkpoint[aitargetno].x - aicar.getPosX(), 2) + std::pow(checkpoint[aitargetno].z - aicar.getPosZ(), 2));

	if(checkpointspecs[aitargetno] == CHECKPOINTSPEC_SLOWDOWN && distance < maxspeed * 10.0f) {
		aispeed -= deceleration * 1.2f;
		if(aispeed < 0.0f) aispeed = 0.0f;
	} else {
		if(checkpointspecs[aitargetno - 1] == CHECKPOINTSPEC_SPEEDUP) {
			aispeed += acceleration / 2.0f;
			if(aispeed > maxspeed) aispeed = maxspeed;
		} else if(checkpointspecs[aitargetno - 1] == CHECKPOINTSPEC_FINISH) {
			aispeed -= deceleration;
			if(aispeed < 0.0f) aispeed = 0.0f;
			gLogi("GameCanvas") << "GAME OVER";
			gameover = true;
		}
	}

	if(aicar.getPosX() >= checkpoint[aitargetno].x - aispeed && aicar.getPosX() <= checkpoint[aitargetno].x + aispeed &&
		aicar.getPosZ() >= checkpoint[aitargetno].z - aispeed && aicar.getPosZ() <= checkpoint[aitargetno].z + aispeed) {
		aitargetno++;
		float targetangle = -std::atan2(checkpoint[aitargetno].z - aicar.getPosZ(), checkpoint[aitargetno].x - aicar.getPosX());
		aicarpanangle = targetangle;
	}

	aicar.pan(aicarpanangle);
	aicar.dolly(-aispeed);

	for(int i = 0; i < wheelnum; i++) aiwheel[i].setPosition(aicar.getPosition());
	for(int i = 0; i < wheelnum; i++) aiwheel[i].pan(aicarpanangle);
	aiwheel[0].truck(-0.0486594f);
	aiwheel[0].boom(0.0210354f);
	aiwheel[0].dolly(-0.10158554f);

	aiwheel[1].truck(-0.0486594f);
	aiwheel[1].boom(0.0210354f);
	aiwheel[1].dolly(0.06652f);

	aiwheel[2].truck(-0.0498114f);
	aiwheel[2].boom(0.0210354f);
	aiwheel[2].dolly(0.10158554f);

	aiwheel[3].truck(-0.0498114f);
	aiwheel[3].boom(0.0210354f);
	aiwheel[3].dolly(-0.06652f);


	aiwheeltiltanglediff = 0.6f * aispeed / maxspeed;
	aiwheeltiltangle += aiwheeltiltanglediff;
	aiwheel[0].tilt(-aiwheeltiltangle);
	aiwheel[1].tilt(-aiwheeltiltangle);
	aiwheel[2].tilt(aiwheeltiltangle);
	aiwheel[3].tilt(aiwheeltiltangle);
	aicarbox = aicar.getBoundingBox();
}

void GameCanvas::checkCollisions() {
	if(aicarbox.intersects(carbox)) {
		//gLogi("GameCanvas") << "Collision Detected";
		speed = aispeed;
		aicar.dolly(-0.02f);
	}
}

void GameCanvas::keyPressed(int key) {
//	gLogi("GameCanvas") << "keyPressed:" << key;
	if(key == 256) exit(0);

	if(key == 87) wpressed = true;
	if(key == 83) spressed = true;
	if(key == 68) dpressed = true;
	if(key == 65) apressed = true;
	if(key == 32) spacepressed = true;

	if(key == 49) camerano = CAMERA_BACK;
	else if(key == 50) camerano = CAMERA_TOP;
}

void GameCanvas::keyReleased(int key) {
//	gLogi("GameCanvas") << "keyReleased:" << key;

	if(key == 87) wpressed = false;
	if(key == 83) spressed = false;
	if(key == 68) dpressed = false;
	if(key == 65) apressed = false;
	if (key == 32) spacepressed = false;
}

void GameCanvas::charPressed(unsigned int codepoint) {
//	gLogi("GameCanvas") << "charPressed:" << gCodepointToStr(codepoint);
}

void GameCanvas::mouseMoved(int x, int y) {
//	gLogi("GameCanvas") << "mouseMoved" << ", x:" << x << ", y:" << y;
}

void GameCanvas::mouseDragged(int x, int y, int button) {
//	gLogi("GameCanvas") << "mouseDragged" << ", x:" << x << ", y:" << y << ", b:" << button;
}

void GameCanvas::mousePressed(int x, int y, int button) {
}

void GameCanvas::mouseReleased(int x, int y, int button) {
//	gLogi("GameCanvas") << "mouseReleased" << ", button:" << button;
}

void GameCanvas::mouseScrolled(int x, int y) {
//	gLogi("GameCanvas") << "mouseScrolled" << ", x:" << x << ", y:" << y;
}

void GameCanvas::mouseEntered() {
}

void GameCanvas::mouseExited() {
}

void GameCanvas::windowResized(int w, int h) {
}

void GameCanvas::showNotify() {

}

void GameCanvas::hideNotify() {

}

