#pragma once

#include <main.h>

#include "scene.h"

#include "ThreeDObject.h"


using namespace glm;

class DummyEnemy : public ThreeDObject
{
public:
	DummyEnemy(double x, double y, double z, double dx, double dy, double dz);

	virtual ~DummyEnemy();

	void render(double dt);

protected:
	Box _box;
	Cylinder _cylinder;
	Sphere _sphere;

	double _positionX;
	double _positionY;
	double _positionZ;

	double _dx;
	double _dy;
	double _dz;
};