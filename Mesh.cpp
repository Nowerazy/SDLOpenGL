#include"Mesh.h"
#include <iostream>
#define TINYOBJLOADER_IMPLEMENTATION 
#include"tinyObjLoader.h"

Mesh::Mesh(vector<Vertex> vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	std::cout << "{" << numVertices << "}" << std::endl;
	m_drawCount = numIndices;
	glGenVertexArrays(2, &m_vertexArrayObject[0]);
	//分配顶点数组对象
	glBindVertexArray(m_vertexArrayObject[0]);
	//绑定数组对象,相当于声明之后的操作,都是对数组对象的操作


	std::vector<glm::vec3> positios;
	std::vector<glm::vec2> texCoord;
	positios.reserve(numVertices);
	texCoord.reserve(numVertices);
	for (unsigned int i = 0; i < numVertices; i++)
	{
		positios.push_back(*vertices[i].GetPos());
		texCoord.push_back(*vertices[i].GetTexCoord());
	}
	/*分配顶点缓存对象
		数组对象将被保存在缓存对象中
	*/
	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	/*将顶点数据保存在缓存对象中
		完成2个任务:
			1.分配顶点数据所需的存储空间
			2.将数据从运存中的数组copy到opengl服务端的内存中
			  GL_STATIC_DRAW:对分配数据的读取和写入的方式,因为这里只是绘制点,
			  运行时不会对它进行修改,顾设置为静态.
	*/
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positios[0]), &positios[0], GL_DYNAMIC_DRAW);

	//启用和着色器中属性位置索引相关联的顶点数组
	glEnableVertexAttribArray(0);//0:着色器中属性位置索引
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	/*关联一个顶点属性数组
		参数1:对应着色器中属性位置
		参数2 : 每个顶点需要更新的分量数目 xyz所以是3
		参数3 : 没个分量的数据类型
		参数4 : 设置顶点数据在输入前是否需要归一化
		参数5 : 数组中每两个元素之间的大小偏移值
		参数6 : 缓存对象起始位置在数组中的偏移值
	*/


	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	/*将顶点数据保存在缓存对象中
		完成2个任务:
			1.分配顶点数据所需的存储空间
			2.将数据从运存中的数组copy到opengl服务端的内存中
			  GL_STATIC_DRAW:对分配数据的读取和写入的方式,因为这里只是绘制点,
			  运行时不会对它进行修改,顾设置为静态.
	*/
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoord[0]), &texCoord[0], GL_DYNAMIC_DRAW);
	//启用和着色器中属性位置索引相关联的顶点数组
	glEnableVertexAttribArray(1);//1:着色器中属性位置索引
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	/*关联一个顶点属性数组
		参数1:对应着色器中属性位置
		参数2 : 每个顶点需要更新的分量数目 xyz所以是3
		参数3 : 每个分量的数据类型
		参数4 : 设置顶点数据在输入前是否需要归一化
		参数5 : 数组中每两个元素之间的大小偏移值
		参数6 : 缓存对象起始位置在数组中的偏移值
	*/
	/*
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(indices[0]), &indices[0], GL_DYNAMIC_DRAW);*/
		/*element may not bind VertexAttribArray,so glEnableVertexAttribArray(1)
			&glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0) will no use.*/

	glBindVertexArray(0);//不再使用任何分配的数组对象
	glBindVertexArray(m_vertexArrayObject[1]);
	vector<glm::vec3> bgVecs;
	bgVecs.push_back(glm::vec3(-1.0, 1.0, 0));
	bgVecs.push_back(glm::vec3(-1.0, -1.0, 0));
	bgVecs.push_back(glm::vec3(1.0, 1.0, 0));
	bgVecs.push_back(glm::vec3(-1.0, -1.0, 0));
	bgVecs.push_back(glm::vec3(1.0, 1.0, 0));
	bgVecs.push_back(glm::vec3(1.0, -1.0, 0));
	glBindBuffer(GL_ARRAY_BUFFER, Mesh::m_vertexArrayBuffers[POSITION_BG_VB]);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(bgVecs[0]), &bgVecs[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);//0:着色器中属性位置索引
}
Mesh::Mesh(const std::string& fileName) {
	m_drawCount = 0;
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn;
	std::string err;
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, fileName.c_str(),
		NULL, true);

	std::vector<float> posVb = attrib.vertices;
	std::vector<float> texcoordVb = attrib.texcoords;
	std::vector<float> normalVb = attrib.normals;

	std::vector<float> texcoordIndex;
	std::vector<float> normalIndex;
	std::vector<int> indices;

	for (unsigned int i = 0; i < shapes.size(); i++)
	{
		m_drawCount += shapes[i].mesh.indices.size();
	}
	indices.reserve(m_drawCount);
	texcoordIndex.reserve(m_drawCount * 2);
	normalIndex.reserve(m_drawCount * 3);
	for (unsigned int j = 0; j < shapes.size(); j++)
		for (unsigned int i = 0; i < shapes[j].mesh.indices.size(); i++)
		{
			indices.push_back(shapes[j].mesh.indices[i].vertex_index);
			int txInd = shapes[j].mesh.indices[i].texcoord_index;
			txInd <<= 1;
			int norIndex = shapes[j].mesh.indices[i].normal_index;
			norIndex *= 3;
			texcoordIndex.push_back(texcoordVb[txInd]);
			texcoordIndex.push_back(texcoordVb[txInd + 1]);
			normalIndex.push_back(normalVb[norIndex]);
			normalIndex.push_back(normalVb[norIndex + 1]);
			normalIndex.push_back(normalVb[norIndex + 2]);
		}
	glGenVertexArrays(1, &m_vertexArrayObject[0]);
	glBindVertexArray(m_vertexArrayObject[0]);
	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, posVb.size() * sizeof(posVb[0]), &posVb[0], GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, texcoordIndex.size() * sizeof(texcoordIndex[0]), &texcoordIndex[0], GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_drawCount * sizeof(indices[0]), &indices[0], GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMALVB]);
	glBufferData(GL_ARRAY_BUFFER, normalIndex.size() * sizeof(normalIndex[0]), &normalIndex[0], GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);

}
Mesh::~Mesh() {
	glDeleteVertexArrays(2, &m_vertexArrayObject[0]);
}
void Mesh::Update(vector<Vertex> vertices) {
	glBindVertexArray(m_vertexArrayObject[0]);
	std::vector<glm::vec3> newpositios;
	newpositios.clear();
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		newpositios.push_back(*vertices[i].GetPos());
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_drawCount * sizeof(newpositios[0]), &newpositios[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
};
void Mesh::DrawBG() {
	glBindVertexArray(m_vertexArrayObject[1]);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
void Mesh::Draw() {
	glBindVertexArray(m_vertexArrayObject[0]);
	glDrawArrays(GL_TRIANGLES, 0, m_drawCount);
	//glDrawElements(GL_TRIANGLE_STRIP, m_drawCount, GL_UNSIGNED_INT, 0);
	//glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
