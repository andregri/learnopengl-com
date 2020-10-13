#include "Exercise3.h"

#include <GL/glew.h>

namespace getting_started
{

	Exercise3::Exercise3()
		: m_ShaderProgram("res/shader/output_position_vertex.shader", "res/shader/position_as_color_fragment.shader")
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


	Exercise3::~Exercise3()
	{
		glDeleteBuffers(1, &m_VBO);
		glDeleteVertexArrays(1, &m_VAO);
	}

	void Exercise3::Draw()
	{
		m_ShaderProgram.Use();
		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
	}

}