#pragma once
class Uniforms
{
public:
	Uniforms();
	~Uniforms();

	void Draw();

private:
	float m_Triangle[9] = {
		0.0f,  0.5f, 0.0f,
		0.0f, -0.5f, 0.0f,
		0.7f,  0.0f, 0.0f
	};

	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_ShaderProgram;
	unsigned int m_ColorUniformLocation;
};

