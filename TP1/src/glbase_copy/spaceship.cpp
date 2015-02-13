#include "spaceship.h"

#include "glm/gtx/transform2.hpp"

float connectorShearXfractionOfY = -0.5f;
float connectorShearZfractionOfY = 0.5f;
float finShearZFractionOfX       = -0.5f;

glm::mat4 rotation90degAroundX(glm::rotate(glm::pi<float>() / 2, vec3(1, 0, 0)));

glm::mat4 rotation90degAroundY(glm::rotate(glm::pi<float>(), vec3(0, 1, 0)));

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

float motorTranslationX = 0;
float motorTranslationY = connectorTranslationY - connectorHeightAfterShear / 2 + motorRadius / 2
	+ connectorSpaceVisibleUnderMotor;
float motorTranslationZ = -1.0f;

glm::vec4 outerMotorFlameColor = vec4(1, 0, 1, 0.7f);

float outerMotorFlameHeight = 0.4f;
float outerMotorFlameRadius = motorRadius * 0.7f;

float outerMotorFlameTranslationX = 0;
float outerMotorFlameTranslationY = 0;
float outerMotorFlameTranslationZ = -((motorHeight + outerMotorFlameHeight) / 2) + 0.01f;

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

glm::mat4 mainBodyTransformationMatrix = glm::scale(vec3(mainBodyWidth, mainBodyHeight, mainBodyDepth));

glm::mat4 leftConnectorTransformationMatrix =
	  glm::translate(vec3(connectorTranslationX, connectorTranslationY, connectorTranslationZ))
	* connectorShear 
	* glm::scale(vec3(connectorWidth, connectorHeight, connectorDepth));

glm::mat4 leftMotorTransformationMatrix_part1 = rotation90degAroundX;

glm::mat4 leftMotorTransformationMatrix = rotation90degAroundX;

glm::mat4 leftMotorOuterFlameTransformationMatrix = rotation90degAroundX;

glm::mat4 leftMotorInnerFlameTransformationMatrix = rotation90degAroundX;// leftMotorOuterFlameTransformationMatrix;

glm::mat4 trunkTransformationMatrix =
	  glm::translate(vec3(trunkTranslationX, trunkTranslationY, trunkTranslationZ))
	* glm::scale(vec3(trunkScaleX, trunkScaleY, trunkScaleZ))
	* rotation90degAroundX;

glm::mat4 leftFinTransformationMatrix =
	  glm::translate(vec3(finTranslationX, finTranslationY, finTranslationZ))
	* finShear
	* glm::scale(vec3(finWidth, finHeight, finDepth));

/* Constructor. Builds all shapes. Some shapes like fins (ailerons en français) will never change, except when the
   mainBody shape (a Box) is translated. We can then avoid applying a transformation matrix to them at every frame
   rendering, so we apply initial transformation matrices (shear transformation and translation) to the right here. */
Spaceship::Spaceship() :
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
	/* Building shape hierarchy. */

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

	_addShapeToList(&mainBody);
	_addShapeToList(&trunk);
	_addShapeToList(&leftFin);
	_addShapeToList(&rightFin);
	_addShapeToList(&leftConnector);
	_addShapeToList(&rightConnector);
	_addShapeToList(&leftMotor);
	_addShapeToList(&rightMotor);
	_addShapeToList(&leftMotorOuterFlame);
	_addShapeToList(&leftMotorInnerFlame);
	_addShapeToList(&rightMotorOuterFlame);
	_addShapeToList(&rightMotorInnerFlame);

	_defineBoundingBox();
}

/* Called every time a frame is rendered. */
void Spaceship::render(double dt)
{
	double positionXCopy = _positionX;
	double positionZCopy = _positionZ;

	calculatePosition(dt);

	animateMotors(dt);

	animateFlames();

	/* First applying transformation matrices to flames (which are children of motors). */
	leftMotorOuterFlame.SetTransform(_leftMotorOuterFlameTransformationMatrix);
	rightMotorOuterFlame.SetTransform(_rightMotorOuterFlameTransformationMatrix);
	leftMotorInnerFlame.SetTransform(_leftMotorInnerFlameTransformationMatrix);
	rightMotorInnerFlame.SetTransform(_rightMotorInnerFlameTransformationMatrix);

	/* Then, applying transformation matrices to motors (parents of flames). */
	leftMotor.SetTransform(_leftMotorTransformationMatrix);
	rightMotor.SetTransform(_rightMotorTransformationMatrix);

	/* Finally, applying transformation matrix to mainBody (the main parent) to move the spaceship to calculated
	   X and Z positions. */
	mainBody.SetTransform(glm::translate(vec3(_positionX, 0, _positionZ)));

	_translateBoundingBox(_positionX - positionXCopy, 0, _positionZ - positionZCopy);

	/*Rendering shapes. */

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
}

Spaceship::~Spaceship()
{

}

/* Adapts the motor angles according to X speed and reverses that angle if spaceship is accelerating/moving backward.*/
void Spaceship::animateMotors(double dt)
{
	/* We simply define the angle using the fraction of X speed over the maximum X speed. */
	double currentMotorAngle = sign(_speedX) * _maxMotorAngle * (abs(_speedX) / _maxSpeedX);

	/* If going/accelerating backward, flip the angle because flame will appear in front of the motors. */
	if (_forceBackwardMotors && (isGoingBackward() || isAcceleratingBackward()))
	{
		currentMotorAngle *= -1;
	}

	double deltaAngle = currentMotorAngle - _motorAngle;

	/* We want to prevent sudden "big" rotations, for example when suddenly going from forward to backward (which flips
	   the angle). */
	if ((abs(deltaAngle) / dt) > _maxMotorAngleDeltaPerSecond)
	{
		_motorAngle += sign(deltaAngle) * _maxMotorAngleDeltaPerSecond * dt;
	}
	else
	{
		_motorAngle = currentMotorAngle;
	}

	/* Check against angle limit. */
	if (abs(_motorAngle) > _maxMotorAngle)
	{
		_motorAngle = _maxMotorAngle * sign(_motorAngle);
	}

	// TODO should be global variables since don't change
	/* Calculate X and Z translation to keep center aligned at the right spot. */
	motorTranslationX = connectorTranslationX + connectorWidthAfterShear / 2 - connectorWidth / 2
		- connectorSpaceVisibleUnderMotor / 2;

	motorTranslationZ = connectorTranslationZ - connectorDepthAfterShear / 2 + connectorDepth / 2;

	/* Creating transformation matrices. */
	_leftMotorTransformationMatrix =
		glm::translate(vec3(motorTranslationX, motorTranslationY, motorTranslationZ))
		*
		glm::rotate((float) _motorAngle, vec3(0, 1, 0));

	_rightMotorTransformationMatrix =
		glm::translate(vec3(-motorTranslationX, motorTranslationY, motorTranslationZ))
		*
		glm::rotate((float) _motorAngle, vec3(0, 1, 0));
}

/* Animates flames by constantly modifying their size, also makes them bigger when going in specific directions. */
void Spaceship::animateFlames()
{
	bool goingForward = _forceForwardMotors && (isGoingForward() || isAcceleratingForward());
	bool goingBackward = _forceBackwardMotors && (isGoingBackward() || isAcceleratingBackward());

	/* Ratios for left and right outer flames:
	       - When going forward/backward (key down AND moving), both flames get '+ 2.5x' their original size;
		   - When going right (key down AND moving), no matter if going forward/backward, left flame gets '+ 2.5x' its
		     original size (combines with forward/backward movement, meaning that forward/backward AND right = 5.0x);
		   - When going left (key down AND moving), no matter if going forward/backward, right flames '+ 2.5x' its
		     original size (combines ... just like above);
			- Finally, a random number between 1.0f and 2.0f is added to create the flame movement. */
	float leftOuterFlameDepthRatio =
		  ((goingForward|| goingBackward) ? 2.5f : 0)
		+ ((_forceRightMotor && (isGoingRight() || isAcceleratingRight())) ? 2.5f : 0)
		+ randomFloat(1.0f, 2.0f);
	
	float rightOuterFlameDepthRatio = 
		  ((goingForward || goingBackward) ? 2.5f : 0)
		+ ((_forceLeftMotor && (isGoingLeft() || isAcceleratingLeft())) ? 2.5f : 0)
		+ randomFloat(1.0f, 2.0f);
	
	/* Inner flames are a bit bigger than outer flames (but the random number can be 0, so they might be as big as
	   outer flames). */
	float leftInnerFlameDepthRatio  = leftOuterFlameDepthRatio + randomFloat(0, 0.5f);
	float rightInnerFlameDepthRatio = rightOuterFlameDepthRatio + randomFloat(0, 0.5f);

	/* Calculating new heights. */
	float currentLeftOuterMotorFlameDepth  = outerMotorFlameHeight * leftOuterFlameDepthRatio;
	float currentRightOuterMotorFlameDepth = outerMotorFlameHeight * rightOuterFlameDepthRatio;
	float currentLeftInnerMotorFlameDepth  = innerMotorFlameHeight * leftInnerFlameDepthRatio;
	float currentRightInnerMotorFlameDepth = innerMotorFlameHeight * rightInnerFlameDepthRatio;

	/* Calculating Z translations to put flames at the end of motor. We add '0.01f' to avoid a flickering effect 
	   which is sometimes visibles when zooming in (happened during tests when building spaceship). */
	float outerLeftMotorFlameTranslationZ  = -((motorHeight + currentLeftOuterMotorFlameDepth) / 2) + 0.01f;
	float outerRightMotorFlameTranslationZ = -((motorHeight + currentRightOuterMotorFlameDepth) / 2) + 0.01f;
	float innerLeftMotorFlameTranslationZ  = -(motorHeight / 2 + (currentLeftInnerMotorFlameDepth / 2)) + 0.01f;
	float innerRightMotorFlameTranslationZ = -(motorHeight / 2 + (currentRightInnerMotorFlameDepth / 2)) + 0.01f;

	/* Translations are applied to motors whose centers are at (0, 0, 0) before their transformation matrix is applied.
	Since the flame transformation matrices are applied first, we only translate the 'Z' coordinate. Then, when the
	motors will have their transformation matrices applied, the motors and the flames will move to the final place. */
	_leftMotorOuterFlameTransformationMatrix =
		glm::translate(vec3(0, 0, outerLeftMotorFlameTranslationZ))
		*
		glm::scale(vec3(1.0f, 1.0f, leftOuterFlameDepthRatio));

	_rightMotorOuterFlameTransformationMatrix =
		glm::translate(vec3(0, 0, outerRightMotorFlameTranslationZ))
		*
		glm::scale(vec3(1.0f, 1.0f, rightOuterFlameDepthRatio));

	_leftMotorInnerFlameTransformationMatrix = 
		glm::translate(vec3(0, 0, innerLeftMotorFlameTranslationZ))
		*
		glm::scale(vec3(1.0f, 1.0f, leftInnerFlameDepthRatio));

	_rightMotorInnerFlameTransformationMatrix =
		glm::translate(vec3(0, 0, innerRightMotorFlameTranslationZ))
		*
		glm::scale(vec3(1.0f, 1.0f, rightInnerFlameDepthRatio));

	/* If spaceship's going backward, flames are reversed (in front of motors), which is more logical than keeping them
	   behind them. If going backward and right OR left, this simple inversion will also work. For example, if going
	   backward and right, the left flame will be bigger than the right one. */
	if (goingBackward)
	{
		_leftMotorOuterFlameTransformationMatrix = flipZ * _leftMotorOuterFlameTransformationMatrix;
		_rightMotorOuterFlameTransformationMatrix = flipZ * _rightMotorOuterFlameTransformationMatrix;

		_leftMotorInnerFlameTransformationMatrix = flipZ * _leftMotorInnerFlameTransformationMatrix;
		_rightMotorInnerFlameTransformationMatrix = flipZ * _rightMotorInnerFlameTransformationMatrix;
	}
}

/* Calculates the Z and X positions of the spaceship. Prevents spaceship from leaving screen. */
void Spaceship::calculatePosition(double dt)
{
	/* Calculating current Z speed with current Z acceleration.*/
	_speedZ = _speedZ + (_currentAccelerationZ * dt);

	/* The drag effects diminishes the acceleration or slows down the spaceship when there is no acceleration. */
	double dragEffectZ = _dragZ * dt;

	/* Applying drag effect to speed. No drag if speed is to change sign (speed becomes 0). */
	if (dragEffectZ > abs(_speedZ))
	{
		_speedZ = 0;
	}
	else
	{
		_speedZ -= sign(_speedZ) * dragEffectZ;
	}

	/* Checks speed against maximum speed. */
	if (abs(_speedZ) > _maxSpeedZ)
	{
		_speedZ = sign(_speedZ) * _maxSpeedZ;
	}

	/* Calculates new Z position. */
	_positionZ += _speedZ * dt;

	/* Prevents the position from being outside the screen. */
	if (_positionZ >= _maxPositionZ)
	{
		_positionZ = _maxPositionZ;

		/* Only set speed to 0 if going forward or still (not moving). We do not want to set the speed to 0 if going
		   backward. This can happen if we go all the way to _maxPositionZ, then stop, then press 'S' to go backward.
		   Since we are at Z=_maxPositionZ, we must no set the speed to 0, otherwise the spaceship would never leave
		   Z=_maxPositionZ. */
		if (isGoingForward() || isStillZ())
		{
			_speedZ = 0;
		}
	}
	else if (_positionZ < _minPositionZ)
	{
		_positionZ = _minPositionZ;

		/* Same logic as above but for minimum Z... */
		if (isGoingBackward() || isStillZ())
		{
			_speedZ = 0;
		}
	}

	/* Same stuff for X speed and X position. */
	_speedX = _speedX + (_currentAccelerationX * dt);

	double dragEffectX = _dragX * dt;

	if (dragEffectX > abs(_speedX))
	{
		_speedX = 0;
	}
	else
	{
		_speedX -= sign(_speedX) * dragEffectX;
	}

	if (abs(_speedX) > _maxSpeedX)
	{
		_speedX = sign(_speedX) * _maxSpeedX;
	}

	_positionX += _speedX * dt;

	if (_positionX >= _maxPositionX)
	{
		_positionX = _maxPositionX;

		if (isGoingLeft() || isStillX())
		{
			_speedX = 0;
		}
	}
	else if (_positionX < _minPositionX)
	{
		_positionX = _minPositionX;

		if (isGoingRight() || isStillX())
		{
			_speedX = 0;
		}
	}

	/* Checks if at the current speed the spaceship is going to hit screen limits (+Z, -Z, +X, -X). */
	if (isAcceleratingForward() && _speedZ > 0)
	{
		/* Distance between spaceship and _maxPositionZ. */
		double distanceAhead = _maxPositionZ - _positionZ;

		/* Time required to get to maxPositionZ starting with current speed, but ending with speed = 0 (explaining the
		'/ 2' since d = [(v1 + v2) * t] / 2). */
		double timeUntilCollision = (double) distanceAhead / (_speedZ / 2);

		/* Drag effect for the time calculated above. */
		double dragEffect = (double)_dragZ * timeUntilCollision;

		/* Stop accelerating if the drag effect applied to current speed would result in a speed above 0. This way,
		   the spaceship will slow down and stop at Z = _maxPositionZ. */
		if (_speedZ - dragEffect > 0)
		{
			_currentAccelerationZ = 0;
		}
	}
	else if (isAcceleratingBackward() && _speedZ < 0)
	{
		/* Same logic as above but for _minPositionZ. */
		double distanceToBack     = _positionZ - _minPositionZ;
		double timeUntilCollision = (double) distanceToBack / (abs(_speedZ) / 2);
		double dragEffect         = (double) _dragZ * timeUntilCollision;

		if (_speedZ + dragEffect < 0)
		{
			_currentAccelerationZ = 0;
		}
	}
	
	if (isAcceleratingLeft() && _speedX > 0)
	{
		/* Same logic as above but for _maxPositionX. */
		double distanceToLeft     = _maxPositionX - _positionX;
		double timeUntilCollision = (double) distanceToLeft / (_speedX / 2);
		double dragEffect         = (double) _dragX * timeUntilCollision;

		if (_speedX - dragEffect > 0)
		{
			_currentAccelerationX = 0;
		}
	}
	else if (isAcceleratingRight() && _speedX < 0)
	{
		/* Same logic as above but for _minPositionX. */
		double distanceToRight    = _positionX - _minPositionX;
		double timeUntilCollision = (double) distanceToRight / (abs(_speedX) / 2);
		double dragEffect         = (double) _dragX * timeUntilCollision;

		if (_speedX + dragEffect < 0)
		{
			_currentAccelerationX = 0;
		}
	}
}

/* Below are methods which are called with certain keys (for example 'W' for 'FORWARD') to control the spaceship
direction. */

void Spaceship::goForward()
{
	_currentAccelerationZ = _accelerationZ;
	_goingForwardKeyDown  = true;
	_forceForwardMotors   = true;
	_forceBackwardMotors  = false;
}

void Spaceship::stopGoingForward()
{
	if (isAcceleratingForward())
	{
		_currentAccelerationZ = 0;
	}

	_goingForwardKeyDown = false;
	_forceForwardMotors  = false;

	if (_goingBackwardKeyDown)
	{
		goBackward();
	}
}

void Spaceship::goLeft()
{
	_currentAccelerationX = _accelerationX;
	_goingLeftKeyDown     = true;
	_forceLeftMotor       = true;
	_forceRightMotor      = false;
}

void Spaceship::stopGoingLeft()
{
	if (isAcceleratingLeft())
	{
		_currentAccelerationX = 0;
	}

	_goingLeftKeyDown   = false;
	_forceLeftMotor     = false;

	if (_goingRightKeyDown)
	{
		goRight();
	}
}

void Spaceship::goRight()
{
	_currentAccelerationX = -_accelerationX;
	_goingRightKeyDown    = true;
	_forceRightMotor      = true;
	_forceLeftMotor       = false;
}

void Spaceship::stopGoingRight()
{
	if (isAcceleratingRight())
	{
		_currentAccelerationX = 0;
	}

	_goingRightKeyDown = false;
	_forceRightMotor   = false;

	if (_goingLeftKeyDown)
	{
		goLeft();
	}
}

void Spaceship::goBackward()
{
	_currentAccelerationZ     = -_accelerationZ;
	_goingBackwardKeyDown     = true;
	_forceBackwardMotors      = true;
	_forceForwardMotors       = false;
}

void Spaceship::stopGoingBackward()
{
	if (isAcceleratingBackward())
	{
		_currentAccelerationZ = 0;
	}

	_goingBackwardKeyDown     = false;
	_forceBackwardMotors      = false;

	if (_goingForwardKeyDown)
	{
		goForward();
	}
}

void Spaceship::resetPosition()
{
	double positionXCopy = _positionX;
	double positionZCopy = _positionZ;
	
	_positionX = 0;
	_positionZ = 0;

	_translateBoundingBox(_positionX - positionXCopy, 0, _positionZ - positionZCopy);

	_speedX = 0;
	_speedZ = 0;
}

bool Spaceship::isGoingForward()
{
	return (sign(_speedZ) > 0);
}

bool Spaceship::isGoingLeft()
{
	return (sign(_speedX) > 0);
}

bool Spaceship::isGoingRight()
{
	return (sign(_speedX) < 0);
}

bool Spaceship::isGoingBackward()
{
	return (sign(_speedZ) < 0);
}

bool Spaceship::isStillZ()
{
	return (sign(_speedZ) == 0);
}

bool Spaceship::isStillX()
{
	return (sign(_speedX) == 0);
}

bool Spaceship::isAcceleratingForward()
{
	return ((sign(_currentAccelerationZ) > 0) && (_positionZ < _maxPositionZ));
}

bool Spaceship::isAcceleratingLeft()
{
	return ((sign(_currentAccelerationX) > 0) && (_positionX < _maxPositionX));
}

bool Spaceship::isAcceleratingRight()
{
	return ((sign(_currentAccelerationX) < 0) && (_positionX > _minPositionX));
}

bool Spaceship::isAcceleratingBackward()
{
	return ((sign(_currentAccelerationZ) < 0) && (_positionZ > _minPositionZ));
}

bool Spaceship::isNotAcceleratingZ()
{
	return (sign(_currentAccelerationZ) == 0);
}

bool Spaceship::isNotAcceleratingX()
{
	return (sign(_currentAccelerationX) == 0);
}

std::vector<glm::vec3> Spaceship::getPosition()
{
	std::vector<glm::vec3> theVector;

	theVector.push_back(vec3(0, 0, 0));
	theVector.push_back(vec3(1, 1, 1));
	theVector.push_back(vec3(2, 2, 2));
	theVector.push_back(vec3(3, 3, 3));

	return theVector;
}


