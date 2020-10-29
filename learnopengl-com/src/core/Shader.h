#pragma once

#include <string>


namespace core
{

	class Shader
	{
	public:
		Shader(const std::string & vertexPath, const std::string & fragmentPath);
		~Shader();
		void Use();

		void SetUniform1i(const std::string & name, const int value);
		void SetUniform1f(const std::string & name, const float value);
		void SetUniformVec3f(const std::string & name, const float v0, const float v1, const float v2);
		void SetUniformMatrix4fv(const std::string & name, const float * matrix);

	private:
		unsigned int m_ID;
	};

}