#include "LightCaster_PointLight.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image/stb_image.h>

#include <iostream>


namespace getting_started
{

	LightCaster_PointLight::LightCaster_PointLight()
		: m_ObjectShader("res/shader/GS-Lighting/lm_vertex.shader", "res/shader/GS-Lighting/lc_pl_obj_fragment.shader"),
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

		const char * path = "res/textures/container2.png";
		int width, height, num_channels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char * data = stbi_load(path, &width, &height, &num_channels, 0);
		if (data)
		{
			glGenTextures(1, &m_DiffuseMap);
			glBindTexture(GL_TEXTURE_2D, m_DiffuseMap);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else
		{
			std::cout << "ERROR::IMAGE::" << path << "::FAILED_LOADING\n";
		}
		stbi_image_free(data);

		path = "res/textures/container2_specular.png";
		//path = "res/textures/lighting_maps_specular_color.png"; // Exercise3
		data = stbi_load(path, &width, &height, &num_channels, 0);
		if (data)
		{
			glGenTextures(1, &m_SpecularMap);
			glBindTexture(GL_TEXTURE_2D, m_SpecularMap);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		}
		else
		{
			std::cout << "ERROR::IMAGE::" << path << "::FAILED_LOADING\n";
		}
		stbi_image_free(data);
	}


	LightCaster_PointLight::~LightCaster_PointLight()
	{
		glDeleteVertexArrays(1, &m_ObjVAO);
		glDeleteVertexArrays(1, &m_LightVAO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteTextures(1, &m_DiffuseMap);
		glDeleteTextures(1, &m_SpecularMap);
		glDeleteTextures(1, &m_EmissionMap);
	}

	void LightCaster_PointLight::Draw(core::Camera camera)
	{
		glm::vec3 lightPos = glm::vec3(-0.5f, 0.5f, 2.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);

		m_ObjectShader.Use();

		glm::mat4 objModel = glm::mat4(1.0f);
		m_ObjectShader.SetUniformMatrix4fv("model", glm::value_ptr(objModel));
		m_ObjectShader.SetUniformMatrix4fv("view", glm::value_ptr(view));
		m_ObjectShader.SetUniformMatrix4fv("projection", glm::value_ptr(projection));

		m_ObjectShader.SetUniformVec3f("viewPos", camera.Position.x, camera.Position.y, camera.Position.z);

		m_ObjectShader.SetUniform1i("material.diffuse", 0);  // set diffuse map
		m_ObjectShader.SetUniform1i("material.specular", 1); // set specular map
		m_ObjectShader.SetUniform1f("material.shininess", 32.0f);

		m_ObjectShader.SetUniformVec3f("light.position", lightPos.x, lightPos.y, lightPos.z);
		m_ObjectShader.SetUniformVec3f("light.ambient", 0.2f, 0.2f, 0.2f); // note that all light colors are set at full intensity
		m_ObjectShader.SetUniformVec3f("light.diffuse", 0.5f, 0.5f, 0.5f);
		m_ObjectShader.SetUniformVec3f("light.specular", 1.0f, 1.0f, 1.0f);
		m_ObjectShader.SetUniform1f("light.constant", 1.0f);
		m_ObjectShader.SetUniform1f("light.linear_", 0.09f);
		m_ObjectShader.SetUniform1f("light.quadratic", 0.032f);

		// bind diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_DiffuseMap);

		// bind specular map
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_SpecularMap);

		// render the cubes
		glm::vec3 cubePositions[] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		glBindVertexArray(m_ObjVAO);

		for (unsigned int i = 0; i < 10; ++i) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			m_ObjectShader.SetUniformMatrix4fv("model", glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// render the light source

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