#include "spaceship.h"

#include "glm/gtx/transform2.hpp"

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

glm::vec4 motorColor = vec4(0, 0, 1, 1);

float motorHeight = 3.5f;
float motorRadius = 0.3f;

float connectorSpaceVisibleUnderMotor = 0.2f;

float motorTranslationX = connectorTranslationX + connectorWidthAfterShear / 2 - motorRadius / 2
	- connectorSpaceVisibleUnderMotor;
float motorTranslationY = connectorTranslationY - connectorHeightAfterShear / 2 + motorRadius / 2
	+ connectorSpaceVisibleUnderMotor;
float motorTranslationZ = -1.0f;

glm::vec4 outerMotorFlameColor = vec4(1, 0, 0, 0.5f);

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

glm::mat4 leftMotorTransformationMatrix = glm::translate(glm::mat4(), 
	vec3(motorTranslationX, motorTranslationY, motorTranslationZ))
	* rotation90degAroundX;

glm::mat4 leftMotorOuterFlameTransformationMatrix = glm::translate(glm::mat4(),
	vec3(outerMotorFlameTranslationX, outerMotorFlameTranslationY, outerMotorFlameTranslationZ))
	* leftMotorTransformationMatrix;

glm::mat4 leftMotorInnerFlameTransformationMatrix = leftMotorOuterFlameTransformationMatrix;

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

	mainBody(mainBodyColor, mainBodyTransformationMatrix),

	leftConnector(connectorColor, leftConnectorTransformationMatrix),
	rightConnector(connectorColor, flipX * leftConnectorTransformationMatrix),

	leftMotor(motorColor, 100, motorHeight, motorRadius, leftMotorTransformationMatrix),
	rightMotor(motorColor, 100, motorHeight, motorRadius, flipX * leftMotorTransformationMatrix),

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
	animateFlames();

	leftMotorOuterFlame.SetTransform(_leftMotorOuterFlameTransformationMatrix);
	rightMotorOuterFlame.SetTransform(_rightMotorOuterFlameTransformationMatrix);
	leftMotorInnerFlame.SetTransform(_leftMotorInnerFlameTransformationMatrix);
	rightMotorInnerFlame.SetTransform(_rightMotorInnerFlameTransformationMatrix);

	mainBody.SetTransform(glm::scale(glm::mat4(), vec3(0.3f, 0.3f, 0.3f)));
	//mainBody.SetTransform(glm::scale(glm::rotate(glm::mat4(), angle, vec3(0,1,0)), vec3(0.5f, 0.5f, 0.5f)));	 // -glm::pi<float>()/7
	//mainBody.SetTransform(glm::rotate(glm::mat4(), angle, vec3(0,1,0)));
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

void Spaceship::animateFlames()
{
	_direction = FORWARD;

	float leftOuterFlameDepthRatio = (RIGHT == _direction || FORWARD == _direction ? 2.5f : 0) + randomFloat(1.0f, 2.0f);
	float rightOuterFlameDepthRatio = (LEFT == _direction || FORWARD == _direction ? 2.5f : 0) + randomFloat(1.0f, 2.0f);
	
	float leftInnerFlameDepthRatio = leftOuterFlameDepthRatio + randomFloat(0, 0.5f);
	float rightInnerFlameDepthRatio = rightOuterFlameDepthRatio + randomFloat(0, 0.5f);

	//-((motorHeight + outerMotorFlameHeight) / 2) + 0.01f;
	
	// 1.0f => 0
	// 1.5f => = 1.37500
	// 2.0f => 2.75f

	_leftMotorOuterFlameTransformationMatrix = glm::translate(glm::mat4(), vec3(0, 0, ((leftOuterFlameDepthRatio - 1) * 2.75f))) * glm::scale(glm::mat4(), vec3(1, 1, leftOuterFlameDepthRatio));
	_rightMotorOuterFlameTransformationMatrix = glm::translate(glm::mat4(), vec3(0, 0, ((rightOuterFlameDepthRatio - 1) * 2.75f))) * glm::scale(glm::mat4(), vec3(1, 1, rightOuterFlameDepthRatio));
	
	_leftMotorInnerFlameTransformationMatrix = glm::translate(glm::mat4(), vec3(0, 0, ((leftInnerFlameDepthRatio - 1) * 2.75f))) * glm::scale(glm::mat4(), vec3(1, 1, leftInnerFlameDepthRatio));
	_rightMotorInnerFlameTransformationMatrix = glm::translate(glm::mat4(), vec3(0, 0, ((rightInnerFlameDepthRatio - 1) * 2.75f))) * glm::scale(glm::mat4(), vec3(1, 1, rightInnerFlameDepthRatio));
}

