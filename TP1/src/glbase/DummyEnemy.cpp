#include "DummyEnemy.h"

glm::mat4 lalala {
	1, 0, 0, 0,
	-0.5f, 1, 0.5f, 0, // x = x - 0.5y ; z = z + 0.5y
	0, 0, 1, 0,
	0, 0, 0, 1
};

glm::mat4 ini = glm::rotate(glm::mat4(), glm::pi<float>() / 4, vec3(0, 1, 0)) * glm::rotate(glm::mat4(), glm::pi<float>() / 4, vec3(1, 0, 0)) * glm::scale(glm::mat4(), glm::vec3(1, 1, 1));

DummyEnemy::DummyEnemy(double x, double y, double z, double dx, double dy, double dz) :
	_box(vec4(1, 1, 1, 1.0f), lalala * glm::scale(glm::mat4(), glm::vec3(10.0f, 10.0f, 10.0f))),
	_cylinder(vec4(1, 1, 1, 1.0f), 10, 10, 3, ini),
	_sphere(vec4(1, 1, 1, 1.0f), 10, 10, 2.5f, glm::mat4()),
	_positionX(x),
	_positionY(y),
	_positionZ(z),
	_dx(dx),
	_dy(dy),
	_dz(dz)
{
	_LOG_INFO() << "DUMMY ENEMY";
	
	_addShapeToList(&_box);
	_addShapeToList(&_cylinder);
	_addShapeToList(&_sphere);

	_defineBoundingBox();

	_translateBoundingBox(_positionX, _positionY, _positionZ);
}

DummyEnemy::~DummyEnemy()
{
	_LOG_INFO() << "~DummyEnemy";
}

void DummyEnemy::render(double dt)
{
	_positionX += _dx * dt;
	_positionY += _dy * dt;
	_positionZ += _dz * dt;

	_box.SetTransform(glm::translate(glm::mat4(), glm::vec3(_positionX, _positionY, _positionZ)));

	_translateBoundingBox(_dx * dt, _dy * dt, _dz * dt);

	_cylinder.SetTransform(glm::translate(glm::mat4(), glm::vec3(_positionX, _positionY, -1)));

	_sphere.SetTransform(glm::translate(glm::mat4(), glm::vec3(_positionX, _positionY, 15)));

	_box.Render();
	//_cylinder.Render();
	_sphere.Render();
}