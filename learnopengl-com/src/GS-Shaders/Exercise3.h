#pragma once

#include "../core/Shader.h"


namespace getting_started
{

	class Exercise3
	{
	public:
		Exercise3();
		~Exercise3();
		void Draw();

	private:
		const float m_Triangle[9] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		core::Shader m_ShaderProgram;
		unsigned int m_VAO;
		unsigned int m_VBO;
	};

}