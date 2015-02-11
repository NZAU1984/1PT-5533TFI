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
	dummyEnemy(0, 0, 50, 0, 0, -1),
	projectile(0, 0, 0, 0, 0, 5)
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

	// TEMP

	float threshold = 0.0001f;

	vec3 P(6, 6.5f, 0.5f);

	vec3 A(5, 6, 0);
	vec3 B(7, 6, 0);
	vec3 C(6, 7, 1);
	vec3 D(8, 7, 1);

	vec3 ABxAD = glm::cross(A - B, A - D);
	vec3 ACxAD = glm::cross(A - C, A - D);

	vec3 PAxAB = glm::cross(P - A, A - B);
	vec3 PBxBD = glm::cross(P - B, B - D);
	vec3 PDxDC = glm::cross(P - D, D - C);
	vec3 PCxCA = glm::cross(P - C, C - A);

	float vol = sqrt(glm::dot(PAxAB, PAxAB)) / 2 + sqrt(glm::dot(PBxBD, PBxBD)) / 2 + sqrt(glm::dot(PDxDC, PDxDC)) / 2
		+ sqrt(glm::dot(PCxCA, PCxCA)) / 2;

	float volume = sqrt(glm::dot(ABxAD, ABxAD))/2 + sqrt(glm::dot(ACxAD, ACxAD))/2;

	if (abs(vol - volume) < threshold)
	{
		_LOG_INFO() << "inside";
	}

	/*
	vec3 pVec(glm::normalize(glm::cross(AB, AC)));
	float blabla = abs(pVec.x * (P.x - A.x) + pVec.y * (P.y - A.y) + pVec.z * (P.z - A.z));
	float threshold = 0.00001f;

	float PA_dot_AB = abs(glm::dot(PA, AB));
	float PA_dot_AC = abs(glm::dot(PA, AC));

	float AB_dot_AB = glm::dot(AB, AB);
	float AC_dot_AC = glm::dot(AC, AC);


	bool inside =
	(abs(pVec.x * (P.x - A.x) + pVec.y * (P.y - A.y) + pVec.z * (P.z - A.z)) <= threshold)
	&&
	(0 <= PA_dot_AB)
	&&
	(PA_dot_AB <= AB_dot_AB)
	&&
	(0 <= PA_dot_AC)
	&&
	(PA_dot_AC <= AC_dot_AC);

	_LOG_INFO() << "inside = " << inside;
	_LOG_INFO() << PA_dot_AB << " <= " << AB_dot_AB;
	_LOG_INFO() << PA_dot_AC << " <= " << AC_dot_AC;*/


	// x TEMP

}

void CoreTP1::Render(double dt)
{
	spaceship.render(dt);
	dummyEnemy.render(dt);
	projectile.render(dt);

	spaceship.checkCollisionWith(dummyEnemy);

	//projectile.checkCollisionWith(dummyEnemy);
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


