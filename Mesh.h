#pragma once
#include "glm/glm.hpp"
#include"GL/glew.h"
#include<string>
#include <vector>
using namespace std;
class Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2 texCoord) {
		this->pos = pos;
		this->texCoord = texCoord;
	}
	inline glm::vec3* GetPos() { return &pos; };
	inline glm::vec2* GetTexCoord() { return &texCoord; };

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
};
class Mesh
{
public:
	Mesh(vector<Vertex> vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	Mesh(const std::string& fileName);
	~Mesh();
	void 	Update(vector<Vertex> vertices);
	void DrawBG();
	void Draw();
private:
	enum {
		POSITION_BG_VB,
		POSITION_VB,
		TEXCOORD_VB,
		INDEX_VB,
		NORMALVB,
		NUM_BUFFERS
	};
	GLuint m_vertexArrayObject[2];
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;
};

