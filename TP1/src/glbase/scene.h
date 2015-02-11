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

	virtual bool containsPoint(glm::vec3 point, glm::vec3 orientation) = 0;

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

	//BoundingBox* _boundingBox;

	glm::vec3 getCenterVector() const;

	GLuint _vertexBuffer, _indexBuffer, _vao;
	
	vec4 _color;

};

class Box : public Shape
{
public:
	//Box(vec4 color);
	Box(vec4 color, const mat4& initialTransformationMatrix = glm::mat4());

	virtual void Render() override;

	bool containsPoint(glm::vec3 point, glm::vec3 orientation);

protected:
	vec4 _leftTopFrontVertex;
	vec4 _leftTopBackVertex;
	vec4 _rightTopBackVertex;
	vec4 _rightTopFrontVertex;
	vec4 _leftBottomFrontVertex;
	vec4 _leftBottomBackVertex;
	vec4 _rightBottomBackVertex;
	vec4 _rightBottomFrontVertex;

	vec4 _vertices[8];

	vec4 _currentLeftTopFrontVertex;
	vec4 _currentLeftTopBackVertex;
	vec4 _currentRightTopBackVertex;
	vec4 _currentRightTopFrontVertex;
	vec4 _currentLeftBottomFrontVertex;
	vec4 _currentLeftBottomBackVertex;
	vec4 _currentRightBottomBackVertex;
	vec4 _currentRightBottomFrontVertex;

	vec3 _currentVertices[8];

	bool _verticesWereRecalculated = false;

	void _transformVertices();

	bool _parallelogramContainsPoint(glm::vec3 P, glm::vec3 orientation, glm::vec3 A, glm::vec3 B, glm::vec3 C, glm::vec3 D, ::vec3& intersection);
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

	bool collisionDetected(const Sphere& sphereShape) const;

	float getRadius() const;

	bool containsPoint(glm::vec3 point, glm::vec3 orientation);

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

	bool containsPoint(glm::vec3 point, glm::vec3 orientation);

protected:
	uint _nSlices, _nTrianglesOnSide, _offsetTop, _offsetSide, _offsetBottom;
};