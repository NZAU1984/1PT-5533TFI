#include "spaceship.h"

#include "glm/gtx/transform2.hpp"

// TODO remove unnecessary 'mat4()' in transformation matrices

float connectorShearXfractionOfY = -0.5f;
float connectorShearZfractionOfY = 0.5f;
float finShearZFractionOfX       = -0.5f;

glm::mat4 rotation90degAroundX(glm::rotate(glm::mat4(), glm::pi<float>() / 2, vec3(1, 0, 0)));

glm::mat4 rotation90degAroundY(glm::rotate(glm::mat4(), glm::pi<float>(), vec3(0, 1, 0)));

glm::mat4 connectorShear
{
	1, 0, 0, 0,
	connectorShearXfractionOfY, 1, connectorShearZfractionOfY, 0, // x = x - 0.5y ; z = z + 0.5y
	0, 0, 1, 0,
	0, 0, 0, 1
};

glm::mat4 finShear
{
	1, 0, finShearZFractionOfX, 0, // z = z - 0.5x
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

glm::mat4 flipX
{
	-1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

glm::mat4 flipY
{
	1, 0, 0, 0,
	0, -1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

glm::mat4 flipZ
{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, -1, 0,
	0, 0, 0, 1
};

glm::vec4 mainBodyColor = vec4(1.0f, 0, 0, 1.0f);

float mainBodyWidth  = 1;
float mainBodyHeight = 0.5f;
float mainBodyDepth  = 3;

glm::vec4 connectorColor = vec4(0, 1, 0, 1.0f);

float connectorWidth  = 0.3f;
float connectorHeight = 2;
float connectorDepth  = 1;

float connectorWidthAfterShear  = connectorWidth + abs(connectorShearXfractionOfY) * connectorHeight;
float connectorHeightAfterShear = connectorHeight;
float connectorDepthAfterShear  = connectorDepth + abs(connectorShearZfractionOfY) * connectorHeight;

float connectorTranslationX = (connectorWidthAfterShear / 2) - connectorWidth + (mainBodyWidth / 2);
float connectorTranslationY = -((connectorHeightAfterShear + mainBodyHeight) / 2);
float connectorTranslationZ = (connectorDepthAfterShear - mainBodyDepth) / 2;

glm::vec4 motorColor = vec4(0, 1, 1, 1);

float motorHeight = 3.5f;
float motorRadius = 0.3f;

float connectorSpaceVisibleUnderMotor = 0.2f;

float motorTranslationX = connectorTranslationX + connectorWidthAfterShear / 2 - motorRadius / 2
	- connectorSpaceVisibleUnderMotor;
float motorTranslationY = connectorTranslationY - connectorHeightAfterShear / 2 + motorRadius / 2
	+ connectorSpaceVisibleUnderMotor;
float motorTranslationZ = -1.0f;

glm::vec4 outerMotorFlameColor = vec4(1, 0, 1, 0.7f); //vec4(1, 0, 0, 0.5f);

float outerMotorFlameHeight = 0.4f; //0.5f * 0.7f;
float outerMotorFlameRadius = motorRadius * 0.7f; //;motorRadius * 0.3f;

float outerMotorFlameTranslationX = 0;
float outerMotorFlameTranslationY = 0;
float outerMotorFlameTranslationZ = -((motorHeight + outerMotorFlameHeight) / 2) + 0.01f; // '+ 0.01f' to prevent image from flickering...

glm::vec4 innerMotorFlameColor = vec4(1, 0, 0, 1.0f);

float innerMotorFlameHeight = outerMotorFlameHeight;
float innerMotorFlameRadius = motorRadius * 0.3f;

glm::vec4 trunkColor = vec4(0, 1, 1, 1);

float trunkWidth  = 1;
float trunkHeight = 1;
float trunkDepth  = 3;

float trunkRadius = 0.5f;

float trunkScaleX = 0.3f;
float trunkScaleY = 1;
float trunkScaleZ = 1;

float trunkTranslationX = 0;
float trunkTranslationY = 0;
float trunkTranslationZ = trunkDepth / 2;

glm::vec4 finColor = vec4(1, 1, 0, 1.0f);

float finWidth  = 1.25f;
float finHeight = 0.5f;
float finDepth  = 1;

float finWidthAfterShear  = finWidth;
float finHeightAfterShear = finHeight;
float finDepthAfterShear  = finDepth + abs(finShearZFractionOfX) * finWidth;

float finTranslationX = finWidthAfterShear / 2;
float finTranslationY = 0;
float finTranslationZ = trunkTranslationZ * 2 - finDepthAfterShear / 2 + 0.2f;

glm::mat4 mainBodyTransformationMatrix = glm::scale(glm::mat4(), vec3(mainBodyWidth, mainBodyHeight, mainBodyDepth));

glm::mat4 leftConnectorTransformationMatrix = glm::translate(glm::mat4(),
	vec3(connectorTranslationX, connectorTranslationY, connectorTranslationZ))
	* connectorShear 
	* glm::scale(glm::mat4(), vec3(connectorWidth, connectorHeight, connectorDepth));

glm::mat4 leftMotorTransformationMatrix_part1 = rotation90degAroundX;

glm::mat4 leftMotorTransformationMatrix = rotation90degAroundX;

/*glm::mat4 leftMotorTransformationMatrix = glm::translate(glm::mat4(),
	vec3(motorTranslationX, motorTranslationY, motorTranslationZ))
	* rotation90degAroundX;*/

glm::mat4 leftMotorOuterFlameTransformationMatrix = rotation90degAroundX;

/*glm::mat4 leftMotorOuterFlameTransformationMatrix = glm::translate(glm::mat4(),
	vec3(outerMotorFlameTranslationX, outerMotorFlameTranslationY, outerMotorFlameTranslationZ))
	* leftMotorTransformationMatrix;*/

glm::mat4 leftMotorInnerFlameTransformationMatrix = rotation90degAroundX;// leftMotorOuterFlameTransformationMatrix;

glm::mat4 trunkTransformationMatrix = glm::translate(glm::mat4(),
	vec3(trunkTranslationX, trunkTranslationY, trunkTranslationZ))
	* glm::scale(glm::mat4(), vec3(trunkScaleX, trunkScaleY, trunkScaleZ))
	* rotation90degAroundX;

glm::mat4 leftFinTransformationMatrix = glm::translate(glm::mat4(),
	vec3(finTranslationX, finTranslationY, finTranslationZ))
	* finShear
	* glm::scale(glm::mat4(), vec3(finWidth, finHeight, finDepth));

Spaceship::Spaceship() :
	angle(0),

	_connectorAngle(0),

	mainBody(mainBodyColor, mainBodyTransformationMatrix),

	leftConnector(connectorColor, leftConnectorTransformationMatrix),
	rightConnector(connectorColor, flipX * leftConnectorTransformationMatrix),

	leftMotor(motorColor, 100, motorHeight, motorRadius, leftMotorTransformationMatrix),
	rightMotor(motorColor, 100, motorHeight, motorRadius, flipX * leftMotorTransformationMatrix), // WARNING

	leftMotorOuterFlame(outerMotorFlameColor, 100, outerMotorFlameHeight, outerMotorFlameRadius, 
		leftMotorOuterFlameTransformationMatrix),
	rightMotorOuterFlame(outerMotorFlameColor, 100, outerMotorFlameHeight, outerMotorFlameRadius, 
		flipX * leftMotorOuterFlameTransformationMatrix),

	leftMotorInnerFlame(innerMotorFlameColor, 100, innerMotorFlameHeight, innerMotorFlameRadius,
		leftMotorInnerFlameTransformationMatrix),
	rightMotorInnerFlame(innerMotorFlameColor, 100, innerMotorFlameHeight, innerMotorFlameRadius,
		flipX * leftMotorInnerFlameTransformationMatrix),

	trunk(trunkColor, 100, trunkDepth, trunkRadius, trunkTransformationMatrix),

	leftFin(finColor, leftFinTransformationMatrix),
	rightFin(finColor, flipX * leftFinTransformationMatrix)
{
	leftMotor.AddChild(&leftMotorInnerFlame);
	rightMotor.AddChild(&rightMotorInnerFlame);

	leftMotor.AddChild(&leftMotorOuterFlame);
	rightMotor.AddChild(&rightMotorOuterFlame);

	leftConnector.AddChild(&leftMotor);
	rightConnector.AddChild(&rightMotor);

	trunk.AddChild(&leftFin);
	trunk.AddChild(&rightFin);

	mainBody.AddChild(&leftConnector);
	mainBody.AddChild(&rightConnector);

	mainBody.AddChild(&trunk);
}

void Spaceship::render(double dt)
{

	/*mainBody.SetTransform(glm::rotate(
		glm::scale(
			glm::translate(glm::mat4(), vec3(0, -2.5f, 0)), 
			vec3(0.2f, 0.2f, 0.2f)
		),
		0.0f, vec3(1, 0, 0)));*/

	animateMotors();

	animateFlames();

	calculatePosition(dt);

	leftMotorOuterFlame.SetTransform(_leftMotorOuterFlameTransformationMatrix);
	rightMotorOuterFlame.SetTransform(_rightMotorOuterFlameTransformationMatrix);
	leftMotorInnerFlame.SetTransform(_leftMotorInnerFlameTransformationMatrix);
	rightMotorInnerFlame.SetTransform(_rightMotorInnerFlameTransformationMatrix);

	leftMotor.SetTransform(_leftMotorTransformationMatrix);
	rightMotor.SetTransform(_rightMotorTransformationMatrix);

	//mainBody.SetTransform(glm::scale(glm::mat4(), vec3(0.3f, 0.3f, 0.3f)));
	//mainBody.SetTransform(glm::scale(glm::rotate(glm::mat4(), angle, vec3(0,1,0)), vec3(0.5f, 0.5f, 0.5f)));	 // -glm::pi<float>()/7
	//mainBody.SetTransform(glm::rotate(glm::mat4(), angle, vec3(0,1,0)));
	
	//_positionZ += 0.01f;

	mainBody.SetTransform(glm::translate(glm::mat4(), vec3(_positionX, 0, _positionZ)));
	
	/*mainBody.SetTransform(
		glm::translate(glm::mat4(), vec3(0,30,-8))
		*
		glm::scale(glm::mat4(), vec3(2.0f, 2.0f, 2.0f))
		*
		glm::rotate(glm::mat4(), angle, vec3(1,0,0))
		); // _pos..., 5, -5*/
	
	/*
	glm::rotate(
		glm::rotate(glm::mat4(), 0.0f, vec3(1,0,0))
		, glm::pi<float>()/2, vec3(0,1,0)
		)
	*/

	leftMotor.Render();
	rightMotor.Render();

	leftConnector.Render();
	rightConnector.Render();

	mainBody.Render();

	leftFin.Render();
	rightFin.Render();

	trunk.Render();

	leftMotorOuterFlame.Render();
	rightMotorOuterFlame.Render();

	leftMotorInnerFlame.Render();
	rightMotorInnerFlame.Render();

	angle += (float)dt * 2 * glm::pi<float>() * 0.1f;
}

void Spaceship::animateMotors()
{
	_motorAngle = 0;// glm::pi<float>() / 2;

	// TODO move to global variables
	float xmotorTranslationX = connectorTranslationX + connectorWidthAfterShear / 2 - connectorWidth / 2
		- connectorSpaceVisibleUnderMotor / 2;
	float xmotorTranslationZ = connectorTranslationZ - connectorDepthAfterShear / 2 + connectorDepth / 2;

	_leftMotorTransformationMatrix = glm::translate(glm::mat4(),
		vec3(xmotorTranslationX, motorTranslationY, xmotorTranslationZ))
		*
		glm::rotate(glm::mat4(), _motorAngle, vec3(0, 1, 0));

	_rightMotorTransformationMatrix = glm::translate(glm::mat4(),
		vec3(-xmotorTranslationX, motorTranslationY, xmotorTranslationZ))
		*
		glm::rotate(glm::mat4(), _motorAngle, vec3(0, 1, 0));
}

/* Animates flames by constantly modifying their size, also makes them bigger when going in specific directions. */
void Spaceship::animateFlames()
{
	/* Flame size always varies between 1x and 2x their original size. Left flames are bigger when going forward,
	backward or right, right flames are bigger when going forward, backward or left. When going backward, we flip the
	'Z' coordinate so the flame are pushing the spaceship towards the origin (Z=0). */
	float leftOuterFlameDepthRatio = (((_direction & DIRECTION_RIGHT) != 0 || (_direction & DIRECTION_FORWARD) != 0
		|| (_direction & DIRECTION_BACKWARD) != 0) ? 2.5f : 0) + randomFloat(1.0f, 2.0f);
	
	float rightOuterFlameDepthRatio = (((_direction & DIRECTION_LEFT) != 0 || (_direction & DIRECTION_FORWARD) != 0
		|| (_direction & DIRECTION_BACKWARD) != 0) ? 2.5f : 0) + randomFloat(1.0f, 2.0f);
	
	float leftInnerFlameDepthRatio = leftOuterFlameDepthRatio + randomFloat(0, 0.5f);
	float rightInnerFlameDepthRatio = rightOuterFlameDepthRatio + randomFloat(0, 0.5f);

	/* Height after 90 rotation becomes depth... */
	float currentLeftOuterMotorFlameHeight = outerMotorFlameHeight * leftOuterFlameDepthRatio;
	float currentRightOuterMotorFlameHeight = outerMotorFlameHeight * rightOuterFlameDepthRatio;

	float currentLeftInnerMotorFlameHeight = innerMotorFlameHeight * leftInnerFlameDepthRatio;
	float currentRightInnerMotorFlameHeight = innerMotorFlameHeight * rightInnerFlameDepthRatio;

	float outerLeftMotorFlameTranslationZ = -((motorHeight + currentLeftOuterMotorFlameHeight) / 2) + 0.01f;
	float outerRightMotorFlameTranslationZ = -((motorHeight + currentRightOuterMotorFlameHeight) / 2) + 0.01f;

	float innerLeftMotorFlameTranslationZ = -(motorHeight / 2 + (currentLeftInnerMotorFlameHeight / 2)) + 0.01f;
	float innerRightMotorFlameTranslationZ = -(motorHeight / 2 + (currentRightInnerMotorFlameHeight / 2)) + 0.01f;

	/* Translations are applied to motors whose centers are at (0, 0, 0) before their transformation matrix is applied.
	Since the flame transformation matrices are applied first, we only translate the 'Z' coordinate. Then, when the
	motors will have their transformation matrices applied, the motors and the flames will move to the final place. */
	_leftMotorOuterFlameTransformationMatrix = glm::translate(vec3(0, 0, outerLeftMotorFlameTranslationZ))
		*
		glm::scale(vec3(1.0f, 1.0f, leftOuterFlameDepthRatio));

	_rightMotorOuterFlameTransformationMatrix = glm::translate(glm::mat4(), vec3(0, 0, outerRightMotorFlameTranslationZ))
		*
		glm::scale(glm::mat4(), vec3(1.0f, 1.0f, rightOuterFlameDepthRatio));

	_leftMotorInnerFlameTransformationMatrix = glm::translate(glm::mat4(), vec3(0, 0, innerLeftMotorFlameTranslationZ))
		*
		glm::scale(glm::mat4(), vec3(1.0f, 1.0f, leftInnerFlameDepthRatio));

	_rightMotorInnerFlameTransformationMatrix = glm::translate(glm::mat4(), vec3(0, 0, innerRightMotorFlameTranslationZ))
		*
		glm::scale(glm::mat4(), vec3(1.0f, 1.0f, rightInnerFlameDepthRatio));

	/* If spaceship's going backward, flames are reversed (in front of motors), which is more logical than keeping them
	behind them. */
	if ((_direction & DIRECTION_BACKWARD) != 0)
	{
		_leftMotorOuterFlameTransformationMatrix = flipZ * _leftMotorOuterFlameTransformationMatrix;
		_rightMotorOuterFlameTransformationMatrix = flipZ * _rightMotorOuterFlameTransformationMatrix;

		_leftMotorInnerFlameTransformationMatrix = flipZ * _leftMotorInnerFlameTransformationMatrix;
		_rightMotorInnerFlameTransformationMatrix = flipZ * _rightMotorInnerFlameTransformationMatrix;
	}
}

/* Calculates the Z and Z positions of the spaceship. The direction is represented by different constants which all
have a '1' at a different position (bit shift), and we can combine those constants combine directions, for example
going FORWARD and going LEFT at the same time. We prevent being able to go FORWARD and BACKWARD at the same time.

Known bug:
    - Hold 'S' to go backward, spaceship goes backward
	- Hold 'W' to go forward (but don't release 'S'), spaceship stops going backward and goes forward
	- Release 'W' (but don't release 'S'), spaceship stops but does not go backward as expected.

	The same thing holds if you first hold 'W', and then hold 'S' and release 'S' but keep holding 'W', same thing
	also for left and right.
*/
void Spaceship::calculatePosition(double dt)
{
	if (DIRECTION_NO_CHANGE == _direction)
	{
		/* Going nowhere */

		return;
	}

	if ((_direction & DIRECTION_FORWARD) != 0)
	{
		/* Going forward */
		_positionZ += _deltaZperSecond * dt;
	}
	else if ((_direction & DIRECTION_BACKWARD) != 0)
	{
		/* Going backward */
		_positionZ -= _deltaZperSecond * dt;
	}

	if ((_direction & DIRECTION_LEFT) != 0)
	{
		/* Going left */
		_positionX += _deltaXperSecond * dt;
	}
	else if ((_direction & DIRECTION_RIGHT) != 0)
	{
		/* Going right */
		_positionX -= _deltaXperSecond * dt;
	}

	/* Below, bound checking */
	if (_positionZ < 0)
	{
		/* Reached bottom limit */

		_positionZ = 0;
		
		stopGoingBackward();
	}
	else if (_positionZ > 75)
	{
		/* Reached top limit */

		_positionZ = 75;
		
		stopGoingForward();
	}

	if (_positionX < -15)
	{
		/* Reached right limit */

		_positionX = -15;
		
		stopGoingRight();
	}
	else if(_positionX > 15)
	{
		/* Reached left limit */

		_positionX = 15;

		stopGoingLeft();
	}
}

/* Below are methods which are called with certain keys (for example 'W' for 'FORWARD') to controle the spaceship
direction. */

void Spaceship::goForward()
{
	if (_positionX >= 75)
	{
		return;
	}

	/* If was going backward, stop that, let's go forward. */
	if ((_direction & DIRECTION_BACKWARD) != 0)
	{
		stopGoingBackward();
	}

	_direction |= DIRECTION_FORWARD;
}

void Spaceship::stopGoingForward()
{
	/* Setting the '1' in the constant equal to zero in '_direction' */
	_direction = _direction & ~DIRECTION_FORWARD;
}

void Spaceship::goLeft()
{
	/* If going right, stop going right, now going left. */
	if ((_direction & DIRECTION_RIGHT) != 0)
	{
		stopGoingRight();
	}

	_direction |= DIRECTION_LEFT;
}

void Spaceship::stopGoingLeft()
{
	/* Setting the '1' in the constant equal to zero in '_direction' */
	_direction = _direction & ~DIRECTION_LEFT;
}

void Spaceship::goRight()
{
	/* If was going left, stop that, now going right. */
	if ((_direction & DIRECTION_LEFT) != 0)
	{
		stopGoingLeft();
	}

	_direction |= DIRECTION_RIGHT;
}

void Spaceship::stopGoingRight()
{
	/* Setting the '1' in the constant equal to zero in '_direction' */
	_direction = _direction & ~DIRECTION_RIGHT;
}

void Spaceship::goBackward()
{
	// TODO simplify, constants ...
	if (_positionX <= 0)
	{
		_LOG_INFO() << "= 0";
		//return;
	}

	/* If was going forward, stop that, now going backward. */
	if ((_direction & DIRECTION_FORWARD) != 0)
	{
		stopGoingForward();
	}

	_direction |= DIRECTION_BACKWARD;
}

void Spaceship::stopGoingBackward()
{
	/* Setting the '1' in the constant equal to zero in '_direction' */
	_direction = _direction & ~DIRECTION_BACKWARD;
}

