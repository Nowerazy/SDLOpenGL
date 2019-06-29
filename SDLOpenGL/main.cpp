#include <iostream>
#include "GL/glew.h"
#include "Display.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

int main(int argc, char** argv) {
	//std::cout << "SDLOpenGL" << std::endl;
	Display display(800,600, "Opengl");
	//Vertex vertices[] = {
	//Vertex(glm::vec3(-0.5,-0.5,0),glm::vec2(0,1.0)),
	//Vertex(glm::vec3(0,0.5,0),glm::vec2(0.5,0)),
	//Vertex(glm::vec3(0.5,-0.5,0),glm::vec2(1.0,1.0)),
	//};
	Vertex vertices[] = {
	Vertex(glm::vec3(-1.0,1.0,0),glm::vec2(0,0)),
	Vertex(glm::vec3(-1.0,-1.0,0),glm::vec2(0,1.0)),
	Vertex(glm::vec3(1.0,1.0,0),glm::vec2(1.0,0)),
	Vertex(glm::vec3(1.0,-1.0,0),glm::vec2(1.0,1.0))
	};
	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
	Shader shader("./res/basicShader");
	Texture texture("./res/2.jpg");
	while (!display.Isclosed())
	{
		glClearColor(0.0f, 0.3f, 0.24f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader.Bind();
		mesh.Draw();
		display.Update();
	}
	return 0;
}