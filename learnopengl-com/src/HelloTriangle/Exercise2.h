#pragma once
#include "Hello.h"


namespace hello_triangle
{

	class Exercise2 : public Hello
	{
	public:
		Exercise2();
		~Exercise2();

		void Draw();

	private:
		const float m_FirstTriangle[9] = {
			// up triangle
			-0.5f,  0.1f, 0.0f,
			 0.5f,  0.1f, 0.0f,
			 0.0f,  0.6f, 0.0f,
		};

		const float m_SecondTriangle[9] = {
			// down triangle
			-0.5f, -0.1f, 0.0f,
			 0.5f, -0.1f, 0.0f,
			 0.0f, -0.6f, 0.0f
		};

		unsigned int m_VAOs[2];
		unsigned int m_VBOs[2];

		unsigned int m_ShaderProgram;
	};

}