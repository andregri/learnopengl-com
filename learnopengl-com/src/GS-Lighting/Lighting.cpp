#include "Lighting.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace getting_started
{

	Lighting::Lighting()
		: m_ShaderProgram("res/shader/GS-Lighting/vertex.shader", "res/shader/GS-Lighting/object_fragment.shader"),
		m_LightingShader("res/shader/GS-Lighting/vertex.shader",  "res/shader/GS-Lighting/light_fragment.shader")
	{
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_Cube), m_Cube, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glGenVertexArrays(1, &m_LightVAO);
		glBindVertexArray(m_LightVAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		m_ShaderProgram.Use();
		m_ShaderProgram.SetUniformVec3f("objectColor", 1.0f, 0.5f, 0.31f);
		m_ShaderProgram.SetUniformVec3f("lightColor", 1.0f, 1.0f, 1.0f);
	}


	Lighting::~Lighting()
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteVertexArrays(1, &m_LightVAO);
		glDeleteBuffers(1, &m_VBO);
	}

	void Lighting::Draw()
	{
		m_ShaderProgram.Use();
		glm::mat4 model = glm::mat4(1.0f);
		m_ShaderProgram.SetUniformMatrix4fv("model", glm::value_ptr(model));
		glm::mat4 view = glm::lookAt(glm::vec3(2.0f, 1.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		m_ShaderProgram.SetUniformMatrix4fv("view", glm::value_ptr(view));
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		m_ShaderProgram.SetUniformMatrix4fv("projection", glm::value_ptr(projection));
		
		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		m_LightingShader.Use();
		glm::vec3 lightPos(1.2f, 1.0f, -2.0f);
		model = glm::translate(glm::mat4(1.0f), lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		m_LightingShader.SetUniformMatrix4fv("model", glm::value_ptr(model));
		m_LightingShader.SetUniformMatrix4fv("view", glm::value_ptr(view));
		m_LightingShader.SetUniformMatrix4fv("projection", glm::value_ptr(projection));

		glBindVertexArray(m_LightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

}