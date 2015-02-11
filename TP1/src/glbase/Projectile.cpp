#include "Projectile.h"

Projectile::Projectile(double x, double y, double z, double dx, double dy, double dz) :
	_outerSphere(glm::vec4(1.0f, 1.0f, 0, 0.7f), 16, 16, 5.0f),
	_innerSphere(glm::vec4(0, 1.0f, 0, 1), 16, 16, 2.5f),
	_positionX(x),
	_positionY(y),
	_positionZ(z),
	_dx(dx),
	_dy(dy),
	_dz(dz)
{
	_outerSphere.AddChild(&_innerSphere);
}

Projectile::~Projectile()
{

}

void Projectile::render(double dt)
{
	double positionXCopy = _positionX;
	double positionYCopy = _positionY;
	double positionZCopy = _positionZ;

	_positionX += _dx * dt;
	_positionY += _dy * dt;
	_positionZ += _dz * dt;

	_outerSphere.SetTransform(glm::translate(glm::mat4(), glm::vec3(_positionX, _positionY, _positionZ)));

	_outerSphere.Render();
	_innerSphere.Render();
}

glm::vec3 Projectile::getPosition()
{
	return glm::vec3(_positionX, _positionY, _positionZ);
}

glm::vec3 Projectile::getOrientationVector()
{
	return glm::vec3(_dx, _dy, _dz);
}