#include "tp1.h"

#include "glm/gtx/transform2.hpp"

#include <sstream>
#include <string>

std::string printVec3(glm::vec3 vec)
{
	std::stringstream ss;
	ss << "(" << vec[0] << ", " << vec[1] << ", " << vec[2] << ")";

	return ss.str();
}

/*
 * 'CoreTP1' is a super class of 'Core' (CoreTP1 extends Core)
 *
 * Initialization, between 'CoreTP1::CoreTP1() :' and '{'
 *     - Calling the base class constructor (calling 'Core' constructor)
 *     - Initializing protected member 'b' (of type Box) with a new 'vec4'
 *     - Initializing protected member 'b2' (of type Box) with a new 'vec4'
 *     - Initializing protecter member 'f' (of type float) with '0'
 *
 * 'Box' class defined in 'scene' (.h/.ccp)
 * 'vec4' is part of GLM
 */
CoreTP1::CoreTP1() :
	Core(),
	dummyEnemy(0, 0, 50, 0, 0, 0),
	projectile(3, 0, 0, 0, 0, 5)
{
	/* '_viewMatrix' defined in 'core.h' with type 'glm::mat4'
	 * It is a protected property of 'Core' (the superclass of the current class)
	 *
	 * More info about 'glm::lookAt' @ http://stackoverflow.com/questions/21830340/understanding-glmlookat
	 * Arguments are "eye", "center", "up"
	 *
	 * +x is pointing towards left
	 * +y is pointing towards top
	 * +z is pointing towards background
	 * */
	// default = 0, 3, -6 ... 0,0,0 .. 0,1,0
	_viewMatrix = glm::lookAt(glm::vec3(0, 45, -25), glm::vec3(0, 0, 20), glm::vec3(0, 1, 0));

	for (glm::vec3 position : spaceship.getPosition())
	{
		_LOG_INFO() << position.x << ", " << position.y << ", " << position.z;
	}

}

void CoreTP1::Render(double dt)
{
	spaceship.render(dt);
	dummyEnemy.render(dt);
	projectile.render(dt);

	spaceship.checkCollisionWith(dummyEnemy);

	bool coll = dummyEnemy.checkCollisionWithProjectile(projectile);

	if (coll)
	{
		_LOG_INFO() << "=== Projectile collision ===";
	}
}

CoreTP1::~CoreTP1()
{
}

void CoreTP1::OnKeyW(bool down)
{
	_LOG_INFO() << "W, down=" << down;

	if (down)
	{
		spaceship.goForward();
	}
	else
	{
		spaceship.stopGoingForward();
	}
}

void CoreTP1::OnKeyA(bool down)
{
	_LOG_INFO() << "A, down=" << down;

	if (down)
	{
		spaceship.goLeft();
	}
	else
	{
		spaceship.stopGoingLeft();
	}
}

void CoreTP1::OnKeyS(bool down)
{
	_LOG_INFO() << "S, down=" << down;

	if (down)
	{
		spaceship.goBackward();
	}
	else
	{
		spaceship.stopGoingBackward();
	}
}

void CoreTP1::OnKeyD(bool down)
{
	_LOG_INFO() << "D, down=" << down;

	if (down)
	{
		spaceship.goRight();
	}
	else
	{
		spaceship.stopGoingRight();
	}
}


