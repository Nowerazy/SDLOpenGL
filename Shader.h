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
	void Bind(int glnumb);
	void Update(const Transform transform, const Camera camera);
	int AddShader(const std::string& filevs, const std::string& filefs);
	int getProgramId(int index);
private:
	int m_programNUM = 0;
	enum
	{
		SHADERS1,
		SHADERS2,
		NUM_SHADERS,
	};
	enum
	{
		TRANSFORM_U,
		TIME,
		NUM_UNIFORM,
	};
	GLuint m_program[NUM_SHADERS];
	GLuint m_shaders[NUM_SHADERS][2];
	GLuint m_uniform[NUM_SHADERS][NUM_UNIFORM];
};

