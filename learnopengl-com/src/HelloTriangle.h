#pragma once

#include "Hello.h"

class HelloTriangle : public Hello
{
public:
	HelloTriangle();
	~HelloTriangle();

	void Draw();

private:
	const float m_Vertices[9] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	unsigned int m_VAO;
	unsigned int m_VBO;
	
	unsigned int m_ShaderProgram;
};

