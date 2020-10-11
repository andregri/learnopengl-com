#include "Exercise2.h"

#include <GL/glew.h>

#include <iostream>

#include "../util/Shader.h"


namespace hello_triangle
{

	Exercise2::Exercise2()
	{
		glGenVertexArrays(2, m_VAOs);
		glGenBuffers(2, m_VBOs);
		
		glBindVertexArray(m_VAOs[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_FirstTriangle), m_FirstTriangle, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);


		glBindVertexArray(m_VAOs[1]);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_SecondTriangle), m_SecondTriangle, GL_STATIC_DRAW);

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


	Exercise2::~Exercise2()
	{
		glDeleteBuffers(2, m_VBOs);
		glDeleteVertexArrays(2, m_VAOs);
		glDeleteProgram(m_ShaderProgram);
	}


	void Exercise2::Draw()
	{
		glUseProgram(m_ShaderProgram);

		glBindVertexArray(m_VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(m_VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);
	}

}