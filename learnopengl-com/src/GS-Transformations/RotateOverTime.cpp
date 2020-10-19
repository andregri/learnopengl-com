#include "RotateOverTime.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image/stb_image.h>

#include <iostream>
#include <string>

namespace getting_started
{

	RotateOverTime::RotateOverTime()
		: m_ShaderProgram("res/shader/GS-Transformations/transformation_vertex.shader", "res/shader/GS-Transformations/transformation_fragment.shader")
	{
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_Rectangle), m_Rectangle, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_Indices), m_Indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		const std::string paths[2] = {
			"res/textures/container.jpg",
			"res/textures/awesomeface.png"
		};

		glGenTextures(2, m_Textures);

		stbi_set_flip_vertically_on_load(true);
		for (int i = 0; i < 2; ++i)
		{
			int width, height, numChannels;
			unsigned char * data = stbi_load(paths[i].c_str(), &width, &height, &numChannels, 0);
			if (data)
			{
				glBindTexture(GL_TEXTURE_2D, m_Textures[i]);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

				GLenum format = GL_RGB;
				if (paths[i].find(".png") != std::string::npos)
					format = GL_RGBA;
				glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else
			{
				std::cout << "ERROR::IMAGES::" << paths[i] << "::FAILED_LOADING\n";
			}
			stbi_image_free(data);
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}


	RotateOverTime::~RotateOverTime()
	{
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_EBO);
		glDeleteTextures(2, m_Textures);
		glDeleteVertexArrays(1, &m_VAO);
	}

	

	void RotateOverTime::Draw()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_Textures[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_Textures[1]);

		glBindVertexArray(m_VAO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	void RotateOverTime::Update()
	{
		m_ShaderProgram.Use();

		m_ShaderProgram.SetUniform1i("texture1", 0);
		m_ShaderProgram.SetUniform1i("texture2", 1);

		// First rotate the container around the origin and then translate to the bottom-right corner.
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		m_ShaderProgram.SetUniformMatrix4fv("transform", glm::value_ptr(trans));
	}

	void RotateOverTime::UpdateExercise1()
	{
		m_ShaderProgram.Use();

		m_ShaderProgram.SetUniform1i("texture1", 0);
		m_ShaderProgram.SetUniform1i("texture2", 1);

		// First translate the container to the bottom-right corner and then rotate around the origin.
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		m_ShaderProgram.SetUniformMatrix4fv("transform", glm::value_ptr(trans));
	}

	void RotateOverTime::DrawExercise2()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_Textures[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_Textures[1]);

		m_ShaderProgram.Use();
		m_ShaderProgram.SetUniform1i("texture1", 0);
		m_ShaderProgram.SetUniform1i("texture2", 1);

		glm::mat4 trans1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, -0.5f, 0.0f));
		trans1 = glm::rotate(trans1, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		m_ShaderProgram.SetUniformMatrix4fv("transform", glm::value_ptr(trans1));

		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		glm::mat4 trans2 = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, 0.5f, 0.0f));
		float scaleAmount = sin(glfwGetTime());
		trans2 = glm::scale(trans2, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
		m_ShaderProgram.SetUniformMatrix4fv("transform", &trans2[0][0]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}