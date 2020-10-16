#pragma once

#include <string>

#include "../core/Shader.h"


namespace getting_started
{

	class MixUniform
	{
	public:
		MixUniform(const std::string & fragment_path);
		~MixUniform();
		void Draw();
		float UpdatetMix(const float mix_value);

	private:
		const float m_Rectangle[32] = {
			// Position			// Color		  // Texture coords
			 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f
		};

		const unsigned int m_Indices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		core::Shader m_ShaderProgram;
		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_EBO;
		unsigned int m_Textures[2];
		float m_Mix;
	};

}