#include "BoundingBox.h"

/* Constructor, defines 8 required vertices to create an appropriate box that can handle rotations. */
BoundingBox::BoundingBox(double minX, double minY, double minZ, double maxX, double maxY, double maxZ)
{
	_LOG_INFO() << "BB constructor";
	_minX = minX;
	_maxX = maxX;
	_minY = minY;
	_maxY = maxY;
	_minZ = minZ;
	_maxZ = maxZ;

	_LOG_INFO() << "X [" << minX << ", " << maxX << " Y[" << minY << ", " << maxY << "] Z[" << minZ << ", " << maxZ << "]";
}

void BoundingBox::translate(double dx, double dy, double dz)
{
	_minX += dx;
	_maxX += dx;
	_minY += dy;
	_maxY += dy;
	_minZ += dz;
	_maxZ += dz;

	//_LOG_INFO() << "X [" << _minX << ", " << _maxX << " Y[" << _minY << ", " << _maxY << "] Z[" << _minZ << ", " << _maxZ << "]";
}

bool BoundingBox::checkCollision(BoundingBox* otherBox)
{
	if (
		   (_maxZ < otherBox->_minZ)
		|| (_minZ > otherBox->_maxZ)
		|| (_maxX < otherBox->_minX)
		|| (_minX > otherBox->_maxX)
		|| (_maxY < otherBox->_minY)
		|| (_minY > otherBox->_maxY)
	)
	{
		return false;
	}

	_LOG_INFO() << "COLLIDE !";

	return true;
}

bool BoundingBox::containsPoint(glm::vec3* point)
{
	if (
		(_maxZ < point->z)
		|| (_minZ > point->z)
		|| (_maxX < point->x)
		|| (_minX > point->x)
		|| (_maxY < point->y)
		|| (_minY > point->y)
		)
	{
		return false;
	}

	return true;
}
