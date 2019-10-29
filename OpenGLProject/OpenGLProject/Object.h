#pragma once
#include "pch.h"
#include <vector>

class Object
{
private:
	std::vector<GLfloat> vertex; // 정점들
	std::vector<GLubyte> index; // 정점 찍는 순서에 대한 인덱스
	float x, y, z = 0; // 월드에서의 위치
	float xRo, yRo, zRo = 0; // 회전 각도
public:
	Object(void);
	~Object(void);
	void AddVertex(GLfloat vtx[], int size); // Object에 Vertex 추가
	void AddIndex(GLubyte idx[], int size);
	void Draw(void);
};

