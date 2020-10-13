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

	void Shader::SetUniform1f(const std::string & name, float value)
	{
		unsigned int location = glGetUniformLocation(m_ID, name.c_str());
		if (location != -1)
			glUniform1f(location, value);
		else
			std::cout << "ERROR::UNIFORM::" << name << "::NOT_FOUND\n";
	}

}