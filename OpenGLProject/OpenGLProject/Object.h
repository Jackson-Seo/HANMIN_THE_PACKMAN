#pragma once
#include <vector>
#include <string>
#include <map>
#include "Shader.h"

using namespace std;

class Object
{
private:

	vector<GLfloat> vertex; // 정점들
	vector<GLubyte> index; // 정점 찍는 순서에 대한 인덱스
	GLuint id; // GenList의 id값

	float x = 0, y = 0, z = 0; // 월드에서의 위치
	float xRo = 0, yRo = 0, zRo = 0; // 회전 각도
	float xSc = 1, ySc = 1, zSc = 1; // Scale값

	GLuint vaoId;
	GLuint vboVId;
	GLuint vboUvId;
	GLuint vboNorId;
	int m_iNumTriangles = 0;

public:

	vector<glm::vec3> bufferPosition; // Vertex의 위치
	vector<glm::vec2> bufferUV; // Vertex의 Texture 좌표
	vector<glm::vec3> bufferNormal; // Normal 좌표
	// 텍스쳐 구조체
	typedef struct {
		GLuint textureId;
		int w;
		int h;
		int comp;
		unsigned char* image = nullptr;
	} Texture;
	map<string, Texture> textures; // 여러 텍스쳐 저장한 구조체
	// Shape 구조체

	typedef struct {
		string texname;
		GLuint idxBegin;
		GLuint cntVertex;
	} Shape;
	vector<Shape> shapes;

public:
	void AddVertex(GLfloat vtx[], int size); // Object에 Vertex 추가
	void AddIndex(GLubyte idx[], int size);
	void Draw(const Shader& shader); // Object를 그립니다
	void setScale(const float& xSc, const float& ySc, const float& Sc); // Object의 Scale을 조정합니다
	void setNumTriangles(const int& n);
	void setID(const GLuint& vao, const GLuint& vboV, const GLuint& vboUV);
};