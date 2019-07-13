#include <iostream>
#include "GL/glew.h"
#include "Display.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char** argv) {
	//std::cout << "SDLOpenGL" << std::endl;
	Display display(WIDTH, HEIGHT, "Opengl");
	/*Vertex vertices[] = {
	Vertex(glm::vec3(-0.5,-0.5,0),glm::vec2(0,1.0)),
	Vertex(glm::vec3(0,0.5,0),glm::vec2(0.5,0)),
	Vertex(glm::vec3(0.5,-0.5,0),glm::vec2(1.0,1.0)),
	};*/
	Vertex vertices[] = {
		Vertex(glm::vec3(-1.0,1.0,0),glm::vec2(0,0)),
		Vertex(glm::vec3(-1.0,-1.0,0),glm::vec2(0,1.0)),
		Vertex(glm::vec3(1.0,1.0,0),glm::vec2(1.0,0)),
		Vertex(glm::vec3(1.0,-1.0,0),glm::vec2(1.0,1.0))
	};
	unsigned int indices[] = { 0,1,2,3 };
	/*Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]),
		indices, sizeof(indices) / sizeof(indices[0]));*/
	Mesh mesh2("./res/catmark_torus_creases0.obj");
	Shader shader("./res/basicShader");
	Texture texture("./res/1.jpg");
	Transform transform;
	Camera camera(glm::vec3(0, 0, -15), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);

	float count = 0.0f;
	float  accz = 0;
	int accZ = 0;
	while (!display.Isclosed())
	{
		display.Clear(0.0f, 0.2f, 0.2f, 1.0f);
		//float sinCount = sinf(count);
		//float cosCount = cosf(count);
		//transform.GetPos()->x = sinCount;
		//transform.GetRot()->x = sinCount * 1;
		//transform.GetRot()->y = cosCount * 4;
		transform.GetRot()->y = (float)display.accumuMoveSize[0] / 360;
		transform.GetRot()->x = -(float)display.accumuMoveSize[1] / 360;
		if (accZ != -(float)display.accumuMoveSize[2]) {

			accZ = -(float)display.accumuMoveSize[2];
			accz = (float)accZ / 30;
		}
		else
		{
			if (accz<0.0001f && accz>-0.0001f)
			{
				accz = 0;
			}
			else
			{
				accz *= 0.98;
			}
		}
		transform.GetPos()->x = -(float)display.accumuMoveSize[3] / 150;
		transform.GetPos()->y = -(float)display.accumuMoveSize[4] / 150;
		transform.GetPos()->z += accz;



		shader.Bind();
		texture.Bind();
		shader.Update(transform, camera);
		mesh2.Draw();
		display.Update();
		count += 0.001f;
	}
	return 0;
}