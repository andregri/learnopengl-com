#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "HelloTriangle/Hello.h"
#include "HelloTriangle/HelloTriangle.h"
#include "HelloTriangle/HelloRectangle.h"
#include "HelloTriangle/Exercise1.h"
#include "HelloTriangle/Exercise2.h"
#include "HelloTriangle/Exercise3.h"
#include "GS-Shaders/Uniforms.h"
#include "GS-Shaders/ColorAttribute.h"
#include "GS-Shaders/Exercise1.h"
#include "GS-Shaders/Exercise2.h"
#include "GS-Shaders/Exercise3.h"
#include "GS-Textures/FirstTexture.h"
#include "GS-Textures/MixTextures.h"
#include "GS-Textures/WrappingMethods.h"
#include "GS-Textures/Exercise3.h"
#include "GS-Textures/MixUniform.h"
#include "GS-Transformations/RotateScale.h"

#define global_variable static
global_variable float mix_value;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window, Hello * hellos[])
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	/*if (glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);*/

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		hellos[0]->Draw(); // Hello Triangle

	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		hellos[1]->Draw(); // Hello Rectangle

	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		hellos[2]->Draw(); // Exercise 1

	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		hellos[3]->Draw(); // Exercise 2

	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
		hellos[4]->Draw(); // Exercise 3

	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
	{
		Uniforms uniforms;
		uniforms.Draw();
	}

	if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
	{
		ColorAttribute color_attrib;
		color_attrib.Draw();
	}

	if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
	{
		getting_started::Exercise1 upside_down;
		upside_down.Draw();
	}

	if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
	{
		getting_started::Exercise2 horizontal_oscillation;
		horizontal_oscillation.Draw();
	}

	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
	{
		getting_started::Exercise3 color_as_vertex_position;
		color_as_vertex_position.Draw();
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		getting_started::FirstTexture wooden_container;
		wooden_container.Draw();
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		getting_started::MixTextures mix_textures("res/shader/GS-Textures/mix_textures_fragment.shader");
		mix_textures.Draw();
	}

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		getting_started::MixTextures mix_textures("res/shader/GS-Textures/mix_textures_flip_horizontally_fragment.shader");
		mix_textures.Draw();
	}

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		getting_started::WrappingMethods wrapping_methods("res/shader/GS-Textures/mix_textures_fragment.shader");
		wrapping_methods.Draw();
	}

	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
	{
		getting_started_texture::Exercise3 exercise3("res/shader/GS-Textures/mix_textures_fragment.shader");
		exercise3.Draw();
	}

	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
	{
		getting_started::MixUniform mix_uniform("res/shader/GS-Textures/mix_uniform_fragment.shader");
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			mix_value -= 0.05f;
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			mix_value += 0.05f;
		printf("mix value: %f\n", mix_uniform.UpdatetMix(mix_value));
		mix_uniform.Draw();
	}
	
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
	{
		getting_started::RotateScale rotate_and_scale;
		rotate_and_scale.Draw();
	}
}


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(800, 600, "LearnOpenGL.com", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
	fprintf(stdout, "Status: Using GL %s\n", glGetString(GL_VERSION));

	glViewport(0, 0, 800, 600);

	HelloTriangle hello_triangle;
	HelloRectangle hello_rectangle;
	hello_triangle::Exercise1 exercise1;
	hello_triangle::Exercise2 exercise2;
	hello_triangle::Exercise3 exercise3;

	Hello * hellos[] = {&hello_triangle, &hello_rectangle, &exercise1, &exercise2, &exercise3};

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		processInput(window, hellos);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}