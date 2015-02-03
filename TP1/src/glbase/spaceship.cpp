#include "spaceship.h"

#include "glm/gtx/transform2.hpp"

glm::mat4 rotation90degAroundX(glm::rotate(glm::mat4(), glm::pi<float>() / 2, vec3(1, 0, 0)));

glm::mat4 rotation90degAroundY(glm::rotate(glm::mat4(), glm::pi<float>(), vec3(0, 1, 0)));

glm::mat4 connectorShear
{
	1, 0, 0, 0,
	-0.5f, 1, -0.5f, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

glm::mat4 finShear
{
	1, 0, 0.5f, 0,
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

// before modification

glm::mat4 leftConnectorTransformationMatrix = connectorShear * glm::translate(glm::scale(glm::mat4(), vec3(0.3f, 2, 1)), vec3(0.75f, -0.60f, -0.5f));//glm::translate(glm::scale(glm::rotate(glm::mat4(), glm::pi<float>() / 2, vec3(1, 0, 0)), vec3(0.3f, 1, 2)), vec3(0, 0, 1));

glm::mat4 leftMotorTransformationMatrix = glm::translate(glm::mat4(), vec3(0.25f + 0.9f, -1.8f, 1.0f)) * rotation90degAroundX;

glm::mat4 leftMotorOuterFlameTransformationMatrix = glm::translate(glm::mat4(), vec3(0, 0, 1.9f)) * leftMotorTransformationMatrix * glm::scale(glm::mat4(), vec3(0.7f, 0.7f, 0.7f));
//glm::translate(glm::mat4(), vec3(0.9f, -1.8f, 2.9f)) * rotation90degAroundX * glm::scale(glm::mat4(), vec3(0.7f, 0.7f, 0.7f));

glm::mat4 leftMotorInnerFlameTransformationMatrix = glm::translate(glm::mat4(), vec3(0, 0, 1.9f)) * leftMotorTransformationMatrix * glm::scale(glm::mat4(), vec3(0.3f, 0.7f, 0.3f)); //leftMotorOuterFlameTransformationMatrix * glm::scale(glm::mat4(), vec3(0.5f, 0.5f, 0.5f)); // glm::translate(glm::mat4(), vec3(0.9f, -1.8f, 2.9f)) * rotation90degAroundX * glm::scale(glm::mat4(), vec3(0.3f, 0.7f, 0.3f));

glm::mat4 leftFinTransformationMatrix = finShear * glm::translate(glm::mat4(), vec3(0.75f, 0, -2.4f)) * glm::scale(glm::mat4(), vec3(1.25f, 0.5f, 1));
//glm::translate(glm::scale(glm::mat4(), vec3(0.3f, 2, 1)), vec3(0.75f, -0.60f, -0.5f));

Spaceship::Spaceship() :
angle(0),

mainBody(vec4(1.0f, 0, 0, 1.0f), glm::scale(glm::mat4(), vec3(1, 0.5f, 3))),

leftConnector(vec4(0, 1, 0, 1.0f), leftConnectorTransformationMatrix),
rightConnector(vec4(0, 1, 0, 1.0f), flipX * leftConnectorTransformationMatrix),

leftMotor(vec4(0, 0, 1, 1), 100, 3.5f, 0.3f, leftMotorTransformationMatrix),

leftMotorOuterFlame(vec4(1, 0, 0, 0.5f), 100, 0.5f, 0.3f, leftMotorOuterFlameTransformationMatrix),
rightMotorOuterFlame(vec4(1, 0, 0, 0.5f), 100, 0.5f, 0.3f, flipX * leftMotorOuterFlameTransformationMatrix),

leftMotorInnerFlame(vec4(1, 0, 0, 1.0f), 100, 0.5f, 0.3f, leftMotorInnerFlameTransformationMatrix),
rightMotorInnerFlame(vec4(1, 0, 0, 1.0f), 100, 0.5f, 0.3f, flipX * leftMotorInnerFlameTransformationMatrix),

rightMotor(vec4(0, 0, 1, 1), 100, 3.5f, 0.3f, flipX * leftMotorTransformationMatrix),

trunk(vec4(0, 1, 1, 1), 100, 3, 0.5f, glm::translate(glm::mat4(), vec3(0, 0, -1.35f)) * rotation90degAroundX * glm::scale(glm::mat4(), vec3(0.3f, 1, 1))),

leftFin(vec4(1, 1, 0, 1), leftFinTransformationMatrix),
rightFin(vec4(1, 1, 0, 1), flipX * leftFinTransformationMatrix)
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

	_LOG_INFO() << "Spaceship1 constructor";
}

void Spaceship::render(double dt)
{
	//_LOG_INFO() << "Spaceship render";

	//leftConnector.SetTransform(glm::rotate(glm::mat4(), angle, vec3(0, 0, 1)));
	mainBody.SetTransform(glm::rotate(glm::scale(glm::mat4(), vec3(0.5f, 0.5f, 0.5f)), angle, vec3(0, 1, 0)));
	//mainBody.SetTransform(glm::scale(glm::mat4(), vec3(0.5f, 0.5f, 0.5f)));

	

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

