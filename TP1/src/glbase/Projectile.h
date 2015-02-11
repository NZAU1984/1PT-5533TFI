#pragma once

#include <main.h>

#include "scene.h"

using namespace glm;

class Projectile
{
public:
	Projectile(double x, double y, double z, double dx, double dy, double dz);

	virtual ~Projectile();

	void render(double dt);

	glm::vec3 getPosition();

	glm::vec3 getOrientationVector();

protected:
	Sphere _outerSphere;
	Sphere _innerSphere;

	double _positionX;
	double _positionY;
	double _positionZ;

	double _dx;
	double _dy;
	double _dz;
};