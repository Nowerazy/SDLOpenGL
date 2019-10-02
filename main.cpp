#include <iostream>
#include "GL/glew.h"
#include "Display.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"
#include "rain.h"

#define WIDTH 900
#define HEIGHT 600

#define RAINNUM 1000
int main(int argc, char** argv) {
	//std::cout << "SDLOpenGL" << std::endl;
	Display display(WIDTH, HEIGHT, "Opengl");
	Rain rainpools[RAINNUM];
	vector<Vertex> rainVertexpools;
	vector<Vertex> te;
	int createdProgramNum = 0;
	rainVertexpools.clear();
	int program[2];
	for (int i = 0; i < RAINNUM; i++)
	{
		rainpools[i].UpdateSpeed(0.01f, 0.02f, 0.1f);
		te = rainpools[i].genVertex();
		rainVertexpools.insert(rainVertexpools.end(), te.begin(), te.end());
		//std::cout << "{" << rainpools[i].tostring() << "}" << std::endl;
	}
	/*Vertex vertices[] = {
		Vertex(glm::vec3(-1.0,1.0,0),glm::vec2(1.0,0)),
		Vertex(glm::vec3(-1.0,-1.0,0),glm::vec2(1.0,1.0)),
		Vertex(glm::vec3(1.0,1.0,0),glm::vec2(0,0)),
		Vertex(glm::vec3(1.0,-1.0,0),glm::vec2(0,1.0)),

		Vertex(glm::vec3(-1.0,-0.2,0),glm::vec2(1.0,0.6)),
		Vertex(glm::vec3(1.0,-0.2,0),glm::vec2(0,0.6)),
		Vertex(glm::vec3(-1.0,0.2,0),glm::vec2(1.0,0.4)),
		Vertex(glm::vec3(1.0,0.2,0),glm::vec2(0,0.4)),
	};
	unsigned int indices0[] = { 0,1,2,2,1,3 };
	unsigned int indices[] = { 6,1,7,1,7,3 };
	unsigned int indices2[] = { 0,4,2,4,2,5 };*/
	int re = rainVertexpools.size();
	Shader shader;
	string atrribConfig[] = { "position", "texCoord" };
	string uniformConfig[] = { "transform" };
	program[0] = shader.CreateProgram("basicShader", "basicShader", atrribConfig, sizeof(atrribConfig) / sizeof(atrribConfig[0]),
		uniformConfig, sizeof(uniformConfig) / sizeof(uniformConfig[0]), &createdProgramNum);

	/*Mesh mesh(rainVertexpools, rainVertexpools.size(),
		indices0, sizeof(indices0) / sizeof(indices0[0]));
*/
	Mesh mesh;
	mesh.FillVertex(rainVertexpools, rainVertexpools.size(),
		nullptr, rainVertexpools.size());
	string texfiles[] = { "./res/snow.png", "./res/1.jpg" };// "./res/raindown.png" , "./res/1.jpg","./res/snow.png" 
	int  texLength = sizeof(texfiles) / sizeof(texfiles[0]);
	Texture texture(program, texfiles, texLength);

	Transform transform;
	//Camera camera(glm::vec3(0, 0, -15), 70.0f, (float)HEIGHT / (float)WIDTH, 0.01f, 1000.0f);
	Camera camera(glm::vec3(0.0f, 0.f, -3.5f), glm::radians(30.0f), (float)HEIGHT / (float)WIDTH, 0.1f, 10.0f);
	program[1] = shader.CreateBgProgram("bgShader", "bgShader", atrribConfig, 1,
		uniformConfig, 0, &createdProgramNum);
	mesh.FillBGVertex();
	float count = 0.0f;
	float  accz = 0;
	int accZ = 0;
	while (!display.Isclosed())
	{
		display.Clear(0.0f, 0.2f, 0.2f, 1.0f);

		//glEnable(GL_DEPTH_TEST);
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		/*glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
		glBlendEquation(GL_FUNC_ADD);*/
		float sinCount = sinf(count);
		float cosCount = cosf(count);
		transform.GetPos()->x = sinCount;
		transform.GetRot()->x = sinCount * 1;
		transform.GetRot()->y = cosCount * 4;
		transform.GetRot()->y = (float)display.accumuMoveSize[0] / 360;
		transform.GetRot()->x = -(float)display.accumuMoveSize[1] / 360;
		if (accZ != -display.accumuMoveSize[2]) {

			accZ = -display.accumuMoveSize[2];
			accz = (float)accZ / 30.0f;
		}
		else
		{
			if (accz<0.0001f && accz>-0.0001f)
			{
				accz = 0;
			}
			else
			{
				accz *= 0.98f;
			}
		}
		transform.GetPos()->x = -(float)display.accumuMoveSize[3] / 150;
		transform.GetPos()->y = -(float)display.accumuMoveSize[4] / 150;
		transform.GetPos()->z += accz;

		//for (int i = texLength-1; i >=0; i--)
		for (int i = 0; i < texLength; i++)
		{
			texture.Bind(i);
			shader.Bind(program[i]);
			if (i == 1)
			{
				mesh.DrawBG();
			}
			else {
				rainVertexpools.clear();
				for (int i = 0; i < RAINNUM; i++)
				{
					rainpools[i].Update();
					//std::cout << "{" << rainpools[i].tostring() << "}" << std::endl;
					te = rainpools[i].genVertex();
					rainVertexpools.insert(rainVertexpools.end(), te.begin(), te.end());
				}
				mesh.Update(rainVertexpools);
				//std::cout << "{" << transform.GetPos()->x <<" "<< transform.GetPos()->y << " " << transform.GetPos()->z << "}" << std::endl;
				shader.Update(program[i],transform, camera);
				mesh.Draw();
			}
		}
		display.Update();
		count += 0.001f;
	}
	return 0;
}