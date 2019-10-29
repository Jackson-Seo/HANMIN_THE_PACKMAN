#pragma once
#include "pch.h"
#include <vector>

class Object
{
private:
	std::vector<GLfloat> vertex; // ������
	std::vector<GLubyte> index; // ���� ��� ������ ���� �ε���
	float x, y, z = 0; // ���忡���� ��ġ
	float xRo, yRo, zRo = 0; // ȸ�� ����
public:
	Object(void);
	~Object(void);
	void AddVertex(GLfloat vtx[], int size); // Object�� Vertex �߰�
	void AddIndex(GLubyte idx[], int size);
	void Draw(void);
};

