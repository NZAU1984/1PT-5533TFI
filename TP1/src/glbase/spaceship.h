#pragma once

#include <main.h>

#include "scene.h"


using namespace glm;

class Spaceship
{
public:
	Spaceship();

	void render(double dt);

	void goForward();
	void goLeft();
	void goRight();
	void goBackward();

	void stopGoingForward();
	void stopGoingLeft();
	void stopGoingRight();
	void stopGoingBackward();

protected:
	// TODO add underscores...
	Box mainBody;
	Box leftConnector;
	Box rightConnector;

	Cylinder leftMotor;
	Cylinder rightMotor;

	Cylinder leftMotorOuterFlame;
	Cylinder rightMotorOuterFlame;

	Cylinder leftMotorInnerFlame;
	Cylinder rightMotorInnerFlame;

	Cylinder trunk;

	Box leftFin;
	Box rightFin;

	float angle;

	glm::mat4 _leftMotorOuterFlameTransformationMatrix;
	glm::mat4 _rightMotorOuterFlameTransformationMatrix;
	glm::mat4 _leftMotorInnerFlameTransformationMatrix;
	glm::mat4 _rightMotorInnerFlameTransformationMatrix;

	uint DIRECTION_NO_CHANGE = 0;
	uint DIRECTION_FORWARD = 1 << 0;
	uint DIRECTION_LEFT = 1 << 1;
	uint DIRECTION_RIGHT = 1 << 2;
	uint DIRECTION_BACKWARD = 1 << 3;

	uint _direction = DIRECTION_NO_CHANGE;

	float _deltaZperSecond = 25;

	float _positionZ = 0;

	float _deltaXperSecond = 15;

	float _positionX = 0;

	void animateFlames();

	void calculatePosition(double dt);
};