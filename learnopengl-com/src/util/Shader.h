#pragma once

#include <GL/glew.h>

#include <string>


namespace util
{
	void CompileShader(const std::string & source_path, const GLenum & shader_type, unsigned int & shader_id);
}