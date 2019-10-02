#pragma once
#include <string>
#include "GL/glew.h"
#include "Shader.h"
class Texture
{
public:
	Texture(int programID[], const std::string fileName[], int texturNUm);
	void Bind(int texnum);
	~Texture();

private:
	enum
	{
		TEXTURE1,
		TEXTURE2,
		NUM_TEXTURE,
	};
	GLuint m_texture[NUM_TEXTURE];
};

