#include "tp1.h"

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
CoreTP1::CoreTP1() : Core(), b(vec4(1, 0, 0, 0.5f)), b2(vec4(0, 1, 0, 1)), f(0)
{
	/* '_viewMatrix' defined in 'core.h' with type 'glm::mat4'
	 * It is a protected property of 'Core' (the superclass of the current class)
	 *
	 * More info about 'glm::lookAt' @ http://stackoverflow.com/questions/21830340/understanding-glmlookat
	 * Arguments are "eye", "center", "up"
	 * */
	_viewMatrix = glm::lookAt(glm::vec3(0, 3, -6), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	b.AddChild(&b2);
}

void CoreTP1::Render(double dt)
{
	b.SetTransform(glm::scale(glm::rotate(glm::mat4(), f, glm::normalize(glm::vec3(0, 0.5f, 0.5f))), vec3(2, 1, 1)));
	b2.SetTransform(glm::scale(glm::translate(glm::mat4(), glm::vec3(2, 0, 0)), vec3(1, 2, 2)));
	b2.Render();
	b.Render();

	DrawText("Hello World!", glm::vec2(0.5f, 0.5f), glm::vec4(1, 1, 0, 1), 32, ALIGN_CENTER);

	f += (float)dt * 2 * glm::pi<float>() * 0.1f;
}

CoreTP1::~CoreTP1()
{
}

void CoreTP1::OnKeyW(bool down)
{
	_LOG_INFO() << "W";
}
