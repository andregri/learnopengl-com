#include "ColorAttribute.h"

#include <GL/Glew.h>

#include <iostream>

#include "../util/Shader.h"



ColorAttribute::ColorAttribute()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_Triangle), m_Triangle, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	unsigned int vertex_shader;
	unsigned int fragment_shader;
	util::CompileShader("res/shader/vertex_colorattr.shader", GL_VERTEX_SHADER, vertex_shader);
	util::CompileShader("res/shader/fragment_colorattr.shader", GL_FRAGMENT_SHADER, fragment_shader);
	m_ShaderProgram = glCreateProgram();
	glAttachShader(m_ShaderProgram, vertex_shader);
	glAttachShader(m_ShaderProgram, fragment_shader);
	glLinkProgram(m_ShaderProgram);
	GLint success;
	glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &success);
	if (success != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar info_log[1024];
		glGetProgramInfoLog(m_ShaderProgram, 1024, &log_length, info_log);
		std::cout << "ERROR::SHADER::LINKING_FAILED\n" << info_log << '\n';
	}
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}


ColorAttribute::~ColorAttribute()
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteProgram(m_ShaderProgram);
}


void ColorAttribute::Draw()
{
	glUseProgram(m_ShaderProgram);
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}