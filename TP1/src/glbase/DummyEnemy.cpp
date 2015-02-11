#include "DummyEnemy.h"

DummyEnemy::DummyEnemy(double x, double y, double z, double dx, double dy, double dz) :
	_box(vec4(1, 1, 1, 1.0f), glm::scale(glm::mat4(), glm::vec3(10.0f, 10.0f, 10.0f))),
	_positionX(x),
	_positionY(y),
	_positionZ(z),
	_dx(dx),
	_dy(dy),
	_dz(dz)
{
	_LOG_INFO() << "DUMMY ENEMY";
	_addShapeToList(&_box);

	_defineBoundingBox();

	_translateBoundingBox(_positionX, _positionY, _positionZ);
}

DummyEnemy::~DummyEnemy()
{

}

void DummyEnemy::render(double dt)
{
	double positionXCopy = _positionX;
	double positionYCopy = _positionY;
	double positionZCopy = _positionZ;

	_positionX += _dx * dt;
	_positionY += _dy * dt;
	_positionZ += _dz * dt;

	_box.SetTransform(glm::translate(glm::mat4(), glm::vec3(_positionX, _positionY, _positionZ)));

	_translateBoundingBox(_dx * dt, _dy * dt, _dz * dt);

	_box.Render();
}