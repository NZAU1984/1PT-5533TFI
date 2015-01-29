#include "scene.h"

#include <string>
#include <vector>

#pragma region NODE

GLint Node::uniform_model = -1, Node::uniform_color = -1;
GLint Node::attribute_position = 1, Node::attribute_normal = 2;

void Node::InitializePreLink(GLuint program)
{
	glBindAttribLocation(program, attribute_position, "in_position");
	glBindAttribLocation(program, attribute_normal, "in_normal");
}

void Node::InitializePostLink(GLuint program)
{
	uniform_model = glGetUniformLocation(program, "model");
	uniform_color = glGetUniformLocation(program, "color");
}

Node::Node()
	: _transform(), _children(), _parent(nullptr)
{ }

void Node::SetTransform(const mat4 &transform)
{
	_transform = transform;
}

void Node::AddChild(Node *child)
{
	_children.push_back(child);
	child->_parent = this;
}

glm::mat4 Node::fullTransform() const
{
	if (_parent == nullptr)
		return _transform;
	else
		return _parent->fullTransform() * _transform;
}

#pragma endregion

#pragma region SHAPE

void Shape::Render()
{
	glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(fullTransform()));
	glUniform4fv(uniform_color, 1, glm::value_ptr(_color));

	if (_color.a < 1)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthMask(GL_FALSE);
	}
	else
	{
		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);
	}
}

Shape::~Shape()
{
	if (_vertexBuffer != BAD_BUFFER)
		glDeleteBuffers(1, &_vertexBuffer);

	if (_indexBuffer != BAD_BUFFER)
		glDeleteBuffers(1, &_indexBuffer);

	glDeleteVertexArrays(1, &_vao);
}
#pragma endregion

#pragma region BOX

Box::Box(vec4 color)
{
	_vertexBuffer = _indexBuffer = BAD_BUFFER;

	_color = color;

	VertexPositionNormal vertices[36] = {
		{ vec3(0, 0, 0), vec3(0, -1, 0) },
		{ vec3(1, 0, 0), vec3(0, -1, 0) },
		{ vec3(0, 0, 1), vec3(0, -1, 0) },

		{ vec3(0, 0, 1), vec3(0, -1, 0) },
		{ vec3(1, 0, 0), vec3(0, -1, 0) },
		{ vec3(1, 0, 1), vec3(0, -1, 0) },


		{ vec3(1, 0, 0), vec3(1, 0, 0) },
		{ vec3(1, 1, 0), vec3(1, 0, 0) },
		{ vec3(1, 0, 1), vec3(1, 0, 0) },

		{ vec3(1, 0, 1), vec3(1, 0, 0) },
		{ vec3(1, 1, 0), vec3(1, 0, 0) },
		{ vec3(1, 1, 1), vec3(1, 0, 0) },


		{ vec3(1, 1, 0), vec3(0, 1, 0) },
		{ vec3(0, 1, 1), vec3(0, 1, 0) },
		{ vec3(1, 1, 1), vec3(0, 1, 0) },

		{ vec3(0, 1, 0), vec3(0, 1, 0) },
		{ vec3(0, 1, 1), vec3(0, 1, 0) },
		{ vec3(1, 1, 0), vec3(0, 1, 0) },


		{ vec3(0, 1, 1), vec3(-1, 0, 0) },
		{ vec3(0, 1, 0), vec3(-1, 0, 0) },
		{ vec3(0, 0, 1), vec3(-1, 0, 0) },

		{ vec3(0, 1, 0), vec3(-1, 0, 0) },
		{ vec3(0, 0, 0), vec3(-1, 0, 0) },
		{ vec3(0, 0, 1), vec3(-1, 0, 0) },


		{ vec3(0, 0, 1), vec3(0, 0, 1) },
		{ vec3(1, 0, 1), vec3(0, 0, 1) },
		{ vec3(0, 1, 1), vec3(0, 0, 1) },

		{ vec3(1, 0, 1), vec3(0, 0, 1) },
		{ vec3(1, 1, 1), vec3(0, 0, 1) },
		{ vec3(0, 1, 1), vec3(0, 0, 1) },


		{ vec3(0, 0, 0), vec3(0, 0, -1) },
		{ vec3(0, 1, 0), vec3(0, 0, -1) },
		{ vec3(1, 0, 0), vec3(0, 0, -1) },

		{ vec3(1, 0, 0), vec3(0, 0, -1) },
		{ vec3(0, 1, 0), vec3(0, 0, -1) },
		{ vec3(1, 1, 0), vec3(0, 0, -1) }
	};

    for (uint x = 0; x < 36; x++)
		vertices[x].position -= 0.5;

	// Create Vertex Array Object
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	// Generate Vertex Buffer
	glGenBuffers(1, &_vertexBuffer);

	// Fill Vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Set Vertex Attributes
	glEnableVertexAttribArray(attribute_position);
	glVertexAttribPointer(attribute_position, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionNormal), (const GLvoid*)0);
	glEnableVertexAttribArray(attribute_normal);
	glVertexAttribPointer(attribute_normal, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionNormal), (const GLvoid*)(0 + sizeof(vec3)));

	glBindVertexArray(0);

	debugGLError();
}

void Box::Render()
{
	Shape::Render();

	glBindVertexArray(_vao);
	
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);
}

#pragma endregion

#pragma region SPHERE

Sphere::Sphere(vec4 color, int nUpperStacks, int nSlices, float radius) :
	/* Total number of stacks, '+ 1' is for the middle stack. */
	_nStacks(2 * nUpperStacks + 1),

	_nSlices(nSlices),

	/* Total number of elements in vertexOrderVector. For every triangle, there are 3 indices corresponding each to a
	specific vertex.
	- First part (nSlices * 3 * 2): the top and bottom parts are like a pie, there's a center vertex (the very top of
	    the sphere / the very bottom of the sphere) and vertices around it. For each part, there are 'nSlices'
		triangles, each triangles having 3 coordinates. Since we have two parts, we multiply by '2'.
	- Second part (2 * nSlices * nUpperStacks * 3 * 2): there are '2 * nUpperStacks' "in between two stacks" parts. For
	    each, there are '2 * nSlices' triangles because each vertex of a stack 'A' (which is further away from the
	    center stack than stack 'B') is linked to the corresponding vertex on stack 'B' (same theta angle) and one
	    triangle is formed with the vertex "to the right", and another with the vertex "to the left" on stack 'B'.
		Finally, we multiply by '3' because there are 3 vertices per triangle.
	*/
	_vertexOrderVectorSize((2 * (nSlices * 3)) + (((2 * nUpperStacks) * (2 * nSlices)) * 3)),
	
	_radius(radius)
{
	_vertexBuffer = _indexBuffer = BAD_BUFFER;

	_color = color;

	/* Total number of vertices. '+ 2' for top and bottom vertices. */
	int nTotalVertices = (_nSlices * _nStacks) + 2;

	/* Array of vertices
	=> 'NEW' OPERATOR :: CREATED ON HEAP :: POSSIBLE MEMORY LEAK => solved by using 'delete[]' further below. 
	*/
	VertexPositionNormal* vertices = new VertexPositionNormal[nTotalVertices];

	/* Indices of top and bottom vertices. Indices will go from the highest vertex (topIndex) to the lower vertex
	(bottomIndex). The order of vertices on every stack will be the same (going in the same direction). */
	int topIndex = 0;
	int bottomIndex = nTotalVertices - 1;

	/* Top and bottom vertices. */
	vertices[topIndex] = { vec3(0, _radius, 0), vec3(0, 1, 0) };
	vertices[bottomIndex] = { vec3(0, -_radius, 0), vec3(0, -1, 0) };

	/* This will tell OpenGL in which order to use the vertices to create all required triangles. Indices are not
	important (that's why we use a vector instead of an array like for vertices), the only important thing is that
	vertex indices for the same triangle be consecutive elements. */
	std::vector<GLuint> vertexOrderVector;

	/* Let's build the triangles for the top and bottom parts which are simply like a pie. */
	for (int i = 1, iMax = _nSlices; i <= iMax; ++i)
	{
		/* Top part. Each triangle always starts from the center vertex. */
		vertexOrderVector.push_back(topIndex);
		vertexOrderVector.push_back(i);
		vertexOrderVector.push_back((i == _nSlices) ? 1 : (i + 1));

		/* Bottom part. Each triangle always starts from the center vertex. */
		vertexOrderVector.push_back(bottomIndex);
		vertexOrderVector.push_back(bottomIndex - i);
		vertexOrderVector.push_back((i == _nSlices) ? (bottomIndex - 1) : (bottomIndex - i - 1));
	}

	/* Let's build the sphere with two loops. The outter loop is for stacks, the inner loop is for vertices all around
	a specific stack. We only loop through the upper stacks and reflect the upper vertices on the lower part by
	inverting the Y coordinates. */
	for (int currentStack = 0; currentStack <= nUpperStacks; ++currentStack)
	{
		/* Phi is the angle used on the Y axis. In a sphere, the top is pi/2, and the bottom is -pi/2. Here we
		calculate the phi angle for the current stack. */
		float phi = (glm::pi<float>() / _nStacks) * (nUpperStacks - currentStack);
			//(glm::pi<float>() / 2) - (((glm::pi<float>() / 2) / (nUpperStacks + 1)) * (currentStack + 1));

		float currentY = _radius * glm::sin(phi);

		/* The radius of every stack is dependent on phi. It's smaller at the top, larger at the center. */
		float currentRadius = _radius * glm::cos(phi);

		/* Indices used in the vertex array. */
		int upperStackOffset	= ((currentStack) * _nSlices) + 1;
		int lowerStackOffset = ((_nStacks - currentStack - 1) * _nSlices) + 1;

		/* For every stack, let's go around the circle and determine the X and Z coordinates. */
		for (int currentSlice = 0; currentSlice < _nSlices; ++currentSlice)
		{
			/* Indices of current vertices.  */
			topIndex = upperStackOffset + currentSlice;
			bottomIndex = lowerStackOffset + currentSlice;

			/* Theta is used to go around a stack to defined X and Z. */
			float theta = ((glm::pi<float>() * 2) / _nSlices) * currentSlice;

			float currentX = currentRadius * glm::cos(theta);
			float currentZ = currentRadius * glm::sin(theta);

			/* Upper and lower vertices for current X and Z (and Y) coordinates. We flip the sign of Y to reflect the
			upper vertex on the bottom. */
			vertices[topIndex] = {vec3(currentX, currentY, currentZ), glm::normalize(vec3(currentX, currentY, currentZ))};
			vertices[bottomIndex] = { vec3(currentX, -currentY, currentZ), glm::normalize(vec3(currentX, -currentY, currentZ)) };

			/* Let's build triangles with indices. The center stack won't enter this block because it does not have to
			create any triangles. The stack right above it and the one right below it will build triangles with its
			vertices. */
			if (upperStackOffset != lowerStackOffset)
			{
				/* Upper triangles. */
				vertexOrderVector.push_back(topIndex);
				vertexOrderVector.push_back(topIndex + _nSlices); // stack right below, vertex has same theta angle
				vertexOrderVector.push_back(topIndex + 1);

				vertexOrderVector.push_back(topIndex);
				vertexOrderVector.push_back(topIndex + _nSlices); // stack right below, vertex has same theta angle
				vertexOrderVector.push_back(topIndex + (_nSlices - 1)); // TODO extract expression cause repeated+++

				

				/* Lower triangles */
				vertexOrderVector.push_back(bottomIndex);
				vertexOrderVector.push_back(bottomIndex - _nSlices); // stack right above, vertex has same theta angle
				vertexOrderVector.push_back(bottomIndex - 1);

				vertexOrderVector.push_back(bottomIndex);
				vertexOrderVector.push_back(bottomIndex - _nSlices); // stack right above, vertex has same theta angle
				vertexOrderVector.push_back(bottomIndex - (_nSlices - 1));
			}
		}
	}

	// Create Vertex Array Object
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	// Generate Vertex Buffer
	glGenBuffers(1, &_vertexBuffer);

	// Fill Vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);

	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(vec3) * 2) * nTotalVertices, vertices, GL_STATIC_DRAW);

	/* Create an element buffer. */
	GLuint ebo;
	glGenBuffers(1, &ebo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * _vertexOrderVectorSize, &vertexOrderVector[0], GL_STATIC_DRAW);

	// Set Vertex Attributes
	glEnableVertexAttribArray(attribute_position);
	glVertexAttribPointer(attribute_position, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionNormal), (const GLvoid*)0);
	glEnableVertexAttribArray(attribute_normal);
	glVertexAttribPointer(attribute_normal, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionNormal), (const GLvoid*)(0 + sizeof(vec3)));

	glBindVertexArray(0);

	debugGLError();

	/* Prevents potential memory leak caused by 'new'. Since OpenGL copies vertices, we can delete the array. */
	delete[] vertices;
}

void Sphere::Render()
{
	Shape::Render();

	glBindVertexArray(_vao);

	/* This draws the sphere by using the list of vertices to tell OpenGL in which order to use them to create each
	triangle. */
	glDrawElements(GL_TRIANGLES, _vertexOrderVectorSize, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

#pragma endregion
