#pragma once
#include"GL/glew.h"
#include <string>
#include"Transform.h"
#include"Camera.h"
class Shader
{
public:
	Shader();
	Shader(const std::string& fileNamevs, const std::string& fileNamefs);
	~Shader();
	void Bind();
	void Update(const Transform transform, const Camera camera);
	int AddShader(const std::string& filevs, const std::string& filefs);

private:
	static const unsigned int NUM_SHADERS = 2;
	int m_programNUM = 0;
	enum
	{
		TRANSFORM_U,
		TIME,
		NUM_UNIFORM,
	};
	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniform[NUM_UNIFORM];
};

