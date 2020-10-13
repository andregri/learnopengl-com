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

		void SetUniform1f(const std::string & name, float value);

	private:
		unsigned int m_ID;
	};

}