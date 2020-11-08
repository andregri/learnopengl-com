#include "LightingMap.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image/stb_image.h>

#include <iostream>


namespace getting_started
{

	LightingMap::LightingMap()
		: m_ObjectShader("res/shader/GS-Lighting/lm_vertex.shader", "res/shader/GS-Lighting/lm_obj_fragment.shader"),
		m_LightShader("res/shader/GS-Lighting/lm_vertex.shader", "res/shader/GS-Lighting/lm_light_fragment.shader")
	{
		glGenVertexArrays(1, &m_ObjVAO);
		glGenVertexArrays(1, &m_LightVAO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_ObjVAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_Cube), m_Cube, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glBindVertexArray(m_LightVAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		const char * diffusePath = "res/textures/container2.png";
		int width, height, num_channels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char * data = stbi_load(diffusePath, &width, &height, &num_channels, 0);
		if (data)
		{
			glGenTextures(1, &m_DiffuseMap);
			glBindTexture(GL_TEXTURE_2D, m_DiffuseMap);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "ERROR::IMAGE::" << diffusePath << "::FAILED_LOADING\n";
		}
		stbi_image_free(data);

		const char * specularPath = "res/textures/container2_specular.png";
		data = stbi_load(diffusePath, &width, &height, &num_channels, 0);
		if (data)
		{
			glGenTextures(1, &m_SpecularMap);
			glBindTexture(GL_TEXTURE_2D, m_SpecularMap);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "ERROR::IMAGE::" << specularPath << "::FAILED_LOADING\n";
		}
		stbi_image_free(data);
	}


	LightingMap::~LightingMap()
	{
		glDeleteVertexArrays(1, &m_ObjVAO);
		glDeleteVertexArrays(1, &m_LightVAO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteTextures(1, &m_DiffuseMap);
	}

	void LightingMap::Draw(core::Camera camera)
	{
		glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);

		m_ObjectShader.Use();

		glm::mat4 objModel = glm::mat4(1.0f);
		m_ObjectShader.SetUniformMatrix4fv("model", glm::value_ptr(objModel));
		m_ObjectShader.SetUniformMatrix4fv("view", glm::value_ptr(view));
		m_ObjectShader.SetUniformMatrix4fv("projection", glm::value_ptr(projection));

		m_ObjectShader.SetUniformVec3f("viewPos", camera.Position.x, camera.Position.y, camera.Position.z);

		m_ObjectShader.SetUniform1i("material.diffuse", 0);  // set diffuse map
		m_ObjectShader.SetUniform1i("material.specular", 1);
		m_ObjectShader.SetUniform1f("material.shininess", 64.0f);

		m_ObjectShader.SetUniformVec3f("light.position", lightPos.x, lightPos.y, lightPos.z);
		m_ObjectShader.SetUniformVec3f("light.ambient", 0.2f, 0.2f, 0.2f); // note that all light colors are set at full intensity
		m_ObjectShader.SetUniformVec3f("light.diffuse", 0.5f, 0.5f, 0.5f);
		m_ObjectShader.SetUniformVec3f("light.specular", 1.0f, 1.0f, 1.0f);

		// bind diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_DiffuseMap);
		
		// bind specular map
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_SpecularMap);

		// render the cube
		glBindVertexArray(m_ObjVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		m_LightShader.Use();
		glm::mat4 lightModel = glm::mat4(1.0f);
		lightModel = glm::translate(lightModel, lightPos);
		lightModel = glm::scale(lightModel, glm::vec3(0.2f));
		m_LightShader.SetUniformMatrix4fv("model", glm::value_ptr(lightModel));
		m_LightShader.SetUniformMatrix4fv("view", glm::value_ptr(view));
		m_LightShader.SetUniformMatrix4fv("projection", glm::value_ptr(projection));

		glBindVertexArray(m_LightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

}