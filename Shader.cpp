#include"Shader.h"
#include<time.h>
#include <fstream>
#include <iostream>

static GLuint Createshader(const std::string& text, GLenum shaderType);
static void CheckShaderError(GLuint shader, GLuint flag, bool isprogram, const std::string& errorMessage);
static std::string LoadShader(const std::string& fileName);

Shader::Shader()
{
	m_programNUM = 0;
}

int Shader::CreateProgram(const std::string& fileNamevs, const std::string& fileNamefs,
	const string atrribConfig[], int configLength,
	const string uniformConfig[], int uniformLength, int* currentProgramNum)
{
	m_programNUM += 1;
	*currentProgramNum = m_programNUM;
	int newProgramID = glCreateProgram();
	std::cout << "Create newProgramID:" << newProgramID << std::endl;
	m_shaders[0] = Createshader(LoadShader("./res/" + fileNamevs + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = Createshader(LoadShader("./res/" + fileNamefs + ".fs"), GL_FRAGMENT_SHADER);
	for (unsigned int i = 0; i < 2; i++)
	{
		glAttachShader(newProgramID, m_shaders[i]);
	}
	for (int i = 0; i < configLength; i++)
	{
		glBindAttribLocation(newProgramID, i, atrribConfig[i].c_str());
	}
	glLinkProgram(newProgramID);
	CheckShaderError(newProgramID, GL_LINK_STATUS, true, "Error:Link program failed");
	glValidateProgram(newProgramID);
	CheckShaderError(newProgramID, GL_VALIDATE_STATUS, true, "Error:Validate program failed");

	Bind(newProgramID);
	for (int i = 0; i < uniformLength; i++)
	{
		m_uniform[TRANSFORM_U] = glGetUniformLocation(newProgramID, uniformConfig[i].c_str());
		m_uniform[TIME] = glGetUniformLocation(newProgramID, uniformConfig[i].c_str());

		std::cout << "{TRANSFORM_U:" << m_uniform[TRANSFORM_U] << "- TIME: " << m_uniform[TIME] << "}" << std::endl;
	}
	return newProgramID;
}
int Shader::CreateBgProgram(const std::string& fileNamevs, const std::string& fileNamefs,
	const string atrribConfig[], int configLength,
	const string uniformConfig[], int uniformLength, int* currentProgramNum)
{
	m_programNUM += 1;
	*currentProgramNum = m_programNUM;
	int newProgramID = glCreateProgram();
	std::cout << "Create newProgramID:" << newProgramID << std::endl;
	m_shaders[0] = Createshader(LoadShader("./res/" + fileNamevs + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = Createshader(LoadShader("./res/" + fileNamefs + ".fs"), GL_FRAGMENT_SHADER);
	for (unsigned int i = 0; i < 2; i++)
	{
		glAttachShader(newProgramID, m_shaders[i]);
	}
	glBindAttribLocation(newProgramID, 2, "position");

	glLinkProgram(newProgramID);
	CheckShaderError(newProgramID, GL_LINK_STATUS, true, "Error:Link program failed");
	glValidateProgram(newProgramID);
	CheckShaderError(newProgramID, GL_VALIDATE_STATUS, true, "Error:Validate program failed");
	Bind(newProgramID);
	return newProgramID;
}
void Shader::Bind(int glnumb) {
	glUseProgram(glnumb);
}
int Shader::getProgramId(int index)
{
	return 0;
}
void Shader::Update(int proID, const Transform transform, const Camera camera) {
	glm::mat4 mod = camera.GetViewProjection() * transform.GetModel();
	GLfloat time = (GLfloat)clock() / 1000;
	m_uniform[TRANSFORM_U] = glGetUniformLocation(proID, "transform");
	//std::cout << "{TRANSFORM_U:" << m_uniform[TRANSFORM_U] << "- TIME: " << m_uniform[TIME] << "}" << std::endl;
	glUniformMatrix4fv(m_uniform[TRANSFORM_U], 1, GL_FALSE, &mod[0][0]);//1:计数,这里是1

	//glUniform1f(m_uniform[TIME], time);
}
void  Shader::CleanProgramShader(int program) {
	for (unsigned int i = 0; i < 2; i++)
	{
		glDetachShader(program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
}
void  Shader::DeletProgram(int program) {
	glDeleteProgram(program);
}
Shader::~Shader()
{
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