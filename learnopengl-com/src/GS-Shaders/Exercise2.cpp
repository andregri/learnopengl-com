#include "Exercise2.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace getting_started
{

	Exercise2::Exercise2()
		: m_ShaderProgram("res/shader/right_shift_vertex.shader", "res/shader/fragment.shader")
	{
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_Triangle), m_Triangle, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBindVertexArray(0);
	}


	Exercise2::~Exercise2()
	{
		glDeleteBuffers(1, &m_VBO);
		glDeleteVertexArrays(1, &m_VAO);
	}

	void Exercise2::Draw()
	{
		m_ShaderProgram.Use();
		float time = glfwGetTime();
		m_ShaderProgram.SetUniform1f("x_offset", sin(time));
		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
	}
}