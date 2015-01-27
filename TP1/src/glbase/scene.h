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

protected:
	GLuint _vertexBuffer, _indexBuffer, _vao;
	vec4 _color;
};

class Box : public Shape
{
public:
	Box(vec4 color);

	virtual void Render() override;
};