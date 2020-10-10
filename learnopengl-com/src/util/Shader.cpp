#include "Shader.h"

#include <fstream>
#include <iostream>
#include <string>


namespace util
{
	void CompileShader(const std::string & source_path, const GLenum & shader_type, unsigned int & shader_id)
	{
		std::ifstream file(source_path);
		std::string shader_source = "";
		for (std::string line; std::getline(file, line);)
		{
			shader_source += line + '\n';
		}
		shader_id = glCreateShader(shader_type);
		const char * c_str = shader_source.c_str();
		glShaderSource(shader_id, 1, &c_str, NULL);
		glCompileShader(shader_id);

		GLint shader_compiled;
		
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &shader_compiled);
		if (shader_compiled != GL_TRUE)
		{
			GLsizei log_length = 0;
			GLchar info_log[1024];
			glGetShaderInfoLog(shader_id, 1024, &log_length, info_log);
			std::cout << "ERROR::SHADER::" << source_path << "::COMPILATION_FAILED\n" << info_log << '\n';
		}
	}
}