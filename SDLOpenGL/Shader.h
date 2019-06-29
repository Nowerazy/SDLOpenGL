#pragma once
#include"GL/glew.h"
#include <string>
class Shader
{
public:
	Shader(const std::string& fileName);
	~Shader();
	void Bind();

private:
	static const unsigned int NUM_SHADERS = 2;
	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
};

