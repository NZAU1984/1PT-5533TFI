#pragma once

#include <main.h>

#include "scene.h"

#include "BoundingBox.h"

#include <list>

using namespace glm;

class ThreeDObject
{
public:
	virtual void render(double dt) = 0;

	virtual ~ThreeDObject();

	bool checkCollisionWith(ThreeDObject& otherObject);

protected:
	BoundingBox* _boundingBox = NULL;

	std::list<Shape *> _shapeList;

	void _addShapeToList(Shape* shape);

	void _defineBoundingBox();

	void _translateBoundingBox(float dx, float dy, float dz);

	BoundingBox* _getBoundingBox();
};