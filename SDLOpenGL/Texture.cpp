#include "Texture.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
Texture::Texture(const std::string& fileName)
{
	int width, height, numComponnents;
	unsigned char* data = stbi_load((fileName).c_str(), &width, &height, &numComponnents, 4);

	if (data == 0)
	{
		std::cerr << "Error: loading pic failed" << std::endl;
	}
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);
}
void Texture::Bind() {
	glBindTexture(GL_TEXTURE_2D, m_texture);
}
Texture::~Texture()
{
	glDeleteTextures(1,&m_texture);
}