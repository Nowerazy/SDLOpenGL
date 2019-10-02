#pragma once
#include "glm/glm.hpp"
#include"GL/glew.h"
#include<string>
#include <vector>
using namespace std;
struct PosTexc {
	glm::vec3* pos;
	glm::vec2* tec;
};
class Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2 texCoord) {
		this->pos = pos;
		this->texCoord = texCoord;
	}
	inline glm::vec3* GetPos() { return &pos; };
	inline glm::vec2* GetTexCoord() { return &texCoord; };
	PosTexc GetPosTexc(){
		PosTexc te;
		te.pos = &pos;
		te.tec = &texCoord;
		return te;
	};
private:
	glm::vec3 pos;
	glm::vec2 texCoord;
};
class Mesh
{
public:
	Mesh();
	Mesh(const std::string& fileName);
	~Mesh();
	void FillBGVertex();
	void FillVertex(vector<Vertex> vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	void 	Update(vector<Vertex> vertices);
	void DrawBG();
	void Draw();
private:
	enum {
		POSITION_VB,
		INDEX_VB,
		NORMALVB,
		TEXCOORD_VB,
		BG_VB,
		NUM_BUFFERS
	};
	GLuint m_vertexArrayObject[2];
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;
};

