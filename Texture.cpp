#include "Texture.h"
#include <iostream>
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
Texture::Texture(int programID[], const std::string fileName[], int texturNUm)
{
	int width, height, numComponnents;
	glGenTextures(NUM_TEXTURE, &m_texture[0]);
	for (int i = 0; i < texturNUm; i++)
	{
		std::cout << "create Texture:{" << fileName[i].c_str() << "}" << std::endl;
		unsigned char* data = stbi_load(fileName[i].c_str(), &width, &height, &numComponnents, 4);

		if (data == 0)
		{
			std::cerr << "Error: loading pic failed" << std::endl;
		}
		//glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_texture[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}
	//glUniform1i(glGetUniformLocation(programID[0], "diffuse"), 0);
	//glUniform1i(glGetUniformLocation(programID[1], "bg"), 1);

}
void Texture::Bind(int texnum) {
	//glActiveTexture(GL_TEXTURE0 + texnum);
	glBindTexture(GL_TEXTURE_2D, m_texture[texnum]);
}
Texture::~Texture()
{
	glDeleteTextures(NUM_TEXTURE, &m_texture[0]);
}