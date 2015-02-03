#pragma once
#include <main.h>
#include "core.h"
#include "scene.h"
#include "spaceship.h"

class CoreTP1 : public Core
{
public:
	CoreTP1();
	virtual ~CoreTP1() override;

protected:
	virtual void Render(double dt) override;
	virtual void OnKeyW(bool down) override;

protected:
	/*Box mainBox, leftConnector, rightConnector;// ,// b2;
	Sphere sphere, sphere1;
	Cylinder cylinder, cylinder1;*/

	Sphere centerSphere;
	Spaceship spaceship;
	float f;
};