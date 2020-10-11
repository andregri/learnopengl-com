#include "Exercise1.h"

#include <GL/glew.h>

#include <iostream>

#include "../util/Shader.h"

namespace hello_triangle
{

	Exercise1::Exercise1()
	{
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), m_Vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		unsigned int vertex_shader;
		unsigned int fragment_shader;
		util::CompileShader("res/shader/vertex.shader", GL_VERTEX_SHADER, vertex_shader);
		util::CompileShader("res/shader/fragment.shader", GL_FRAGMENT_SHADER, fragment_shader);
		m_ShaderProgram = glCreateProgram();
		glAttachShader(m_ShaderProgram, vertex_shader);
		glAttachShader(m_ShaderProgram, fragment_shader);
		glLinkProgram(m_ShaderProgram);
		GLint link_success;
		glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &link_success);
		if (link_success != GL_TRUE)
		{
			GLsizei log_length = 0;
			GLchar info_log[1024];
			glGetProgramInfoLog(m_ShaderProgram, 1024, &log_length, info_log);
			std::cout << "ERROR::SHADER::LINKING_FAILED\n" << info_log << '\n';
		}
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
	}


	Exercise1::~Exercise1()
	{
		glDeleteBuffers(1, &m_VBO);
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteProgram(m_ShaderProgram);
	}

	void Exercise1::Draw()
	{
		glUseProgram(m_ShaderProgram);
		glBindVertexArray(m_VAO);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glBindVertexArray(0);
	}

}