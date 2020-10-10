#include "HelloTriangle.h"

#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <string>

#include "util/Shader.h"


HelloTriangle::HelloTriangle()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), m_Vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	// you can safely unbind the VBO because glVertexAttribPointer registered the VBO as the registered vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO so that it is not modified accidentally by other VAo calls.
	glBindVertexArray(0);

	unsigned int vertex_shader;
	unsigned int fragment_shader;
	util::CompileShader("res/shader/vertex.shader", GL_VERTEX_SHADER, vertex_shader);
	util::CompileShader("res/shader/fragment.shader", GL_FRAGMENT_SHADER, fragment_shader);
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


HelloTriangle::~HelloTriangle()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteProgram(m_ShaderProgram);
}

void HelloTriangle::Draw()
{
	glUseProgram(m_ShaderProgram);
	glBindVertexArray(m_VAO);
	
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//glBindVertexArray(0); // no need to unbind it every time 
}
