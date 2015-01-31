#pragma once
#include <main.h>
#include "core.h"
#include "scene.h"

class CoreTP1 : public Core
{
public:
	CoreTP1();
	virtual ~CoreTP1() override;

protected:
	virtual void Render(double dt) override;
	virtual void OnKeyW(bool down) override;

protected:
	Box b, b2;
	Sphere sphere;
	Cylinder cylinder, cylinder1;
	float f;
};