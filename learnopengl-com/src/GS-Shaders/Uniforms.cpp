#include "Uniforms.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../util/Shader.h"


Uniforms::Uniforms()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_Triangle), m_Triangle, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	unsigned int vertex_shader;
	unsigned int fragment_shader;
	util::CompileShader("res/shader/vertex.shader", GL_VERTEX_SHADER, vertex_shader);
	util::CompileShader("res/shader/fragment_uniform.shader", GL_FRAGMENT_SHADER, fragment_shader);
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
		std::cout << "ERRO::SHADER::LINKING_FAILED" << info_log << '\n';
	}
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}


Uniforms::~Uniforms()
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteProgram(m_ShaderProgram);
}


void Uniforms::Draw()
{
	m_ColorUniformLocation = glGetUniformLocation(m_ShaderProgram, "myColor");
	glUseProgram(m_ShaderProgram);
	float time = glfwGetTime();
	float green = sin(time / 2.0f) + 0.5f;
	glUniform4f(m_ColorUniformLocation, 0.0f, green, 0.0f, 1.0f);

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
}