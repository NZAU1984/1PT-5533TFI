#include "ThreeDObject.h"

ThreeDObject::~ThreeDObject()
{
	_LOG_INFO() << "~ThreeDObject";
	delete _boundingBox;
}

void ThreeDObject::_addShapeToList(Shape* shape)
{
	_shapeList.push_back(shape);
}

void ThreeDObject::_defineBoundingBox()
{
	float minX = 0;
	float maxX = 0;
	float minY = 0;
	float maxY = 0;
	float minZ = 0;
	float maxZ = 0;
	bool firstItem = true;

	for (auto it = _shapeList.begin(), itEnd = _shapeList.end(); it != itEnd; ++it)
	{
		if (firstItem)
		{
			minX = (*it)->getMinX();
			maxX = (*it)->getMaxX();
			minY = (*it)->getMinY();
			maxY = (*it)->getMaxY();
			minZ = (*it)->getMinZ();
			maxZ = (*it)->getMaxZ();

			firstItem = false;
		}
		else
		{
			minX = min(minX, (*it)->getMinX());
			maxX = max(maxX, (*it)->getMaxX());
			minY = min(minY, (*it)->getMinY());
			maxY = max(maxY, (*it)->getMaxY());
			minZ = min(minZ, (*it)->getMinZ());
			maxZ = max(maxZ, (*it)->getMaxZ());
		}
	}

	/* Created on heap, deleted in destructor. */
	_boundingBox = new BoundingBox(minX, minY, minZ, maxX, maxY, maxZ);
}

void ThreeDObject::_translateBoundingBox(float dx, float dy, float dz)
{
	_boundingBox->translate(dx, dy, dz);
}

BoundingBox* ThreeDObject::_getBoundingBox()
{
	return _boundingBox;
}

bool ThreeDObject::checkCollisionWith(ThreeDObject& otherObject)
{

	return _getBoundingBox()->checkCollision(otherObject._getBoundingBox());
}

bool ThreeDObject::checkCollisionWithProjectile(Projectile& projectile)
{
	for (auto it = _shapeList.begin(), itEnd = _shapeList.end(); it != itEnd; ++it)
	{
		if ((*it)->containsPoint(projectile.getPosition()))
		{
			return true;
		}
	}

	return false;
}