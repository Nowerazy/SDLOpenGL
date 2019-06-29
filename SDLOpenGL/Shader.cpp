#include"Shader.h"
#include <fstream>
#include <iostream>

static GLuint Createshader(const std::string& text, GLenum shaderType);
static void CheckShaderError(GLuint shader, GLuint flag, bool isprogram, const std::string& errorMessage);
static std::string LoadShader(const std::string& fileName);

Shader::Shader(const std::string& fileName)
{
	m_program = glCreateProgram();
	m_shaders[0] = Createshader(LoadShader(fileName +".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = Createshader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(m_program, m_shaders[i]);
	}
	glBindAttribLocation(m_program,0,"position");

	glBindAttribLocation(m_program, 1, "texCoord");

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error:Link program failed");
	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error:Validate program failed");
}
void Shader::Bind() {
	glUseProgram(m_program);
}
Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	glDeleteProgram(m_program);
}

static void CheckShaderError(GLuint shader, GLuint flag, bool isprogram, const std::string& errorMessage) {
	GLint success = 0;
	GLchar error[1024] = { 0 };
	if (isprogram) {
		glGetProgramiv(shader, flag, &success);
	}
	else
	{
		glGetShaderiv(shader, flag, &success);
	}
	if (success == GL_FALSE)
	{
		if (isprogram)
		{
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else
		{
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}
		std::cerr << errorMessage << " : " << error << "," << std::endl;
	}
}
static std::string LoadShader(const std::string& fileName) {

	std::ifstream file;
	file.open((fileName).c_str());
	std::string output, line;
	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader:" << fileName << std::endl;
	}
	return output;
}

GLuint static Createshader(const std::string& text, GLenum shaderType) {
	GLuint shader = glCreateShader(shaderType);
	if (shader == 0)
	{
		std::cerr << " Error: Shader creation failure " << std::endl;
	}
	const GLchar* shaderSouceString[1];
	GLint shaderSourceStringLength[1];
	shaderSouceString[0] = text.c_str();
	shaderSourceStringLength[0] = text.length();
	glShaderSource(shader, 1, shaderSouceString, shaderSourceStringLength);
	glCompileShader(shader);
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error:Shader compilation failed");
	return shader;
}