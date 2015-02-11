#pragma once

#include <main.h>

using namespace glm;

class BoundingBox
{
public:
	BoundingBox(double minX, double minY, double minZ, double maxX, double maxY, double maxZ);

	void translate(double dx, double dy, double dz);

	bool checkCollision(BoundingBox* otherBox);

	bool containsPoint(glm::vec3* point);

protected:
	/* Using vec4 and not vec3 to store vertices because it's simplier this way to apply transformation matrices.
	   Otherwise it requires to convert a vec3 to a vec3 and then convert that vec4 to a vec3. */
	glm::vec4 _vertices[8];

	double _centerX;
	double _centerY;
	double _centerZ;

	double _minX;
	double _maxX;
	double _minY;
	double _maxY;
	double _minZ;
	double _maxZ;
};