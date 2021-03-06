#pragma once
#include "Hello.h"

namespace hello_triangle
{

	class Exercise1 : public Hello
	{
	public:
		Exercise1();
		~Exercise1();

		void Draw();

	private:
		const float m_Vertices[18] = {
			// left triangle
			-0.7f, -0.3f, 0.0f,
			-0.3f, -0.3f, 0.0f,
			-0.5f,  0.2f, 0.0f,
			// right triangle
			 0.3f, -0.3f, 0.0f,
			 0.7f, -0.3f, 0.0f,
			 0.5f,  0.2f, 0.0f
		};

		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_ShaderProgram;
	};

}