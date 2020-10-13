#pragma once
class ColorAttribute
{
public:
	ColorAttribute();
	~ColorAttribute();
	void Draw();

private:
	const float m_Triangle[18] = {
		// position			// Color
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_ShaderProgram;
};

