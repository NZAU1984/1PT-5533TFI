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

	// TODO delete
	float _connectorAngle;

	float _motorAngle;

	glm::mat4 _leftMotorTransformationMatrix;
	glm::mat4 _rightMotorTransformationMatrix;

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

	float _positionZ = 0;

	float _positionX = 0;

	const float _minPositionZ = 0;
	const float _maxPositionZ = 75;

	const float _minPositionX = -15;
	const float _maxPositionX = 15;

	float _minStopAcceleratingX = 0;
	float _maxStopAcceleratingX = 0;

	float _minStopAcceleratingZ = 0;
	float _maxStopAcceleratingZ = 0;

	float _stopAcceleratingX = 0;
	float _stopAcceleratingZ = 0;

	float _stopAcceleratingFractionX = 6.0f / 15;
	float _stopAcceleratingFractionZ = 6.0f / 15;


	float _speedZ = 0;

	float _speedX = 0;

	const float _maxSpeedZ = 50;

	const float _maxSpeedX = 25;

	const float _accelerationZ = 25;

	const float _accelerationX = 25;

	float _currentAccelerationZ = 0;

	float _currentAccelerationX = 0;

	float _dragZ = 10;

	float _dragX = 10;

	float _maxMotorAngle = glm::pi<float>() / 6;

	float _deltaZperSecond = 25;

	float _deltaXperSecond = 15;

	void animateMotors();

	void animateFlames();

	void calculatePosition(double dt);

	bool isGoingForward();

	bool isGoingLeft();

	bool isGoingRight();

	bool isGoingBackward();

	bool isStillZ();

	bool isStillX();

	bool isAcceleratingForward();

	bool isAcceleratingLeft();

	bool isAcceleratingRight();

	bool isAcceleratingBackward();

	bool isNotAcceleratingZ();

	bool isNotAcceleratingX();

	// TEMP var below

	uint TEMP1 = 0;

	uint TEMP2 = 0;
};