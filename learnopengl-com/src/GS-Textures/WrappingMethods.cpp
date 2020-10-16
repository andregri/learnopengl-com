#include "WrappingMethods.h"

#include <GL/glew.h>
#include "../vendor/stb_image/stb_image.h"

#include <iostream>
#include <string>

namespace getting_started
{

	WrappingMethods::WrappingMethods(const std::string & fragment_path)
		: m_ShaderProgram("res/shader/GS-Textures/first_texture_vertex.shader", fragment_path)
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
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(unsigned int), (void*)(6 * sizeof(float)));
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
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				GLenum format = GL_RGB;
				if (paths[i].find(".png") != std::string::npos)
				{
					format = GL_RGBA;
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				}
					
				glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else
			{
				std::cout << "ERROR::IMAGE::" << paths[0] << "::LOADING_FAILED\n";
			}
			stbi_image_free(data);
		}

		m_ShaderProgram.Use();
		m_ShaderProgram.SetUniform1i("texture1", 0);
		m_ShaderProgram.SetUniform1i("texture2", 1);
	}


	WrappingMethods::~WrappingMethods()
	{
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_EBO);
		glDeleteTextures(2, m_Textures);
		glDeleteVertexArrays(1, &m_VAO);
	}

	void WrappingMethods::Draw()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_Textures[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_Textures[1]);
		m_ShaderProgram.Use();
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}