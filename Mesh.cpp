#include"Mesh.h"
#include <vector>

#define TINYOBJLOADER_IMPLEMENTATION 
#include"tinyObjLoader.h"

Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	m_drawCount = numIndices;
	glGenVertexArrays(1, &m_vertexArrayObject);
	//���䶥���������
	glBindVertexArray(m_vertexArrayObject);
	//���������,�൱������֮��Ĳ���,���Ƕ��������Ĳ���


	std::vector<glm::vec3> positios;
	std::vector<glm::vec2> texCoord;
	positios.reserve(numVertices);
	texCoord.reserve(numVertices);
	for (unsigned int i = 0; i < numVertices; i++)
	{
		positios.push_back(*vertices[i].GetPos());
		texCoord.push_back(*vertices[i].GetTexCoord());
	}
	/*���䶥�㻺�����
		������󽫱������ڻ��������
	*/
	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	/*���������ݱ����ڻ��������
		���2������:
			1.���䶥����������Ĵ洢�ռ�
			2.�����ݴ��˴��е�����copy��opengl����˵��ڴ���
			  GL_STATIC_DRAW:�Է������ݵĶ�ȡ��д��ķ�ʽ,��Ϊ����ֻ�ǻ��Ƶ�,
			  ����ʱ������������޸�,������Ϊ��̬.
	*/
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positios[0]), &positios[0], GL_DYNAMIC_DRAW);
	//���ú���ɫ��������λ������������Ķ�������
	glEnableVertexAttribArray(0);//0:��ɫ��������λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	/*����һ��������������
		����1:��Ӧ��ɫ��������λ��
		����2 : ÿ��������Ҫ���µķ�����Ŀ xyz������3
		����3 : û����������������
		����4 : ���ö�������������ǰ�Ƿ���Ҫ��һ��
		����5 : ������ÿ����Ԫ��֮��Ĵ�Сƫ��ֵ
		����6 : ���������ʼλ���������е�ƫ��ֵ
	*/


	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	/*���������ݱ����ڻ��������
		���2������:
			1.���䶥����������Ĵ洢�ռ�
			2.�����ݴ��˴��е�����copy��opengl����˵��ڴ���
			  GL_STATIC_DRAW:�Է������ݵĶ�ȡ��д��ķ�ʽ,��Ϊ����ֻ�ǻ��Ƶ�,
			  ����ʱ������������޸�,������Ϊ��̬.
	*/
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoord[0]), &texCoord[0], GL_DYNAMIC_DRAW);
	//���ú���ɫ��������λ������������Ķ�������
	glEnableVertexAttribArray(1);//1:��ɫ��������λ������
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	/*����һ��������������
		����1:��Ӧ��ɫ��������λ��
		����2 : ÿ��������Ҫ���µķ�����Ŀ xyz������3
		����3 : û����������������
		����4 : ���ö�������������ǰ�Ƿ���Ҫ��һ��
		����5 : ������ÿ����Ԫ��֮��Ĵ�Сƫ��ֵ
		����6 : ���������ʼλ���������е�ƫ��ֵ
	*/

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(indices[0]), &indices[0], GL_DYNAMIC_DRAW);
	/*element may not bind VertexAttribArray,so glEnableVertexAttribArray(1)
		&glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0) will no use.*/


	glBindVertexArray(0);//����ʹ���κη�����������
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
	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);
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
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}
void Mesh::Draw() {
	glBindVertexArray(m_vertexArrayObject);
	//glDrawArrays(GL_TRIANGLE_STRIP,0,m_drawCount); 
	//glDrawElements(GL_TRIANGLE_STRIP, m_drawCount, GL_UNSIGNED_INT, 0);
	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
