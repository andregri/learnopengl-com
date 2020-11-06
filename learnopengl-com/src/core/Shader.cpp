#include "Shader.h"

#include <GL/glew.h>

#include <iostream>

#include "../util/Shader.h"


namespace core
{

	Shader::Shader(const std::string & vertex_path, const std::string & fragment_path)
	{
		unsigned int vertexShader, fragmentShader;
		util::CompileShader(vertex_path, GL_VERTEX_SHADER, vertexShader);
		util::CompileShader(fragment_path, GL_FRAGMENT_SHADER, fragmentShader);

		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertexShader);
		glAttachShader(m_ID, fragmentShader);
		glLinkProgram(m_ID);
		GLint success;
		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
		if (success != GL_TRUE)
		{
			GLsizei log_length = 0;
			GLchar info_log[1024];
			glGetProgramInfoLog(m_ID, 1024, &log_length, info_log);
			std::cout << "ERROR::SHADER::LINKING_FAILED" << info_log << '\n';
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}


	Shader::~Shader()
	{
		glDeleteProgram(m_ID);
	}

	void Shader::Use()
	{
		glUseProgram(m_ID);
	}

	void Shader::SetUniform1i(const std::string & name, const int value)
	{
		int location = glGetUniformLocation(m_ID, name.c_str());
		if (location != -1)
			glUniform1i(location, value);
		else
			std::cout << "ERROR::UNIFORM::" << name << "::NOT_FOUND\n";
	}

	void Shader::SetUniform1f(const std::string & name, const float value)
	{
		int location = glGetUniformLocation(m_ID, name.c_str());
		if (location != -1)
			glUniform1f(location, value);
		else
			std::cout << "ERROR::UNIFORM::" << name << "::NOT_FOUND\n";
	}

	void Shader::SetUniformVec3f(const std::string & name, const float v0, const float v1, const float v2)
	{
		int location = glGetUniformLocation(m_ID, name.c_str());
		if (location != -1)
			glUniform3f(location, v0, v1, v2);
		else
			std::cout << "ERROR::UNIFORM::" << name << "::NOT_FOUND\n";
	}

	void Shader::SetUniformMatrix4fv(const std::string & name, const float * matrix)
	{
		int location = glGetUniformLocation(m_ID, name.c_str());
		if (location != -1)
			glUniformMatrix4fv(location, 1, GL_FALSE, matrix);
		else
			std::cout << "ERROR::UNIFORM::" << name << "::NOT_FOUND\n";
	}
}