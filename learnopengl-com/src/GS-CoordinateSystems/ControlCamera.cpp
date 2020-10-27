#include "ControlCamera.h"

#include <GL/glew.h>
#include <stb_image/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>

namespace getting_started
{

	ControlCamera::ControlCamera()
		: m_ShaderProgram("res/shader/GS-Transformations/transformation_vertex.shader", "res/shader/GS-Transformations/transformation_fragment.shader")
	{
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_Cube), m_Cube, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);

		std::string paths[2] = { "res/textures/container.jpg", "res/textures/awesomeface.png" };
		glGenTextures(2, m_Textures);
		for (int i = 0; i < 2; ++i)
		{
			int width, height, nrChannel;
			unsigned char * data;
			stbi_set_flip_vertically_on_load(true);
			data = stbi_load(paths[i].c_str(), &width, &height, &nrChannel, 0);
			if (data)
			{
				glBindTexture(GL_TEXTURE_2D, m_Textures[i]);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				GLenum format = GL_RGB;
				if (paths[i].find(".png") != std::string::npos)
					format = GL_RGBA;
				glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else
			{
				std::cout << "ERROR::IMAGE::" << paths[0] << "::LOADING_FAILED\n";
			}
			stbi_image_free(data);
		}
	}

	ControlCamera::~ControlCamera()
	{
		glDeleteBuffers(1, &m_VBO);
		glDeleteTextures(2, m_Textures);
		glDeleteVertexArrays(1, &m_VAO);
	}


	void ControlCamera::Draw(core::Camera camera)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_Textures[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_Textures[1]);

		m_ShaderProgram.Use();
		m_ShaderProgram.SetUniform1i("texture1", 0);
		m_ShaderProgram.SetUniform1i("texture2", 1);

		glm::mat4 model = glm::mat4(1.0f);

		//glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
		glm::mat4 view = camera.GetViewMatrix();

		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);

		glm::mat4 transform = projection * view * model;
		m_ShaderProgram.SetUniformMatrix4fv("transform", glm::value_ptr(transform));
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

}