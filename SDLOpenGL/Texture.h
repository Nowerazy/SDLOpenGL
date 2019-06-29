#pragma once
#include <string>
#include "GL/glew.h"
class Texture
{
public:
	Texture(const std::string&fileName);
	void Bind();
	~Texture();

private:
	GLuint m_texture;
};

