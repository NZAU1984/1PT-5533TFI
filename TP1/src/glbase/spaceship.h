#pragma once

#include <main.h>

#include "scene.h"


using namespace glm;

class Spaceship
{
public:
	Spaceship();


	

	void render(double dt);

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

	enum _directionEnum {NO_CHANGE, LEFT, RIGHT, FORWARD, BACKWARD};

	_directionEnum _direction = NO_CHANGE;

	void animateFlames();
};