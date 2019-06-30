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
	while (!display.Isclosed())
	{
		display.Clear(0.0f, 0.2f, 0.2f, 1.0f);
		float sinCount = sinf(count);
		float cosCount = cosf(count);
		transform.GetPos()->x = sinCount;
		//transform.GetPos()->z = cosCount;
		transform.GetRot()->x = sinCount * 1;
		transform.GetRot()->y = cosCount * 4;
		shader.Bind();
		texture.Bind();
		shader.Update(transform, camera);
		mesh2.Draw();
		display.Update();
		count += 0.001f;
	}
	return 0;
}