#pragma once

#include <main.h>

using namespace glm;

struct VertexPositionNormal
{
	vec3 position;
	vec3 normal;
};

class Node
{
public:
	static void InitializePreLink(GLuint program);
	static void InitializePostLink(GLuint program);

	Node();
	void SetTransform(const mat4 &transform);
	void AddChild(Node *child);

protected:
	glm::mat4 fullTransform() const;

	mat4 _transform;
	std::vector<Node*> _children;
	Node* _parent;

	static GLint uniform_model, uniform_color;
	static GLint attribute_position, attribute_normal;
};

class Shape : public Node
{
public:
	virtual void Render();
	virtual ~Shape();

	void color(const vec4& v) { _color = v; }
	const vec4& color() const { return _color; }

	virtual bool containsPoint(glm::vec3 point) = 0;

	float getMinX();
	float getMaxX();
	float getMinY();
	float getMaxY();
	float getMinZ();
	float getMaxZ();

protected:
	/* Used in shapes (like Sphere and Cylinder) to initially apply a transformation matrix on vertices created in the
	constructor to avoid applying that same transformation every time a frame is created. */
	void applyTransformatioMatrixAndDefineMinMaxXYZ(VertexPositionNormal* vertices, uint nVertices, const glm::mat4& transformationMatrix);

	float _minX;
	float _maxX;
	float _minY;
	float _maxY;
	float _minZ;
	float _maxZ;

	glm::mat4 _initialTransformationMatrix;

	GLuint _vertexBuffer, _indexBuffer, _vao;
	
	vec4 _color;

	bool _inverseTransformationMatrixWasCalculated = false;

	glm::mat4 _inverseTransformationMatrix;

};

class Box : public Shape
{
public:
	Box(vec4 color, const mat4& initialTransformationMatrix = glm::mat4());

	virtual void Render() override;

	bool containsPoint(glm::vec3 point);

protected:

};

/*
 Class Sphere

 Draws a sphere with one top vertex, one bottom vertex and nStacks stacks with nSlices vertices on each,
 so the total number of vertices is 2 + (_nStacks * _nSlices).

 A 'stack' here represents a fixed Y coordinate for which we create _nSlices (X, Z) coordinates that
 estimate a circle around the center ((X, Z) = (0, 0)).
*/
class Sphere : public Shape
{
public:
	/* Constructor */
	//Sphere(vec4 color, uint nUpperStacks, uint nSlices, float radius);
	Sphere(vec4 color, uint nUpperStacks, uint nSlices, float radius, const mat4& initialTransformationMatrix = glm::mat4());

	/* Rendering method. */
	virtual void Render() override;

	bool containsPoint(glm::vec3 point);

protected:
	/* Number of stacks and, for each stack, number of slices (vertices). */
	//uint _nStacks, _nSlices;
	uint _vertexOrderVectorSize;
	float _radius;
};

class Cylinder : public Shape
{
public:
	/* Constructor */
	//Cylinder(vec4 color, uint nSlices, float height, float radius);
	Cylinder(vec4 color, uint nSlices, float height, float radius, const mat4& initialTransformationMatrix = glm::mat4());

	/* Rendering method. */
	virtual void Render() override;

	bool containsPoint(glm::vec3 point);

protected:
	uint _nSlices, _nTrianglesOnSide, _offsetTop, _offsetSide, _offsetBottom, _height, _radius;
};