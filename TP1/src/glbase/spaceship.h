#pragma once

#include <main.h>

#include "scene.h"

#include "ThreeDObject.h"

#include <vector>


using namespace glm;

class Spaceship : public ThreeDObject
{
public:
	Spaceship();

	virtual ~Spaceship();

	void render(double dt);

	void goForward();
	void goLeft();
	void goRight();
	void goBackward();

	void stopGoingForward();
	void stopGoingLeft();
	void stopGoingRight();
	void stopGoingBackward();

	void resetPosition();

	std::vector<glm::vec3> getPosition();

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

	double _motorAngle;

	double _maxMotorAngleDeltaPerSecond = glm::pi<double>();

	glm::mat4 _leftMotorTransformationMatrix;
	glm::mat4 _rightMotorTransformationMatrix;

	glm::mat4 _leftMotorOuterFlameTransformationMatrix;
	glm::mat4 _rightMotorOuterFlameTransformationMatrix;
	glm::mat4 _leftMotorInnerFlameTransformationMatrix;
	glm::mat4 _rightMotorInnerFlameTransformationMatrix;

	bool _goingForwardKeyDown  = false;
	bool _goingLeftKeyDown     = false;
	bool _goingRightKeyDown    = false;
	bool _goingBackwardKeyDown = false;

	bool _forceForwardMotors    = false;
	bool _forceLeftMotor        = false;
	bool _forceRightMotor       = false;
	bool _forceBackwardMotors   = false;

	double _positionZ = 0;

	double _positionX = 0;

	const double _minPositionZ = 0;
	const double _maxPositionZ = 75;

	const double _minPositionX = -15;
	const double _maxPositionX = 15;

	double _minStopAcceleratingX = 0;
	double _maxStopAcceleratingX = 0;

	double _minStopAcceleratingZ = 0;
	double _maxStopAcceleratingZ = 0;

	double _stopAcceleratingX = 0;
	double _stopAcceleratingZ = 0;

	double _speedZ = 0;

	double _speedX = 0;

	const double _maxSpeedZ = 50;

	const double _maxSpeedX = 25;

	const double _accelerationZ = 25;

	const double _accelerationX = 25;

	double _currentAccelerationZ = 0;

	double _currentAccelerationX = 0;

	double _dragZ = 10;

	double _dragX = 10;

	double _maxMotorAngle = glm::pi<double>() / 6;

	double _deltaZperSecond = 25;

	double _deltaXperSecond = 15;

	void animateMotors(double dt);

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