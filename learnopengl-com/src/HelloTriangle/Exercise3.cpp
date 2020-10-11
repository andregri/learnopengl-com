#include "Exercise3.h"

#include <GL/glew.h>

#include <iostream>

#include "../util/Shader.h"


namespace hello_triangle
{

	Exercise3::Exercise3()
	{
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), m_Vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);


		unsigned int vertex_shader;
		unsigned int fragment_shader1;
		unsigned int fragment_shader2;
		util::CompileShader("res/shader/vertex.shader", GL_VERTEX_SHADER, vertex_shader);
		util::CompileShader("res/shader/fragment.shader", GL_FRAGMENT_SHADER, fragment_shader1);
		util::CompileShader("res/shader/fragment_yellow.shader", GL_FRAGMENT_SHADER, fragment_shader2);

		m_ShaderPrograms[0] = glCreateProgram();
		glAttachShader(m_ShaderPrograms[0], vertex_shader);
		glAttachShader(m_ShaderPrograms[0], fragment_shader1);
		glLinkProgram(m_ShaderPrograms[0]);
		GLint link_success;
		glGetProgramiv(m_ShaderPrograms[0], GL_LINK_STATUS, &link_success);
		if (link_success != GL_TRUE)
		{
			GLsizei log_length = 0;
			GLchar info_log[1024];
			glGetProgramInfoLog(m_ShaderPrograms[0], 1024, &log_length, info_log);
			std::cout << "ERROR::SHADER::LINKING_FAILED\n" << info_log << '\n';
		}

		m_ShaderPrograms[1] = glCreateProgram();
		glAttachShader(m_ShaderPrograms[1], vertex_shader);
		glAttachShader(m_ShaderPrograms[1], fragment_shader2);
		glLinkProgram(m_ShaderPrograms[1]);
		glGetProgramiv(m_ShaderPrograms[1], GL_LINK_STATUS, &link_success);
		if (link_success != GL_TRUE)
		{
			GLsizei log_length = 0;
			GLchar info_log[1024];
			glGetProgramInfoLog(m_ShaderPrograms[1], 1024, &log_length, info_log);
			std::cout << "ERROR::SHADER::LINKING_FAILED\n" << info_log << '\n';
		}

		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader1);
		glDeleteShader(fragment_shader2);
	}


	Exercise3::~Exercise3()
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteProgram(m_ShaderPrograms[0]);
		glDeleteProgram(m_ShaderPrograms[1]);
	}


	void Exercise3::Draw()
	{
		glBindVertexArray(m_VAO);
		
		glUseProgram(m_ShaderPrograms[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(m_ShaderPrograms[1]);
		glDrawArrays(GL_TRIANGLES, 3, 3);

		glBindVertexArray(0);
	}

}