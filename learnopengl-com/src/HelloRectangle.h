#pragma once

#include "Hello.h"

class HelloRectangle : public Hello
{
public:
	HelloRectangle();
	~HelloRectangle();
	void Draw();

private:
	const float m_Vertices[12] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	const unsigned int m_Indices[6] = {
		0, 1, 2, // first triangle
		0, 2, 3  // second triangle
	};

	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_EBO;

	unsigned int m_ShaderProgram;
};

