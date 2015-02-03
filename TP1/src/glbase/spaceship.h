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
};