#include"Mesh.h"
#include <vector>


Mesh::Mesh(Vertex* vertices, unsigned int numVertices)
{
	m_drawCount = numVertices;
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
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positios[0]), &positios[0], GL_STATIC_DRAW);
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
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoord[0]), &texCoord[0], GL_STATIC_DRAW);
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



	glBindVertexArray(0);//����ʹ���κη�����������
}
Mesh::~Mesh() {
	glDeleteVertexArrays(1,&m_vertexArrayObject);
}
void Mesh::Draw() {
	glBindVertexArray(m_vertexArrayObject);
	glDrawArrays(GL_TRIANGLE_STRIP,0,m_drawCount); 
	glBindVertexArray(0);
}
