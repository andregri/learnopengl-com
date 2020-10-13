#include "Shader.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>


namespace util
{
	void CompileShader(const std::string & source_path, const GLenum & shader_type, unsigned int & shader_id)
	{
		std::ifstream shaderFile;
		shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		std::string shaderSource;

		try
		{
			shaderFile.open(source_path);
			std::stringstream shaderStream;
			shaderStream << shaderFile.rdbuf();
			shaderSource = shaderStream.str();
			shaderFile.close();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::" << source_path << "::FILE_NOT_SUCCESSFULLY_READ\n";
		}

		shader_id = glCreateShader(shader_type);
		const char * c_str = shaderSource.c_str();
		glShaderSource(shader_id, 1, &c_str, NULL);
		glCompileShader(shader_id);

		GLint shaderCompiled;

		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &shaderCompiled);
		if (shaderCompiled != GL_TRUE)
		{
			GLsizei logLength = 0;
			GLchar infoLog[1024];
			glGetShaderInfoLog(shader_id, 1024, &logLength, infoLog);
			std::cout << "ERROR::SHADER::" << source_path << "::COMPILATION_FAILED\n" << infoLog << '\n';
		}
	}
}