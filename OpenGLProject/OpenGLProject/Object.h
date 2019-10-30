#pragma once
#include "pch.h"
#include <vector>

class Object
{
private:
	std::vector<GLfloat> vertex; // ������
	std::vector<GLubyte> index; // ���� ��� ������ ���� �ε���
	GLuint id; // GenList�� id��
	float x = 0, y = 0, z = 0; // ���忡���� ��ġ
	float xRo = 0, yRo = 0, zRo = 0; // ȸ�� ����
public:
	Object(void);
	Object(const GLuint id);
	~Object(void);
	void AddVertex(GLfloat vtx[], int size); // Object�� Vertex �߰�
	void AddIndex(GLubyte idx[], int size);
	void Draw(void);
};

