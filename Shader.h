#pragma once
#include"GL/glew.h"
#include <string>
#include"Transform.h"
#include"Camera.h"
using namespace std;
class Shader
{
public:
	Shader();
	int CreateProgram(const std::string& fileNamevs, const std::string& fileNamefs, const string atrribConfig[], int configLength, const string uniformConfig[], int uniformLength, int* currentProgramNum);
	int CreateBgProgram(const std::string& fileNamevs, const std::string& fileNamefs, const string atrribConfig[], int configLength, const string uniformConfig[], int uniformLength, int* currentProgramNum);
	~Shader();
	void Bind(int glnumb);
	void CleanProgramShader(int program);
	void DeletProgram(int program);
	int getProgramId(int index);
	void Update(int proID, const Transform transform, const Camera camera);
private:
	int m_programNUM = 0;
	enum
	{
		TRANSFORM_U,
		TIME,
		NUM_UNIFORM,
	};
	GLuint m_shaders[2];
	GLuint m_uniform[NUM_UNIFORM];
};

