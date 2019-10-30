#pragma once
#include "pch.h"
#include <vector>

class Object
{
private:
	std::vector<GLfloat> vertex; // 정점들
	std::vector<GLubyte> index; // 정점 찍는 순서에 대한 인덱스
	GLuint id; // GenList의 id값
	float x = 0, y = 0, z = 0; // 월드에서의 위치
	float xRo = 0, yRo = 0, zRo = 0; // 회전 각도
public:
	Object(void);
	Object(const GLuint id);
	~Object(void);
	void AddVertex(GLfloat vtx[], int size); // Object에 Vertex 추가
	void AddIndex(GLubyte idx[], int size);
	void Draw(void);
};

